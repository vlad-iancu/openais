#include <TMPMessages/TMPPauseMessage.hpp>
#include <TMPMessages/TMPStopMessage.hpp>
#include <TMPMessages/TMPRequestNameMessage.hpp>
#include <TMPMessages/TMPResponseNameMessage.hpp>
#include <TMPMessages/TMPRequestStatusMessage.hpp>
#include <TMPMessages/TMPResponseStatusMessage.hpp>
#include <TMPMessages/TMPResumeMessage.hpp>

#include <Task/TaskManager/TaskManagerServer/TMPServer.hpp>

#include <boost/functional.hpp>

using namespace openais::TMP;
using namespace openais::taskmanager;
using openais::TMP::TMPConnection;

TMPServer::TMPServer()
    :
        m_io(),
        m_workGuard(boost::asio::make_work_guard(m_io))
{
    
}

TMPServer::~TMPServer()
{
    Stop();
}

void TMPServer::Initialize(const openais::task::Config &config)
{
    std::string address;
    uint16_t port;
    address = config["address"].Get<std::string>("127.0.0.1");
    port = config["port"].Get<uint16_t>(7892);
    m_threadCount = config["threads"].Get<int>(1); 
    m_maxConnections = config["max_connections"].Get<int>(-1);
    m_pingInterval = config["ping_interval"].Get<uint64_t>(1000);
    boost::asio::ip::address addr = boost::asio::ip::address::from_string(address);
    m_endpoint = boost::asio::ip::tcp::endpoint(addr, port);
}

void TMPServer::Start()
{
    m_acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(m_io, m_endpoint);
    boost::asio::ip::tcp::no_delay nodelay;
    m_acceptor->set_option(nodelay);
    m_timer = std::make_unique<boost::asio::deadline_timer>(m_io, boost::posix_time::milliseconds(m_pingInterval));
    m_timer->async_wait(boost::bind(&TMPServer::HandlePingTimer, this, boost::asio::placeholders::error));
    m_active = true;
    Accept();
    for(int i = 0;i < m_threadCount; i++)
    {
        std::thread thr([&] {
                m_io.run();
        });
        thr.detach();
        m_threads.push_back(std::move(thr));
    }
}

boost::asio::io_context& TMPServer::GetIoContext()
{
    return m_io;
}

void TMPServer::Stop()
{
    m_workGuard.reset();
    m_timer->cancel();
    m_io.stop();
    for(auto &thr : m_threads)
    {
        if(thr.joinable())
        {
            thr.join();
        }
    }
    m_active = false;
}

bool TMPServer::IsActive() const
{
    return m_active;
}

void TMPServer::HandlePingTimer(const boost::system::error_code &ec)
{
    if(!IsActive())
    {
       return;
    }
    if(!ec)
    {
        for(auto &conn : m_connections)
        {
            SendRequestStatusMessage(&conn);
        }
        m_timer->expires_at(m_timer->expires_at() + boost::posix_time::milliseconds(m_pingInterval));
        m_timer->async_wait(boost::bind(&TMPServer::HandlePingTimer, this, boost::asio::placeholders::error));
    }
    else
    {
        if(ec.value() != boost::asio::error::operation_aborted)
        {
            Stop();
        }
    }
}

void TMPServer::Accept()
{
    if(!IsActive())
    {
       return;
    }
    boost::asio::ip::tcp::socket sock(m_io);
    TMPConnection *conn = new TMPConnection(std::move(sock));
    m_acceptor->async_accept(
            conn->GetSocket(),
            boost::bind(&TMPServer::HandleAccept, this, boost::asio::placeholders::error, conn));

}

void TMPServer::HandleAccept(const boost::system::error_code &ec, TMPConnection *conn)
{

    if(!IsActive())
    {
        return;
    }
    if(!ec)
    {
        m_connections.push_back(conn);
        conn->AddMessageHandler(std::bind(&TMPServer::OnResponseNameMessage, this, conn, std::placeholders::_1));
        conn->AddMessageHandler(std::bind(&TMPServer::OnResponseStatusMessage, this, conn, std::placeholders::_1)); 
        conn->StartListening();
        SendRequestNameMessage(conn);
        if(m_connections.size() < m_maxConnections && m_maxConnections > 0)
        {
            Accept();
        }
    }
}

void TMPServer::SendPauseMessage(TMPConnection *conn)
{
    if(!IsActive())
    {
       return;
    }
    TMPPauseMessage *msg = new TMPPauseMessage();
    msg->SetId(TMPID::PAUSE);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    conn->SendMessage(msgPtr);
}

void TMPServer::SendStopMessage(TMPConnection *conn)
{
    if(!IsActive())
    {
       return;
    }
    TMPStopMessage *msg = new TMPStopMessage();
    msg->SetId(TMPID::STOP);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    conn->SendMessage(msgPtr);
}

void TMPServer::SendResumeMessage(TMPConnection *conn)
{
    if(!IsActive())
    {
       return;
    }
    TMPResumeMessage *msg = new TMPResumeMessage();
    msg->SetId(TMPID::RESUME);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    conn->SendMessage(msgPtr);
}

void TMPServer::SendRequestStatusMessage(TMPConnection *conn)
{
   if(!IsActive())
   {
       return;
   }
   TMPRequestStatusMessage *msg = new TMPRequestStatusMessage();
   msg->SetId(TMPID::REQUEST_STATUS);
   TMPMessagePtr msgPtr = TMPMessagePtr(msg);
   conn->SendMessage(msgPtr);
}

void TMPServer::SendRequestNameMessage(TMPConnection *conn)
{
    if(!IsActive())
    {
       return;
    }
    TMPRequestNameMessage *msg = new TMPRequestNameMessage();
    msg->SetId(TMPID::REQUEST_NAME);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    conn->SendMessage(msgPtr);
}

void TMPServer::OnResponseNameMessage(TMPConnection *conn, openais::TMP::TMPMessagePtr msg)
{
    if(!IsActive())
    {
        return;
    }
    if(msg->GetId() == TMPID::RESPONSE_NAME)
    {
        TMPResponseNameMessage *msgPtr = dynamic_cast<TMPResponseNameMessage*>(msg.get());
    }
}

void TMPServer::OnResponseStatusMessage(TMPConnection *conn, openais::TMP::TMPMessagePtr msg)
{
    if(!IsActive())
    {
       return;
    }
    if(msg->GetId() == TMPID::RESPONSE_STATUS)
    {
        TMPResponseStatusMessage *msgPtr = dynamic_cast<TMPResponseStatusMessage*>(msg.get());
    }
}

void TMPServer::PauseTask(int taskId)
{
    SendPauseMessage(&m_connections[taskId]);
}

void TMPServer::StopTask(int taskId)
{
    SendStopMessage(&m_connections[taskId]);
}

void TMPServer::ResumeTask(int taskId)
{
    SendResumeMessage(&m_connections[taskId]);
}

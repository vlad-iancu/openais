#include <TMPMessages/TMPResponseStatusMessage.hpp>
#include <TMPMessages/TMPResponseNameMessage.hpp>
#include <Task/TaskManager/TaskManagerClient/TMPClient.hpp>
#include <Task/Task.hpp>

#include <iostream>
#include <functional>
#include <memory>

using namespace openais::taskmanager;
using namespace openais::TMP;
using openais::task::Config;

TMPClient::TMPClient()
    :
        m_io(),
        m_workGuard(boost::asio::make_work_guard(m_io))
{

}

TMPClient::~TMPClient()
{
    Stop();
}

void TMPClient::Initialize(const Config &config)
{
    SetTMAddress(config["address"].Get<std::string>("127.0.0.1"));
    SetTMPort(config["port"].Get<uint16_t>(7891));
    SetThreadCount(config["threads"].Get<int>(1));
}

void TMPClient::Start()
{
    boost::asio::ip::tcp::socket sock(m_io);
    sock.open(boost::asio::ip::tcp::v4());
    boost::asio::ip::tcp::no_delay nodelay;
    sock.set_option(nodelay);
    m_connection = TMPConnection::Create(std::move(sock));
    m_connection->SetRemoteAddress(m_address);
    m_connection->SetRemotePort(m_port);
    m_connection->AddMessageHandler(std::bind(&TMPClient::OnPauseMessage, this, std::placeholders::_1));
    m_connection->AddMessageHandler(std::bind(&TMPClient::OnResumeMessage, this, std::placeholders::_1));
    m_connection->AddMessageHandler(std::bind(&TMPClient::OnStopMessage, this, std::placeholders::_1));
    m_connection->AddMessageHandler(std::bind(&TMPClient::OnRequestNameMessage, this, std::placeholders::_1));
    m_connection->AddMessageHandler(std::bind(&TMPClient::OnRequestStatusMessage, this, std::placeholders::_1));
    m_connection->Start();
    for(int i = 0;i < m_threadCount; i++)
    {
        std::thread thr([&] {
                m_io.run();
        });
        thr.detach();
        m_threads.push_back(std::move(thr));
    }
    m_active = true;
}

void TMPClient::Stop()
{
    m_connection = nullptr;
    m_workGuard.reset();
    for(auto &thr : m_threads)
    {
        if(thr.joinable())
        {
            thr.join();
        }
    }
    m_active = false;
}

bool TMPClient::IsActive() const
{
    return m_active;
}

std::string TMPClient::GetTMAddress() const
{
    return m_address;
}

uint16_t TMPClient::GetTMPort() const
{
    return m_port;
}

int TMPClient::GetThreadCount() const
{
    return m_threadCount;
}

void TMPClient::SetTMAddress(const std::string &address)
{
    m_address = address;
}

void TMPClient::SetTMPort(uint16_t port)
{
    m_port = port;
}

void TMPClient::SetThreadCount(int threads)
{
    m_threadCount = threads;
}

void TMPClient::OnPauseMessage(TMP::TMPMessagePtr msg)
{
    if(msg->GetId() == TMP::PAUSE)
    {
        openais::task::Task::task->Pause();
    }
}
void TMPClient::OnStopMessage(TMP::TMPMessagePtr msg)
{
    if(msg->GetId() == TMP::STOP)
    {
        openais::task::Task::task->Stop();
    }
}
void TMPClient::OnResumeMessage(TMP::TMPMessagePtr msg)
{
    if(msg->GetId() == TMP::RESUME)
    {
        openais::task::Task::task->Resume();
    }
}
void TMPClient::OnRequestStatusMessage(TMP::TMPMessagePtr msg)
{
    TMP::TMPStatus status;
    if(msg->GetId() == TMP::REQUEST_STATUS)
    {
        bool isActive = openais::task::Task::task->IsActive();
        bool isPaused = openais::task::Task::task->IsPaused();
        if(isActive && isPaused)
        {
            status = TMP::TMPStatus::PAUSED;
        } 
        else
            if(!isActive)
            {
                status = TMP::TMPStatus::EXITED;
            } else
                {
                    status = TMP::TMPStatus::RUNNING;
                }
        SendResponseStatusMessage(status);
    }
}

void TMPClient::OnRequestNameMessage(TMP::TMPMessagePtr msg)
{
    if(msg->GetId() == TMP::REQUEST_NAME)
    {
        SendResponseNameMessage(openais::task::Task::task->GetName());
    }
}

void TMPClient::SendResponseNameMessage(const std::string &name)
{
    TMPResponseNameMessage *msg = new TMPResponseNameMessage(name);
    msg->SetId(TMP::TMPID::RESPONSE_NAME);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    m_connection->SendMessage(msgPtr);
}

void TMPClient::SendResponseStatusMessage(openais::TMP::TMPStatus status)
{
    TMPResponseStatusMessage *msg = new TMPResponseStatusMessage(status);
    msg->SetId(TMP::TMPID::RESPONSE_STATUS);
    TMPMessagePtr msgPtr = TMPMessagePtr(msg);
    m_connection->SendMessage(msgPtr);
}

#include <TMPConnection.hpp>
#include <TMP.hpp>

#include <TMPMessages/TMPPauseMessage.hpp>
#include <TMPMessages/TMPStopMessage.hpp>
#include <TMPMessages/TMPResumeMessage.hpp>
#include <TMPMessages/TMPRequestNameMessage.hpp>
#include <TMPMessages/TMPRequestStatusMessage.hpp>
#include <TMPMessages/TMPResponseNameMessage.hpp>
#include <TMPMessages/TMPResponseStatusMessage.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <sstream>

using namespace openais::TMP;

TMPConnection::TMPConnection(boost::asio::ip::tcp::socket socket)
    : m_socket(std::move(socket))
{
}

std::shared_ptr<TMPConnection> TMPConnection::Create(boost::asio::ip::tcp::socket socket)
{
    std::shared_ptr<TMPConnection> conn(new TMPConnection(std::move(socket)));
    return conn;
}

void TMPConnection::AddMessageHandler(TMPMessageHandler handler)
{
    m_handlerList.push_back(handler);
}

bool TMPConnection::IsActive() const
{
    return m_socket.is_open();
}

void TMPConnection::SendMessage(TMPMessagePtr msg)
{
    if(!IsActive())
    {
        return;
    }
    std::string content = msg->Save();
    char id = (char)(msg->GetId());
    m_socket.async_write_some(boost::asio::buffer(&id, 1),
            [&](const boost::system::error_code &err, std::size_t bytes)
            {
            });
    uint16_t length = (uint16_t)content.size();
    m_socket.async_write_some(boost::asio::buffer(&length, 2),
            [&](const boost::system::error_code &err, std::size_t bytes)
            {
            });
    m_socket.async_write_some(boost::asio::buffer(content.c_str(), content.size()),
            [&](const boost::system::error_code &err, std::size_t bytes)
            {
            });
}

void TMPConnection::Start()
{
    boost::asio::ip::tcp::endpoint remote_endpoint(boost::asio::ip::address::from_string(m_remoteAddress), m_remotePort);
    m_socket.async_connect(
            remote_endpoint,
            [&](const boost::system::error_code &ec)
            {
                if(ec)
                {
                    m_active = false;
                }
                ReadNextMessage();
            });
}

void TMPConnection::StartListening()
{
    ReadNextMessage();
}

std::string TMPConnection::GetRemoteAddress() const
{
    return m_remoteAddress;
}

boost::asio::ip::tcp::socket& TMPConnection::GetSocket()
{
    return m_socket;
}

void TMPConnection::SetRemoteAddress(const std::string &address)
{
    m_remoteAddress = address;
}

uint16_t TMPConnection::GetRemotePort() const
{
    return m_remotePort;
}

void TMPConnection::SetRemotePort(uint16_t port)
{
    m_remotePort = port;
}

void TMPConnection::ReadNextMessage()
{
    using namespace openais::TMP;
    using error_code = boost::system::error_code;
    if(!IsActive())
    {
        return;
    }
    m_socket.async_read_some(
            boost::asio::buffer(&m_msgId, 1),
            [&](const error_code &ec, std::size_t bytes)
            {
                if(ec)
                {
                    m_active = false;
                    return;
                }
                m_socket.async_read_some(
                        boost::asio::buffer(&m_msgLen, 2),
                        [&](const error_code &ec, std::size_t bytes)
                        {
                            if(ec || bytes != 2)
                            {
                                m_active = false;
                                return;
                            }
                            TMPID id = (TMPID)((int)m_msgId);
                            ReadMessage(id, m_msgLen);
                        });
            }
    );
}

void TMPConnection::ReadMessage(TMP::TMPID id, uint16_t length)
{
    using namespace TMP;
    
    if(!IsActive())
    {
        return;
    }
    m_msgLen = length;
    m_msgContent = std::unique_ptr<char[]>(new char[m_msgLen]);
    m_socket.async_read_some(
            boost::asio::buffer(m_msgContent.get(), m_msgLen),
            [&, id](const boost::system::error_code &ec, std::size_t bytes)
            {
                if(ec || bytes != m_msgLen)
                {
                    m_active = false;
                    return;
                }
                TMPMessage *msg;
                switch(id)
                {
                    case TMPID::PAUSE:
                    {
                        msg = new TMPPauseMessage();
                    } break;
                    case TMPID::STOP:
                    {
                        msg = new TMPStopMessage();
                    } break;
                    case TMPID::REQUEST_NAME:
                    {
                        msg = new TMPRequestNameMessage();
                    } break;
                    case TMPID::REQUEST_STATUS:
                    {
                        msg = new TMPRequestStatusMessage();
                    } break;
                    case TMPID::RESUME:
                    {
                        msg = new TMPResumeMessage();
                    } break;
                    case TMPID::RESPONSE_NAME:
                    {
                        msg = new TMPResponseNameMessage();
                    } break;
                    case TMPID::RESPONSE_STATUS:
                    {
                        msg = new TMPResponseStatusMessage();
                    } break;
                    default:
                    {
                        //nothing
                    }
                }
                
                TMPMessagePtr message(msg);
                message->Load(m_msgContent.get());
                PublishMessage(message);
                ReadNextMessage();
            });
}

void TMPConnection::PublishMessage(TMPMessagePtr msg)
{
    if(!IsActive())
    {
        return;
    }
    for(auto &handler : m_handlerList)
    {
        handler(msg);
    }
}



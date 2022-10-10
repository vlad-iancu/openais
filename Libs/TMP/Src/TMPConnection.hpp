#ifndef OPENAIS_LIBS_TMPCONNECTION_H
#define OPENAIS_LIBS_TMPCONNECTION_H

#include <boost/asio.hpp>
#include <memory>
#include <TMPMessage.hpp>
#include <functional>
#include <list>
#include <vector>

namespace openais
{
    namespace TMP
    {
        using TMPMessageHandler = std::function<void(openais::TMP::TMPMessagePtr)>;

        class TMPConnection 
        {
        private:
            using TMPMessagePtr = openais::TMP::TMPMessagePtr;

        public:
            static std::shared_ptr<TMPConnection> Create(boost::asio::ip::tcp::socket socket);
            TMPConnection(boost::asio::ip::tcp::socket socket);

        public:
            void Start();
            void StartListening();
            bool IsActive() const;
            void AddMessageHandler(TMPMessageHandler handler); 
        
        public:
            std::string GetRemoteAddress() const;
            uint16_t GetRemotePort() const;
            boost::asio::ip::tcp::socket& GetSocket();

            void SetRemoteAddress(const std::string &address);
            void SetRemotePort(uint16_t port);

        private:
            void ReadNextMessage();
            void ReadMessage(openais::TMP::TMPID id, uint16_t length);
            
        public:
            void SendMessage(TMPMessagePtr msg);

        private:
            void PublishMessage(TMPMessagePtr msg);

        private:
            std::string m_remoteAddress;
            uint16_t m_remotePort;
            boost::asio::ip::tcp::socket m_socket;
            std::list<TMPMessageHandler> m_handlerList;
            bool m_active;
            std::unique_ptr<char[]> m_msgContent;
            char m_msgId;
            uint16_t m_msgLen;
        };
    }
}

#endif


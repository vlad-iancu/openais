#ifndef OPENAIS_TASK_TMPCLIENT_H
#define OPENAIS_TASK_TMPCLIENT_H
#include <TMPMessage.hpp>

#include <boost/asio.hpp>
#include <TMPConnection.hpp>
#include <Task/Config.hpp>

#include <thread>
#include <string>
#include <cstdint>
#include <memory>

namespace openais
{
    namespace taskmanager
    {
        class TMPClient
        {
        public:
            TMPClient();
            ~TMPClient();

        public:
            void Initialize(const openais::task::Config &config);
            void Start();

        public:
            void Stop();
            bool IsActive() const;

        public:
            std::string GetTMAddress() const;
            uint16_t GetTMPort() const;
            int GetThreadCount() const;
            
            void SetTMAddress(const std::string &address);
            void SetTMPort(uint16_t port);
            void SetThreadCount(int threads);

        private:
            void OnPauseMessage(TMP::TMPMessagePtr msg);
            void OnStopMessage(TMP::TMPMessagePtr msg);
            void OnResumeMessage(TMP::TMPMessagePtr msg);
            void OnRequestStatusMessage(TMP::TMPMessagePtr msg);
            void OnRequestNameMessage(TMP::TMPMessagePtr msg);

            void SendResponseNameMessage(const std::string &name);
            void SendResponseStatusMessage(openais::TMP::TMPStatus status);

        private:
            std::string m_address;
            int m_threadCount;
            uint16_t m_port;
            bool m_active;
            boost::asio::io_context m_io;
            std::shared_ptr<openais::TMP::TMPConnection> m_connection;
            std::list<std::thread> m_threads;
            boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;
        };
    }
}

#endif

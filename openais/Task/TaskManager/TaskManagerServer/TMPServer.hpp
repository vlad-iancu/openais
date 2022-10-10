#ifndef OPENAIS_TASK_TASKMANAGER_SERVER_H
#define OPENAIS_TASK_TASKMANAGER_SERVER_H

#include <boost/asio.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <TMPConnection.hpp>
#include <Task/Config.hpp>

#include <thread>
#include <list>
#include <chrono>

namespace openais
{
    namespace taskmanager
    {
        class TMPServer
        {
        public:
            TMPServer();
            ~TMPServer();

        public:
            void Initialize(const openais::task::Config &config);
            void Start();
            void Stop();
            bool IsActive() const;
            boost::asio::io_context &GetIoContext();

        private:
            void Accept();
            void HandleAccept(const boost::system::error_code &ec, openais::TMP::TMPConnection *conn);
            void HandlePingTimer(const boost::system::error_code &ec);

        private:
            void SendPauseMessage(openais::TMP::TMPConnection *conn);
            void SendStopMessage(openais::TMP::TMPConnection *conn);
            void SendResumeMessage(openais::TMP::TMPConnection *conn);
            void SendRequestStatusMessage(openais::TMP::TMPConnection *conn);
            void SendRequestNameMessage(openais::TMP::TMPConnection *conn);

            void OnResponseNameMessage(openais::TMP::TMPConnection *conn, openais::TMP::TMPMessagePtr msg);
            void OnResponseStatusMessage(openais::TMP::TMPConnection *conn, openais::TMP::TMPMessagePtr msg);

        public:
            void PauseTask(int taskId);
            void StopTask(int taskId);
            void ResumeTask(int taskId);

        private:
            std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
            std::unique_ptr<boost::asio::deadline_timer> m_timer;
            uint64_t m_pingInterval;
            boost::asio::ip::tcp::endpoint m_endpoint;
            boost::asio::io_context m_io;
            int m_maxConnections;
            boost::ptr_vector<openais::TMP::TMPConnection> m_connections;
            int m_threadCount;
            std::list<std::thread> m_threads;
            bool m_active;
            boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;

        };
    }
}

#endif

#include <Task/TaskManager/TaskManagerServer/TMPServer.hpp>
#include <Task/Config.hpp>

#include <cstdlib>
#include <iostream>
#include <thread>
#include <signal.h>
#include <execinfo.h>

using namespace openais::taskmanager;
using namespace openais::task;

TMPServer *g_server;

static void signal_handler(int signal)
{
    g_server->Stop();
    exit(0);
}

static void segfault_handler(int signal)
{
    void *arr[13];
    std::size_t size;
    size = backtrace(arr, 13);
    backtrace_symbols_fd(arr, size, STDERR_FILENO);
    exit(1);
}

static void AttachSignals()
{
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGSEGV, segfault_handler);
}

int main()
{
    AttachSignals();
    TMPServer srv;
    const char *configDirStr = getenv("OPENAIS_CONFIG_DIR");
    setenv("PYTHONPATH", configDirStr, 1);
    Py_Initialize();
    Config config;
    openais::task::GetPythonConfig("TaskManagerServer", config);
    g_server = &srv;
    srv.Initialize(config);
    srv.Start();
    
    while(srv.IsActive())
    {
        int command;
        int index;
        std::cout << "1 - PAUSE" << std::endl;
        std::cout << "2 - STOP" << std::endl;
        std::cout << "3 - RESUME" << std::endl;
        if(srv.IsActive())
            std::cin >> command >> index;
        switch (command) {
            case 1: {srv.PauseTask(index);}  break;
            case 2: {srv.StopTask(index);}  break;
            case 3: {srv.ResumeTask(index);}  break;
            default:
                    {
                        break;
                    }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}


#define PY_SSIZE_T_CLEAN
#include <Task/Task.hpp>
#include <Task/Config.hpp>
#include <Task/PeriodicTask.hpp>
#include <Task/ContinualTask.hpp>
#ifdef OPENAIS_DEBUG
#include <Task/TaskManager/TaskManagerClient/TMPClient.hpp>
#endif
#include <Logger/Logger.hpp>

#include <Interface/InterfaceDB.hpp>
#include <Interface/Interface.hpp>

#include <boost/property_tree/ptree.hpp>

#include <csignal>
#include <chrono>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <variant>

namespace openais
{
    namespace task
    {
        void signal_handler(int signal)
        {
            Task::task->Stop();
            //SIG_DFL(signal);
        }

        void AttachSignals()
        {
            signal(SIGTERM, signal_handler);
            signal(SIGINT, signal_handler);
            //signal(SIGSEGV, SIG_DFL);
            //signal(SIGBUS, SIG_DFL);
            //signal(SIGABRT, SIG_DFL);
            //signal(SIGILL, SIG_DFL);
            signal(SIGQUIT, signal_handler);
            //signal(SIGSYS, SIG_DFL);
            //signal(SIGFPE, SIG_DFL);
            
        }

        void RegisterInterfaces(const Config &config)
        {
            using namespace openais::interface;
            for (const auto &interface : config)
            {
                const boost::ptr_vector<Config> &vec = interface.Get<const boost::ptr_vector<Config> &>();
                std::string interfaceDbName = interface.Get<const boost::ptr_vector<Config> &>()[0].Get<std::string>();
                std::string interfaceName = interface.Get<const boost::ptr_vector<Config> &>()[1].Get<std::string>();
                Interface *iface = Interface::GetInterface(interfaceName);
                if (!iface)
                {
                    continue;
                }

                InterfaceDB::Register(interfaceDbName, iface);
            }
        }

        int Main(int argc, char **argv)
        {
            AttachSignals();
            Config config;
            try
            {
                const char *configDirStr = getenv("OPENAIS_CONFIG_DIR");
                setenv("PYTHONPATH", configDirStr, 1);
                Py_Initialize();
                std::string taskName = openais::task::Task::task->GetName();
                GetPythonConfig(taskName + "Config", config);
            }
            catch (const std::exception &e)
            {
                std::cout << "Error at parsing config file" << std::endl;
                return 1;
            }
                       
            openais::logger::Logger::Configure(config);
            RegisterInterfaces(config["Interfaces"]);
            double frequencyHz;
            try
            {
                frequencyHz = config["frequencyHz"].Get<double>();
            }
            catch (const std::exception &e)
            {
                // frequencyHz not present
            }

            PeriodicTask *periodicTask = dynamic_cast<PeriodicTask *>(Task::task);
            ContinualTask *continualTask = dynamic_cast<ContinualTask *>(Task::task);
#ifdef OPENAIS_DEBUG
            openais::taskmanager::TMPClient client;
            client.Initialize(config["TMP"]);
            client.Start();
#endif
            if (periodicTask)
            {
                periodicTask->SetFrequency(frequencyHz);
                periodicTask->Initialize(config);
                periodicTask->Run();
                periodicTask->Clean();
            }
            if (continualTask)
            {
                continualTask->Initialize(config);
                continualTask->Run();
                continualTask->Clean();
            }
            openais::logger::Logger::Release();
            Py_Finalize();
            return 0;
        }

    } // namespace task

} // namespace openais

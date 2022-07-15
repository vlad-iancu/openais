#define PY_SSIZE_T_CLEAN
#include <Task/Task.hpp>
#include <Task/Config.hpp>
#include <Task/PeriodicTask.hpp>
#include <Task/ContinualTask.hpp>

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
            signal(SIGSEGV, SIG_DFL);
            signal(SIGBUS, signal_handler);
            signal(SIGABRT, signal_handler);
            signal(SIGILL, signal_handler);
            signal(SIGQUIT, signal_handler);
            signal(SIGSYS, signal_handler);
            signal(SIGFPE, signal_handler);
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

        void GetPythonConfig(std::string module, Config &config)
        {
            PyObject *pModule, *pModuleDict;
            pModule = PyImport_ImportModule(module.c_str());
            pModuleDict = PyModule_GetDict(pModule);
            config.FromPythonObject(pModuleDict);
        }

        int Main(int argc, char **argv)
        {
            AttachSignals();
            //std::cout << "Entered main" << std::endl;
            Config config;
            //std::cout << "Trying to parse config" << std::endl;
            try
            {
                std::filesystem::path configPath(Task::task->GetConfigFileName());
                setenv("PYTHONPATH", configPath.parent_path().c_str(), 1);
                Py_Initialize();
                //std::cout << "Py_Initialize" << std::endl;
                GetPythonConfig(configPath.replace_extension("").filename().c_str(), config);
                //std::cout << "Got config" << std::endl;
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

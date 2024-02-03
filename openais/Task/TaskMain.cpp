#define PY_SSIZE_T_CLEAN
#include <Task/Task.hpp>
#include <Task/Interpreter.hpp>
#include <Task/PeriodicTask.hpp>
#include <Task/ContinualTask.hpp>
#include <Task/Component.hpp>
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
            // SIG_DFL(signal);
        }

        void AttachSignals()
        {
            signal(SIGTERM, signal_handler);
            signal(SIGINT, signal_handler);
            // signal(SIGSEGV, SIG_DFL);
            // signal(SIGBUS, SIG_DFL);
            // signal(SIGABRT, SIG_DFL);
            // signal(SIGILL, SIG_DFL);
            signal(SIGQUIT, signal_handler);
            // signal(SIGSYS, SIG_DFL);
            // signal(SIGFPE, SIG_DFL);
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
            Py_Initialize();
            Interpreter::Initialize(PyThreadState_Get());
            Config config;
            const char *configDirStr = getenv("OPENAIS_CONFIG_DIR");
            std::string configModule = openais::task::Task::task->GetName() + "Config";
            Interpreter interp(configDirStr);

            interp.Get(configModule, config);
            openais::logger::Logger::Configure(config);
            RegisterInterfaces(config["Interfaces"]);

            PeriodicTask *periodicTask = dynamic_cast<PeriodicTask *>(Task::task);
            ContinualTask *continualTask = dynamic_cast<ContinualTask *>(Task::task);

            
            double frequencyHz;
            try
            {
                frequencyHz = config["frequencyHz"].Get<double>();
            }
            catch (const std::exception &e)
            {
                // frequencyHz not present
                if (periodicTask)
                {
                    std::cout << "frequencyHz not present" << std::endl;
                    exit(1);
                }
            }
            std::cout << "Components: " << Component::GetCounter() << std::endl;
            for(int i = 0; i < Component::GetCounter(); i++)
            {
                Component *component = Component::GetComponent(i);
                component->SetFrequency(config["components"][component->GetName()]["frequencyHz"].Get<double>());
                component->Initialize(config["components"][component->GetName()]);
                std::cout << "Component " << component->GetName() << " initialized" << std::endl;
            }
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
            return 0;
        }

    } // namespace task

} // namespace openais

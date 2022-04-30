#include <Task/Task.hpp>
#include <Task/Config.hpp>
#include <Task/CommandLine.hpp>

#include <Interface/InterfaceDB.hpp>
#include <Interface/Interface.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <csignal>
#include <chrono>
#include <thread>
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
        }

        void AttachSignals()
        {
            signal(SIGTERM, signal_handler);
            signal(SIGINT, signal_handler);
            signal(SIGSEGV, signal_handler);
            signal(SIGBUS, signal_handler);
            signal(SIGABRT, signal_handler);
        }

        void RegisterInterfaces(const Config &config)
        {
            using namespace openais::interface;
            for (const auto &kv : config)
            {
                std::string interfaceDbName = kv.first;
                std::string interfaceName = std::get<string>(kv.second);

                Interface *iface = Interface::GetInterface(interfaceName);
                if (!iface)
                    continue;

                InterfaceDB::Register(interfaceDbName, iface);
            }
        }

        int Main(int argc, char **argv)
        {
            AttachSignals();

            JsonConfig jsonConfig;

            try
            {
                boost::property_tree::read_json(Task::task->GetConfigFileName(), jsonConfig);
            }
            catch(const std::exception& e)
            {
                std::cout << "Warning: config file " << Task::task->GetConfigFileName() << " could not be parsed" << std::endl;
            }
            
            Config taskConfig;
            Config interfaceConfig;

            try
            {
                taskConfig = ParseJsonConfig(jsonConfig.get_child("config"));
                interfaceConfig = ParseJsonConfig(jsonConfig.get_child("interfaces"));
            }
            catch(const boost::property_tree::ptree_bad_path& e)
            {
                std::cerr << e.what() << '\n';
            }

            bool help;
            boost::optional<std::pair<Config, Config>> commandLineOptions = ParseCommandLineOptions(argc, argv, help);
            if (help)
            {
                return 0;
            }
            if (!commandLineOptions.has_value())
            {
                std::cout << "Incorrect command line arguments" << std::endl;
                return -1;
            }
            Config &taskCommandLineConfig = commandLineOptions.value().first;
            Config &interfaceCommandLineConfig = commandLineOptions.value().second;
            for (const auto &[k, v] : taskCommandLineConfig)
            {
                taskConfig[k] = v;
            }
            for (const auto &[k, v] : interfaceCommandLineConfig)
            {
                interfaceConfig[k] = v;
            }

            RegisterInterfaces(interfaceConfig);

            double frequency_hz = std::get<double>(taskConfig["frequency_hz"]);

            Task::task->Initialize(taskConfig);
            Task::task->Run(frequency_hz);
            Task::task->Clean();

            return 0;
        }

    } // namespace task

} // namespace openais

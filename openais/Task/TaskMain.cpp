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

using namespace openais::task;

/* #define EXTRACT_CONFIG_PARAMETER(id, type)                             \
    boost::optional<type> id = kv.second.get_optional<type>(kv.first); \
    if (id.has_value())                                                \
    {                                                                  \
        config[kv.first] = id.value();                                 \
    }
 */
bool g_stop = false;
void signal_handler(int signal)
{
    g_stop = true;
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
        if(!iface) continue;

        InterfaceDB::Register(interfaceDbName, iface);
    }
}

int main(int argc, char **argv)
{
    AttachSignals();

    JsonConfig jsonConfig;

    boost::property_tree::read_json(Task::task->GetConfigFileName(), jsonConfig);

    Config taskConfig = ParseJsonConfig(jsonConfig.get_child("config"));
    Config interfaceConfig = ParseJsonConfig(jsonConfig.get_child("interfaces"));
    bool help;
    boost::optional<std::pair<Config, Config>> commandLineOptions = ParseCommandLineOptions(argc, argv, help);
    if(help)
    {
        return 0;
    }
    if(!commandLineOptions.has_value())
    {
        std::cout << "Incorrect command line arguments" << std::endl;
        return -1;
    }
    Config &taskCommandLineConfig = commandLineOptions.value().first;
    Config &interfaceCommandLineConfig = commandLineOptions.value().second;
    for(const auto &[k, v] : taskCommandLineConfig)
    {
        taskConfig[k] = v;
    }
    for(const auto &[k, v] : interfaceCommandLineConfig)
    {
        interfaceConfig[k] = v;
    }
    
    RegisterInterfaces(interfaceConfig);
    uint64_t sleep_time = (uint64_t)((1.0 / std::get<double>(taskConfig["frequency_hz"]) * 1E6));
    Task::task->Initialize(taskConfig);
    while (!g_stop)
    {
        Task::task->Executive();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
    }
    Task::task->Clean();
    return 0;
}
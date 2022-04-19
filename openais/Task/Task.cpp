#include <Task/Task.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <Interface/InterfaceDB.hpp>
#include <Interface/Interface.hpp>

#include <csignal>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iostream>

using namespace openais::task;
using JsonConfig = boost::property_tree::ptree;

openais::task::Task *openais::task::Task::task;

#define EXTRACT_CONFIG_PARAMETER(id, type)                             \
    boost::optional<type> id = kv.second.get_optional<type>(kv.first); \
    if (id.has_value())                                                \
    {                                                                  \
        config[kv.first] = id.value();                                 \
    }

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

void RegisterInterfaces(const JsonConfig &config)
{
    using namespace openais::interface;
    for (const auto &kv : config)
    {
        std::string interfaceDbName = kv.first;
        boost::optional<std::string> interfaceNameOptional = kv.second.get_value_optional<std::string>();
        if(!interfaceNameOptional.has_value()) continue;

        std::string interfaceName = interfaceNameOptional.get();
        Interface *iface = Interface::GetInterface(interfaceName);
        if(!iface) continue;

        InterfaceDB::Register(interfaceDbName, iface);
        std::cout << "Added Interface " << interfaceDbName << " -> " << interfaceName << std::endl;
    }
    std::cout << "Finished adding interfaces" << std::endl;
}

int main()
{
    AttachSignals();

    Config config;

    JsonConfig jsonConfig;

    boost::property_tree::read_json(Task::task->GetConfigFileName(), jsonConfig);

    RegisterInterfaces(jsonConfig.get_child("interfaces"));
    uint64_t sleep_time = (uint64_t)((1.0 / jsonConfig.get<double>("config.frequency_hz")) * 1E6);
    std::cout << "Sleep time: " << sleep_time << " microseconds"  << std::endl;
    
    for (const auto &kv : jsonConfig.get_child("config"))
    {
        EXTRACT_CONFIG_PARAMETER(stringValue, string);
        EXTRACT_CONFIG_PARAMETER(doubleValue, double);
        EXTRACT_CONFIG_PARAMETER(uintValue, uint64_t);
    }

    Task::task->Initialize(config);
    while (!g_stop)
    {
        Task::task->Executive();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
    }
    Task::task->Clean();
    return 0;
}
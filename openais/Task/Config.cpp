#include <Task/Config.hpp>
#include <iostream>

using namespace openais::task;

#define EXTRACT_CONFIG_PARAMETER(type)                                                       \
    boost::optional<type> type##Value = kv.second.get_value_optional<type>();                \
    if ((type##Value).has_value())                                                           \
    {                                                                                        \
        config[kv.first] = (type##Value).value();                                            \
    }                                                                                        \

Config openais::task::ParseJsonConfig(const JsonConfig &jsonConfig)
{
    Config config;
    for (const auto &kv : jsonConfig)
    {
        EXTRACT_CONFIG_PARAMETER(string);
        EXTRACT_CONFIG_PARAMETER(uint64_t);
        EXTRACT_CONFIG_PARAMETER(double);
    }
    return config;
}
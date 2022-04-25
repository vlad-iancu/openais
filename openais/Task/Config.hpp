#ifndef OPENAIS_CONFIG_H
#define OPENAIS_CONFIG_H

#include <map>
#include <string>
#include <variant>
#include <boost/property_tree/ptree.hpp>

namespace openais
{
    namespace task
    {
        using string = std::string;
        using ConfigValue = std::variant<double, string, uint64_t>;
        using Config = std::map<string, ConfigValue>;
        using JsonConfig = boost::property_tree::ptree;
        
        Config ParseJsonConfig(const JsonConfig &jsonConfig);
    } // namespace task
    
} // namespace openais


#endif
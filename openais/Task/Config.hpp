#ifndef OPENAIS_CONFIG_H
#define OPENAIS_CONFIG_H

#include <map>
#include <string>
#include <variant>

namespace openais
{
    namespace task
    {
        using string = std::string;
        using ConfigValue = std::variant<double, string, uint64_t>;
        using Config = std::map<string, ConfigValue>;
    } // namespace task
    
} // namespace openais


#endif
#include <Task/CommandLine.hpp>

#include <boost/lexical_cast.hpp>

#include <utility>
#include <iostream>

#define CONVERT(type)                                       \
    try                                                     \
    {                                                       \
        value = boost::lexical_cast<type>(str);             \
        return value;                                       \
    }                                                       \
    catch(boost::bad_lexical_cast&)                         \
    {                                                       \
                                                            \
    }

static ConfigValue ToConfigValue(const string &str)
{
    ConfigValue value;
    CONVERT(double);
    CONVERT(uint64_t);
    CONVERT(string);
    return value;
}

boost::optional<std::pair<Config, Config>> openais::task::ParseCommandLineOptions(int argc, char **argv, bool &help)
{
    namespace po = boost::program_options;
    using tokenizer = boost::tokenizer<boost::char_separator<char>>;

    Config config;
    Config interface;

    po::options_description description("Options");

    description.add_options()
    ("help,h", "Help screen")
    ("config,c", po::value<std::vector<string>>(), "Value in the Task configuration in th form \"--config key=value\"")
    ("interface,i", po::value<std::vector<string>>(), "Interface entry in InterfaceDB in the form \"--interface interfaceDbName=interfaceName\"");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);

    if(vm.count("help"))
    {
        std::cout << description << std::endl;
        help = true;
        return boost::optional<std::pair<Config, Config>>(std::make_pair(Config(), Config()));
    }
    help = false;

    std::vector<string> configEntries = vm.count("config") ? vm["config"].as<std::vector<string>>() : std::vector<string>(0);
    std::vector<string> interfaceEntries = vm.count("interface") ? vm["interface"].as<std::vector<string>>() : std::vector<string>(0);

    boost::char_separator<char> equals("=");
    for (const auto &configEntry : configEntries)
    {
        tokenizer tokens(configEntry, equals);
        std::vector<string> nameValue;
        std::copy(tokens.begin(), tokens.end(), std::back_inserter(nameValue));
        if (nameValue.size() != 2)
        {
            return boost::optional<std::pair<Config, Config>>(std::make_pair(Config(), Config()));
        }
        std::string name = nameValue[0];
        ConfigValue value = ToConfigValue(nameValue[1]);
        config[name] = value;
    }
    for (const auto &interfaceEntry : interfaceEntries)
    {
        tokenizer tokens(interfaceEntry, equals);
        std::vector<string> nameValue;
        std::copy(tokens.begin(), tokens.end(), std::back_inserter(nameValue));
        if (nameValue.size() != 2)
        {
            return boost::optional<std::pair<Config, Config>>(std::make_pair(Config(), Config()));
        }
        std::string name = nameValue[0];
        ConfigValue value = nameValue[1];
        interface[name] = value;
    }
    return std::make_pair(config, interface);
}
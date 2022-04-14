#include <Interface/InterfaceDB.hpp>

using namespace openais::interface;

std::map<std::string, Interface*> InterfaceDB::interfaces;

void InterfaceDB::Register(const std::string &name, Interface *interface)
{
    interfaces[name] = interface;
}

#include <Interface/Interface.hpp>

#include <algorithm>

using namespace openais::interface;

int Interface::counter = 0;
Interface *Interface::interfaces[MAX_INTERFACES];

Interface *Interface::GetInterface(int index)
{
    return interfaces[index];
}

int Interface::GetInterfaceCount()
{
    return counter;
}

void Interface::RegisterInterface(Interface *interface)
{
    interfaces[counter] = interface->Clone();
}

Interface *Interface::GetInterface(const std::string &name)
{
    Interface **ifaceptr = std::find_if(
        interfaces, 
        interfaces + counter,
        [&](const Interface *el)
        {
            return name == el->GetInterfaceName();
        });
    if(ifaceptr == nullptr)
    {
        return nullptr;
    }
    return *ifaceptr;
}
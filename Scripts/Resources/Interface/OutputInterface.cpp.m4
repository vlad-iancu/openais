define(ClassName, `Output'interfaceName`Interface')dnl
`#include'<ClassName.hpp>
`#include'<iostream>

using namespace openais::interfaces;

ClassName ClassName::_interface;

ClassName::ClassName`()'
{
    `openais::interface::Interface::RegisterInterface(this)';
}

ClassName::ClassName`('const ClassName &other`)'
{

}

void ClassName::`Publish'(const interfaceType &data)
{
    std::cout << "ClassName publishes" << `std::endl';
}

std::string ClassName::`GetInterfaceName'() const
{
    return "interfaceName";
}

openais::interface::Interface *ClassName::`Clone'() const
{
    return new ClassName`(*this)';
}


define(NAME, translit(interfaceName, `a-z', `A-Z'))dnl
define(ClassName, `Input'interfaceName`Interface')dnl

`#include' <ClassName.hpp>

`#include <chrono>'

`using namespace openais::interfaces;'

ClassName ClassName::_interface;

ClassName::ClassName`()'
{
    ` openais::interface::Interface::RegisterInterface(this);'
}

ClassName::ClassName`('const ClassName &other`)'
{
}

`openais::interface::Interface *'ClassName::Clone`()' const
{
    return new ClassName`(*this)';
}

std::string ClassName::GetInterfaceName`()' const
{
    return "interfaceName";
}

bool ClassName::Start`()'
{
    IsActive`(true)';
    return true;
}

bool ClassName::Stop`()'
{
    IsActive`(false)';
    return true;
}

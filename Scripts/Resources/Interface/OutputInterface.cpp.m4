define(ClassName, `Output'interfaceName`Interface')dnl
`#include'<ClassName.hpp>

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

}

std::string ClassName::`GetInterfaceName'() const
{
    return "interfaceName";
}

openais::interface::Interface *ClassName::`Clone'() const
{
    return new ClassName`(*this)';
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

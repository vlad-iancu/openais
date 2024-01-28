#!/bin/sh

ClassName=Output$1Interface
interfaceType=$2

cat << EOF
#include <$ClassName.hpp>

using namespace openais::interfaces;

$ClassName $ClassName::_interface;

$ClassName::$ClassName()
{
    openais::interface::Interface::RegisterInterface(this);
}

$ClassName::$ClassName(const $ClassName &other)
{

}

void $ClassName::Publish(const $interfaceType &data)
{

}

std::string $ClassName::GetInterfaceName() const
{
    return "$INTERFACE_NAME";
}

openais::interface::Interface *$ClassName::Clone() const
{
    return new $ClassName(*this);
}

bool $ClassName::Start()
{
    SetActive(true);
    return true;
}

bool $ClassName::Stop()
{
    SetActive(false);
    return true;
}
EOF
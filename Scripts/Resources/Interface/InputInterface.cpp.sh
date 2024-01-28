#!/bin/bash

interfaceType=$2
#Create CMakeLists.txt
ClassName="Input"$1"Interface"

cat << EOF
#include <$ClassName.hpp>
#include <chrono>
using namespace openais::interfaces;

$ClassName $ClassName::_interface;

$ClassName::$ClassName()
{
    openais::interface::Interface::RegisterInterface(this);
}

$ClassName::$ClassName(const $ClassName &other)
{
}

openais::interface::Interface *$ClassName::Clone() const
{
    return new $ClassName(*this);
}

std::string $ClassName::GetInterfaceName() const
{
    return "$interfaceName";
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
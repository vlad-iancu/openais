#!/bin/bash

COMPONENT=$1
TASK=$2
CLASS=${COMPONENT}Component

if [ -z "$COMPONENT" ]; then
    echo "Component name is required"
    exit 1
fi
if [ -z "$TASK" ]; then
    echo "Task name is required"
    exit 1
fi
cat << EOF

#include "$CLASS.hpp"
#include <Task/Task.hpp>
#include <iostream>

using namespace openais::task;

$CLASS $CLASS::_instance;

$CLASS::$CLASS()
{
    Component::RegisterComponent(this);
}

$CLASS::~$CLASS()
{
}

void $CLASS::Initialize(const Config &config)
{
}

void $CLASS::Start()
{
    SetActive(true);
}

void $CLASS::Stop()
{
}

void $CLASS::Execute()
{
    std::cout << "Executing $CLASS" << std::endl;
}

std::string $CLASS::GetName() const
{
    return "$COMPONENT";
}

Component *$CLASS::Clone() const
{
    return new $CLASS(*this);
}


EOF
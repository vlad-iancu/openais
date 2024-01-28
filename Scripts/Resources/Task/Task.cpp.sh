#!/bin/bash

SampleTask=$1Task
SAMPLE_TASK_CONFIG_FILENAME=`echo $1 | tr 'a-z' 'A-Z'`_TASK_CONFIG_FILENAME

cat << EOF
#include <$SampleTask.hpp>
#include <iostream>


using Task = openais::task::Task;
using $SampleTask = openais::task::$SampleTask;
using Config = openais::task::Config;

$SampleTask $SampleTask::_task;

$SampleTask::$SampleTask()
{
    Task::task = this->Clone();
}

Task *$SampleTask::Clone() const
{
    return new $SampleTask(*this);
}

void $SampleTask::Initialize(const Config &config)
{
}

void $SampleTask::Executive()
{
    std::cout << "$SampleTask is running..." << std::endl;
}

void $SampleTask::Clean()
{
}

std::string $SampleTask::GetName() const
{
    return "$SampleTask";
}
EOF
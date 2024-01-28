#include <SomeTask.hpp>
#include <iostream>


using Task = openais::task::Task;
using SomeTask = openais::task::SomeTask;
using Config = openais::task::Config;

SomeTask SomeTask::_task;

SomeTask::SomeTask()
{
    Task::task = this->Clone();
}

Task *SomeTask::Clone() const
{
    return new SomeTask(*this);
}

void SomeTask::Initialize(const Config &config)
{
}

void SomeTask::Executive()
{
    std::cout << "SomeTask is running..." << std::endl;
}

void SomeTask::Clean()
{
}

std::string SomeTask::GetName() const
{
    return "SomeTask";
}

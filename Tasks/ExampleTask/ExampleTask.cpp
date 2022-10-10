#include <ExampleTask.hpp>
#include <iostream>

using Task = openais::task::Task;
using ExampleTask = openais::task::ExampleTask;
using Config = openais::task::Config;

ExampleTask ExampleTask::_task;

ExampleTask::ExampleTask()
{
    Task::task = this->Clone();
}

Task *ExampleTask::Clone() const
{
    return new ExampleTask(*this);
}

void ExampleTask::Initialize(const Config &config)
{
    m_printStr = config["printStr"].Get<std::string>("No printStr");
}

void ExampleTask::Executive()
{
    std::cout << "ExampleTask is running... printStr = \"" << m_printStr << "\"" << std::endl;
}

void ExampleTask::Clean()
{
}

std::string ExampleTask::GetName() const
{
    return "ExampleTask";
}


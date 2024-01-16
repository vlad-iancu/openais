#include <HelloPrinterTask.hpp>
#include <iostream>

using Task = openais::task::Task;
using HelloPrinterTask = openais::task::HelloPrinterTask;
using Config = openais::task::Config;

HelloPrinterTask HelloPrinterTask::_task;

HelloPrinterTask::HelloPrinterTask()
{
    Task::task = this->Clone();
}

Task *HelloPrinterTask::Clone() const
{
    return new HelloPrinterTask(*this);
}

void HelloPrinterTask::Initialize(const Config &config)
{
}

void HelloPrinterTask::Executive()
{
    std::cout << "HelloPrinterTask is running..." << std::endl;
}

void HelloPrinterTask::Clean()
{
}

std::string HelloPrinterTask::GetName() const
{
    return "HelloPrinterTask";
}

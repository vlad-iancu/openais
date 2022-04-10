#include <SampleTask.hpp>
#include <iostream>

using Task = openais::task::Task;
using SampleTask = openais::task::SampleTask;
using Config = openais::task::Config;
using string = std::string;

SampleTask SampleTask::_task;

SampleTask::SampleTask()
{
    Task::task = this->Clone();
}

Task *SampleTask::Clone() const
{
    return new SampleTask(*this);
}

void SampleTask::Initialize(const Config &config)
{
}

void SampleTask::Executive()
{
    std::cout << "SampleTask is running..." << std::endl;
}

void SampleTask::Clean()
{
}

string SampleTask::GetConfigFileName() const
{
    return SAMPLE_TASK_CONFIG_FILENAME;
}
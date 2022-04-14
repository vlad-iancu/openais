#include <SampleTask.hpp>
#include <Interface/InterfaceDB.hpp>

#include <iostream>

using Task = openais::task::Task;
using SampleTask = openais::task::SampleTask;
using Config = openais::task::Config;
using string = std::string;
using namespace openais;

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
    std::cout << "Initializing logger..." << std::endl;
    logger = interface::InterfaceDB::GetInterface<interfaces::OutputLoggerInterface>("Logger");
    std::cout << "Initialized logger" << std::endl;
}

void SampleTask::Executive()
{
    logger->Publish("Logging from SampleTask");
}

void SampleTask::Clean()
{
}

string SampleTask::GetConfigFileName() const
{
    return SAMPLE_TASK_CONFIG_FILENAME;
}
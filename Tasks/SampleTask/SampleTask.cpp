#include <SampleTask.hpp>
#include <Interface/InterfaceDB.hpp>
#include <boost/lexical_cast.hpp>
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
    std::cout << "Entered init" << std::endl;
    logger = interface::InterfaceDB::GetInterface<interface::OutputInterface<string>>("Logger");
    if(logger != nullptr)
    std::cout << "Got Logger" << std::endl;
    numberProvider = interface::InterfaceDB::GetInterface<interface::InputInterface<string>>("NumberProvider");
    std::cout << "Got Counter" << std::endl;

    numberProvider->SetCallback(std::bind(&SampleTask::PublishNumber, this, std::placeholders::_1));
    std::cout << "Starting Logger" << std::endl;
    logger->Start();
    std::cout << "Started Logger" << std::endl;
    numberProvider->Start();
    std::cout << "Started Counter" << std::endl;
    std::cout << "Finished init" << std::endl;
}

void SampleTask::PublishNumber(string n)
{
    std::scoped_lock<std::mutex> lk(mtx);
    logger->Publish(n);
}

void SampleTask::Executive()
{
    PublishNumber("0");
}

void SampleTask::Clean()
{
}

string SampleTask::GetConfigFileName() const
{
    return SAMPLE_TASK_CONFIG_FILENAME;
}
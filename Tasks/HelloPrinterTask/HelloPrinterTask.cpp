#include <HelloPrinterTask.hpp>
#include <Interface/InterfaceDB.hpp>
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
    outputInterface = interface::InterfaceDB::GetInterface<OutputInterface<Person>>("PersonOutput");
}

void HelloPrinterTask::Executive()
{
    Person person;
    person.set_age(20);
    person.set_name("John");
    person.set_id(1);
    outputInterface->Publish(person);
    
    //std::cout << "HelloPrinterTask is running..." << std::endl;
}

void HelloPrinterTask::Clean()
{
}

std::string HelloPrinterTask::GetName() const
{
    return "HelloPrinterTask";
}
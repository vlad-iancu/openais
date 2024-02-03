#include <Task/PeriodicTask.hpp>
#include <Task/Component.hpp>
#include <chrono>

using namespace openais::task;

void PeriodicTask::Run()
{
    //Make this execute components once in a while
    SetActive(true);
    uint64_t sleep_time_micro = mFrequencyHz ? (uint64_t)((double)(1E6 / mFrequencyHz)) : 0;
    for(int i = 0; i < Component::GetCounter(); i++)
    {
        Component::GetComponent(i)->Start();
        uint64_t component_sleep_time_micro = Component::GetComponent(i)->GetFrequency() ? (uint64_t)((double)(1E6 / Component::GetComponent(i)->GetFrequency())) : 0;
        mComponentThreads.push_back(std::thread([=]() {
            Component *component = Component::GetComponent(i);
            while (component->IsActive())
            {
                Component::GetComponent(i)->Execute();
                std::this_thread::sleep_for(std::chrono::microseconds(component_sleep_time_micro));
            }
            Component::GetComponent(i)->Stop();
        }));
        
    }
    while (IsActive())
    {
        if(!IsPaused())
        {
            Executive();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_time_micro));
    }
    SetActive(false);
}

double PeriodicTask::GetFrequency() const 
{
    return mFrequencyHz;
}

void PeriodicTask::SetFrequency(double frequency)
{
    mFrequencyHz = frequency;
}

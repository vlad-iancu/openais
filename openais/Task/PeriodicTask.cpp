#include <Task/PeriodicTask.hpp>

#include <chrono>
#include <thread>

using namespace openais::task;

void PeriodicTask::Run()
{
    SetActive(true);
    uint64_t sleep_time_micro = m_frequencyHz ? (uint64_t)((double)(1E6 / m_frequencyHz)) : 0;
    while (IsActive())
    {
        Executive();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_time_micro));
    }
    SetActive(false);
}

double PeriodicTask::GetFrequency() const 
{
    return m_frequencyHz;
}

void PeriodicTask::SetFrequency(double frequency)
{
    m_frequencyHz = frequency;
}
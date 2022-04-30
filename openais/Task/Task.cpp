#include <Task/Task.hpp>

#include <thread>
#include <chrono>

using namespace openais::task;

Task *Task::task;

void Task::Run(double frequency_hz)
{
    SetActive(true);
    uint64_t sleep_time_micro = frequency_hz ? (uint64_t)((double)(1E6 / frequency_hz)) : 0;
    while(m_active)
    {
        Executive();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_time_micro));
    }
}

void Task::Stop()
{
    SetActive(false);
}

bool Task::IsActive() const
{
    return m_active;
}

void Task::SetActive(bool active)
{
    m_active = active;
}

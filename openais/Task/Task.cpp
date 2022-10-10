#include <Task/Task.hpp>

#include <thread>
#include <chrono>

using namespace openais::task;

Task *Task::task;

void Task::Stop()
{
    SetActive(false);
}

void Task::Pause()
{
    m_paused = true;
}

bool Task::IsPaused() const
{
    return m_paused;
}

void Task::Resume()
{
    m_paused = false;
}

bool Task::IsActive() const
{
    return m_active;
}

void Task::SetActive(bool active)
{
    m_active = active;
}

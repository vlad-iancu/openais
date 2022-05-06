#include <Task/ContinualTask.hpp>

using namespace openais::task;

void ContinualTask::Run()
{
    SetActive(true);
    Executive();
    SetActive(false);
}
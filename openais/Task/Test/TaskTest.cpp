#include <Task/Task.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <thread>
#include <future>
#include <functional>
#include <chrono>

using namespace openais::task;
using testing::NiceMock;

class TaskMock : public Task
{
public:
    Task *Clone() const override
    {
        return new TaskMock(*this);
    }

    MOCK_METHOD((void), Initialize, (const Config&), (override));

    MOCK_METHOD((void), Executive, (), (override));
    
    MOCK_METHOD((void), Clean, (), (override));

    string GetConfigFileName() const override
    {
        return "TestConfigFile";
    }

public:
    TaskMock() {}
    TaskMock(const TaskMock &other) {}
};

TEST(TaskTest, Run)
{
    using testing::Eq;
    using testing::AnyNumber;

    NiceMock<TaskMock> mockTask;
    EXPECT_CALL(mockTask, Executive()).Times(AnyNumber());

    std::future<void> taskFuture = std::async(std::bind(&TaskMock::Run, &mockTask, 0));
    std::this_thread::sleep_for(std::chrono::microseconds(5)); //Acceptable
    
    EXPECT_THAT(mockTask.IsActive(), Eq(true));
    mockTask.Stop();
    EXPECT_THAT(mockTask.IsActive(), Eq(false));
    taskFuture.get();
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <thread>
#include <future>
#include <functional>
#include <chrono>

#define private public
#define protected public
#include <Task/Task.hpp>
#include <Task/PeriodicTask.hpp>
#include <Task/ContinualTask.hpp>

#undef private
#undef protected

using namespace openais::task;
using testing::NiceMock;

class PeriodicTaskMock : public PeriodicTask
{
public:
    Task *Clone() const override
    {
        return new PeriodicTaskMock(*this);
    }

    MOCK_METHOD((void), Initialize, (const Config &), (override));

    MOCK_METHOD((void), Executive, (), (override));

    MOCK_METHOD((void), Clean, (), (override));

    std::string GetConfigFileName() const override
    {
        return "TestConfigFile";
    }

public:
    PeriodicTaskMock() {}
    PeriodicTaskMock(const PeriodicTaskMock &other) {}
};

class ContinualTaskMock : public ContinualTask
{
public:
    Task *Clone() const override
    {
        return new ContinualTaskMock(*this);
    }

    MOCK_METHOD((void), Initialize, (const Config &), (override));

    MOCK_METHOD((void), Executive, (), (override));

    MOCK_METHOD((void), Clean, (), (override));

    MOCK_METHOD((void), SetActive, (bool));

    std::string GetConfigFileName() const override
    {
        return "TestConfigFile";
    }

public:
    ContinualTaskMock() {}
    ContinualTaskMock(const ContinualTaskMock &other) {}
};

TEST(TaskTest, PeriodicTaskRun)
{
    using testing::AnyNumber;
    using testing::Eq;

    NiceMock<PeriodicTaskMock> mockTask;

    EXPECT_CALL(mockTask, Executive()).Times(AnyNumber());

    std::future<void> taskFuture = std::async(std::bind(&PeriodicTaskMock::Run, &mockTask));
    std::this_thread::sleep_for(std::chrono::microseconds(5)); // Acceptable

    EXPECT_THAT(mockTask.IsActive(), Eq(true));
    mockTask.Stop();
    EXPECT_THAT(mockTask.IsActive(), Eq(false));
    taskFuture.get();
}

TEST(TaskTest, ContinualTaskRun)
{
    using testing::Eq;
    NiceMock<ContinualTaskMock> mockTask;
    ON_CALL(mockTask, SetActive).WillByDefault([&mockTask](bool active) 
    {
        mockTask.ContinualTask::SetActive(active);
    });

    mockTask.Run();
    EXPECT_THAT(mockTask.IsActive(), Eq(false));
    mockTask.Stop();
}
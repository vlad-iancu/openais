#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Time/Time.hpp>

#include <chrono>

TEST(Time, Now)
{
    using namespace openais::time;

    using testing::Le;

    TimeStamp chronoNow = std::chrono::system_clock::now()
                              .time_since_epoch()
                              .count();

    TimeStamp openaisNow = Time::Now();

    EXPECT_THAT(std::abs(chronoNow - openaisNow), Le(Time::Microseconds(10)));
}

TEST(Time, SingleTimerSleep)
{
    using namespace openais::time;

    using testing::Le;

    TimeStamp start = std::chrono::system_clock::now()
                          .time_since_epoch()
                          .count();

    Time::MoveTimeForward(Time::Seconds(1));
    Time::Sleep(Time::Milliseconds(5));
    TimeStamp end = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    EXPECT_THAT(end - start, Le(Time::Microseconds(10)));
}

TEST(Time, MultipleTimerSleep)
{
    using namespace openais::time;

    using testing::Le;

    Time::MoveTimeForward(Time::Seconds(5));

    TimeStamp start;
    TimeStamp end;

    start = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();
    Time::Sleep(Time::Seconds(4));
    end = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();
    EXPECT_THAT(end - start, Le(Time::Milliseconds(5)));

    start = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();
    Time::Sleep(Time::Seconds(4));
    end = std::chrono::system_clock::now()
                .time_since_epoch()
                .count();
    EXPECT_THAT(end - start, Le(Time::Milliseconds(5)));
}
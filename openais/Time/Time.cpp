#include <Time/Time.hpp>

#include <thread>

using namespace openais::time;

TimeStamp Time::present;

TimeStamp Time::GetPresentTime()
{
    using namespace std::chrono;
    TimeStamp ns = duration_cast<nanoseconds>(Clock::now().time_since_epoch()).count();
    return ns;
}

TimeStamp Time::Now()
{
    return std::max(GetPresentTime(), present);
}

void Time::Sleep(TimeVal time)
{
    //Done this way so that if there is no MoveTimeForward call sleepTime should be zero and sleep_for call would be ignored
    TimeStamp now = GetPresentTime();
    TimeStamp present = std::max(Now(), now);
    TimeVal sleepTime = time - (present - now);
    std::this_thread::sleep_for(std::chrono::nanoseconds(sleepTime));
}

void Time::MoveTimeForward(TimeVal time)
{
    present = std::max(GetPresentTime(), Now()) + time;
}

TimeVal Time::Nanoseconds(TimeVal nanos)
{
    return nanos;
}

TimeVal Time::Microseconds(TimeVal micros)
{
    return micros * 1E3;
}

TimeVal Time::Milliseconds(TimeVal millis)
{
    return 1E3 * Microseconds(millis);
}

TimeVal Time::Seconds(TimeVal seconds)
{
    return 1E3 * Milliseconds(seconds);
}

TimeVal Time::Minutes(TimeVal mins)
{
    return 60 * Seconds(mins);
}

TimeVal Time::Hours(TimeVal hours)
{
    return 60 * Minutes(hours);
}
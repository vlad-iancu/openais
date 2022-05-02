#ifndef OPENAIS_TIME_TIME_H
#define OPENAIS_TIME_TIME_H

#include <cstdint>
#include <chrono>

namespace openais
{
    namespace time
    {
        using TimeVal = int64_t;
        using TimeStamp = int64_t;
        using Clock = std::chrono::system_clock;

        class Time
        {
        private:
            static TimeStamp present;

        public:
            static TimeStamp Now();
            static void MoveTimeForward(TimeVal time);
            static TimeStamp GetPresentTime();
            static void Sleep(TimeVal time);
            
        public:
            static TimeVal Nanoseconds(TimeVal nanos);
            static TimeVal Microseconds(TimeVal micros);
            static TimeVal Milliseconds(TimeVal millis);
            static TimeVal Seconds(TimeVal seconds);
            static TimeVal Minutes(TimeVal mins);
            static TimeVal Hours(TimeVal hours);
        };

    } // namespace time

} // namespace openais

#endif
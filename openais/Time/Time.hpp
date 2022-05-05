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
            /**
             * @brief Retrieves the current time taking into account forward time movings
             * You should use this method instead of GetPresentTime if you want MoveTimeForward calls to take effect
             * 
             * @return TimeStamp 
             */
            static TimeStamp Now();

            /**
             * @brief Advances the current time
             * 
             * @param time 
             */
            static void MoveTimeForward(TimeVal time);

            /**
             * @brief Gets the number of nanoseconds since Unix epoch
             * 
             * @return TimeStamp 
             */
            static TimeStamp GetPresentTime();

            /**
             * @brief Sleeps for the provided number of nanoseconds
             * This method takes into account MoveTimeForward calls
             * 
             * @param time 
             */
            static void Sleep(TimeVal time);
            
        public:
            /**
             * @brief Just a convenience method to point out that the value passed as parameter
             * represents nanoseconds
             * 
             * @param nanos 
             * @return TimeVal 
             */
            static TimeVal Nanoseconds(TimeVal nanos);

            /**
             * @brief Converts microseconds to nanoseconds
             * 
             * @param micros 
             * @return TimeVal 
             */
            static TimeVal Microseconds(TimeVal micros);

            /**
             * @brief Converts milliseconds to nanoseconds
             * 
             * @param millis 
             * @return TimeVal 
             */
            static TimeVal Milliseconds(TimeVal millis);

            /**
             * @brief Converts seconds to nanoseconds
             * 
             * @param seconds 
             * @return TimeVal 
             */
            static TimeVal Seconds(TimeVal seconds);

            /**
             * @brief Converts minutes to nanoseconds
             * 
             * @param mins 
             * @return TimeVal 
             */
            static TimeVal Minutes(TimeVal mins);

            /**
             * @brief Converts hours to nanoseconds
             * 
             * @param hours 
             * @return TimeVal 
             */
            static TimeVal Hours(TimeVal hours);
        };

    } // namespace time

} // namespace openais

#endif
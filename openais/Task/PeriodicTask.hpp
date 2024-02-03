#ifndef OPENAIS_TASK_PERIODICTASK_H
#define OPENAIS_TASK_PERIODICTASK_H

#include <Task/Task.hpp>
#include <thread>

#include <list>
namespace openais
{
    namespace task
    {
        /**
         * @brief A task that has a periodic execution
         * 
         */
        class PeriodicTask : public Task
        {
        protected:
            double mFrequencyHz;
            std::list<std::thread> mComponentThreads;

        public:
            void Run() override;
        
        public:
            /**
             * @brief Get the frequency at which Executive is run
             * 
             * @return double
             */
            double GetFrequency() const;
            
            /**
             * @brief Sets the frequency at which Executive is run
             * 
             */
            void SetFrequency(double frequency);
        };
    } // namespace task

} // namespace openais

#endif
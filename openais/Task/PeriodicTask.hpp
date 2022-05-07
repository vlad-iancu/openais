#ifndef OPENAIS_TASK_PERIODICTASK_H
#define OPENAIS_TASK_PERIODICTASK_H

#include <Task/Task.hpp>

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
            double m_frequencyHz;

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
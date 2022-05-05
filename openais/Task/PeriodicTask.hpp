#ifndef OPENAIS_TASK_PERIODICTASK_H
#define OPENAIS_TASK_PERIODICTASK_H

#include <Task/Task.hpp>

namespace openais
{
    namespace task
    {
        class PeriodicTask : public Task
        {
        protected:
            double m_frequencyHz;

        public:
            void Run() override;
        
        public:
            double GetFrequency() const;
            void SetFrequency(double frequency);
        };
    } // namespace task

} // namespace openais

#endif
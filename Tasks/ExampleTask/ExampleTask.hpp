#ifndef EXAMPLE_TASK_H
#define EXAMPLE_TASK_H

#include <Task/PeriodicTask.hpp>

namespace openais
{
    namespace task
    {
        class ExampleTask : PeriodicTask
        {
        private:
            static ExampleTask _task;

        public:
            Task *Clone() const override;
            void Initialize(const Config &config) override;
            void Executive() override;
            void Clean() override;
            std::string GetName() const override;

        public:
            ExampleTask();
            ExampleTask(const ExampleTask &other) {}

        private:
            std::string m_printStr;
        };

    } // namespace task

} // namespace openais

#endif

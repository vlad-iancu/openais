#ifndef SOME_TASK_H
#define SOME_TASK_H

#include <Task/PeriodicTask.hpp>

#ifndef SAMPLE_TASK_CONFIG_FILENAME
#define SAMPLE_TASK_CONFIG_FILENAME "config.py"
#endif

namespace openais
{
    namespace task
    {
        class SomeTask : PeriodicTask
        {
        private:
            static SomeTask _task;

        public:
            Task *Clone() const override;
            void Initialize(const Config &config) override;
            void Executive() override;
            void Clean() override;
            std::string GetName() const override;

        public:
            SomeTask();
            SomeTask(const SomeTask &other) {}
        };

    } // namespace task

} // namespace openais

#endif

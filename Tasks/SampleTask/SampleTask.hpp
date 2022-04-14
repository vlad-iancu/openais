#ifndef SAMPLE_TASK_H
#define SAMPLE_TASK_H

#include <Task/Task.hpp>
#include <OutputLoggerInterface.hpp>

#ifndef SAMPLE_TASK_CONFIG_FILENAME
#define SAMPLE_TASK_CONFIG_FILENAME "config.json"
#endif
namespace openais
{
    namespace task
    {
        class SampleTask : Task
        {
        private:
            static SampleTask _task;
            interfaces::OutputLoggerInterface *logger;

        public:
            Task *Clone() const override;
            void Initialize(const Config &config) override;
            void Executive() override;
            void Clean() override;
            string GetConfigFileName() const override;

        public:
            SampleTask();
            SampleTask(const SampleTask &other) {}
        };

    } // namespace task

} // namespace openais

#endif
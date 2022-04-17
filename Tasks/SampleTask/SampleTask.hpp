#ifndef SAMPLE_TASK_H
#define SAMPLE_TASK_H

#include <Task/Task.hpp>
#include <Interface/OutputInterface.hpp>
#include <Interface/InputInterface.hpp>

#include <mutex>

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
            openais::interface::OutputInterface<string> *logger;
            openais::interface::InputInterface<string> *numberProvider;
            std::mutex mtx;

        private:
            void PublishNumber(string n);

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
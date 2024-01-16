
#ifndef HELLOPRINTER_TASK_H
#define HELLOPRINTER_TASK_H

#include <Task/PeriodicTask.hpp>


#ifndef HELLOPRINTER_TASK_CONFIG_FILENAME
#define HELLOPRINTER_TASK_CONFIG_FILENAME "config.py"
#endif

namespace openais
{
    namespace task
    {
        class HelloPrinterTask : PeriodicTask
        {
        private:
            static HelloPrinterTask _task;

        public:
            Task *Clone() const override;
            void Initialize(const Config &config) override;
            void Executive() override;
            void Clean() override;
            std::string GetName() const override;

        public:
            HelloPrinterTask();
            HelloPrinterTask(const HelloPrinterTask &other) {}
        };

    } // namespace task

} // namespace openais

#endif

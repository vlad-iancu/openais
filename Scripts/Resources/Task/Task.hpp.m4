define(HEADER_GUARD, translit(taskName, `a-z', `A-Z')`_TASK_H')dnl
define(SampleTask, taskName`Task')dnl
define(SAMPLE_TASK_CONFIG_FILENAME, translit(taskName, `a-z', `A-Z')`_TASK_CONFIG_FILENAME')dnl
`#ifndef' HEADER_GUARD
`#define' HEADER_GUARD

`#include' <Task/Task.hpp>


`#ifndef' SAMPLE_TASK_CONFIG_FILENAME
`#define' SAMPLE_TASK_CONFIG_FILENAME "config.json"
`#endif'

namespace openais
{
    namespace task
    {
        class SampleTask : Task
        {
        private:
            static SampleTask _task;

        public:
            Task *Clone() const override;
            void Initialize(const Config &config) override;
            void Executive() override;
            void Clean() override;
            string GetConfigFileName() const override;

        public:
            SampleTask`()';
            SampleTask`(const' SampleTask `&other)' {}
        };

    } // namespace task

} // namespace openais

`#endif'

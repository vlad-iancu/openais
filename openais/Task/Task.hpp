#ifndef OPENAIS_TASK_H
#define OPENAIS_TASK_H

#include <Task/Config.hpp>

namespace openais
{
    namespace task
    {
        class Task
        {
        public:
            static Task *task;

        public:
            virtual Task *Clone() const = 0;
            virtual void Initialize(const Config &config) = 0;
            virtual void Executive() = 0;
            virtual void Clean() = 0;
            virtual string GetConfigFileName() const = 0;
        };
    } // namespace task

} // namespace openais

#endif
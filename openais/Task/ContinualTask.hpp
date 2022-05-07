#ifndef OPENAIS_TASK_CONTINUALTASK_H
#define OPENAIS_TASK_CONTINUALTASK_H

#include <Task/Task.hpp>

namespace openais
{
    namespace task
    {
        /**
         * @brief A task that has a linear one-time execution
         * 
         */
        class ContinualTask : public Task
        {
        public:
            /**
             * @brief Runs the Executive method one time
             * 
             */
            void Run() override;
        };
    } // namespace task

} // namespace openais

#endif
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
            /**
             * @brief Self-registering prototype
             * 
             */
            static Task *task;

        public:
            /**
             * @brief Clones the current Task object
             *
             * @return Task* 
             */
            virtual Task *Clone() const = 0;

            /**
             * @brief Initializes the Task
             * This method usually initalizes the Interface members of the task
             * and aquires the resources that will be used 
             * 
             * @param config The JSON configuration parameters declared in the `config` 
             * member of the `config.json` of this Task
             */
            virtual void Initialize(const Config &config) = 0;

            /**
             * @brief Defines what the task does
             * This method will be periodically executed at `(1 / frequency_hz) seconds`
             * 
             */
            virtual void Executive() = 0;

            /**
             * @brief Deinitializes the task. This method is responsible with freeing
             * the resources aquired by the Task in `Initialize`
             * 
             */
            virtual void Clean() = 0;
            
            /**
             * @brief Get the name of the configuration file. to be
             * passed to `Initialize`.
             * This method is auto-generated,
             * 
             * @return string 
             */
            virtual string GetConfigFileName() const = 0;
        };
    } // namespace task

} // namespace openais

#endif
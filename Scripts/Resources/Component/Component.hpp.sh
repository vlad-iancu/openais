#!/bin/bash
COMPONENT=$1
TASK=$2Task
CLASS=${COMPONENT}Component
HEADER_GUARD=OPENAIS_`echo $COMPONENT | tr '[:lower:]' '[:upper:]'`_COMPONENT_H

if [ -z "$COMPONENT" ]; then
    echo "Component name is required"
    exit 1
fi
if [ -z "$TASK" ]; then
    echo "Task name is required"
    exit 1
fi
cat << EOF

#ifndef $HEADER_GUARD
#define $HEADER_GUARD

#include <Task/Component.hpp>
#include "../../$TASK.hpp"

namespace openais::task {
    class $CLASS : public Component {
    private:
        $CLASS();
        static $CLASS _instance;
        $TASK *mTask = ($TASK *)Task::task;

    public:
        $CLASS(const $CLASS &other) = default;
        virtual ~$CLASS();
        virtual void Initialize(const Config &config);
        virtual void Start();
        virtual void Stop();
        virtual void Execute();
        virtual std::string GetName() const;
        virtual Component *Clone() const;
    };
}

#endif

EOF
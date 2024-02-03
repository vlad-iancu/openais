#!/bin/bash
COMPONENT=$1
TASK=$2

SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Component
TASK_DIR=$PROJECT_DIR/Tasks/${TASK}Task


if [ -z "$COMPONENT" ]; then
    echo "Component name is required"
    exit 1
fi

if [ -z "$TASK" ]; then
    echo "Task name is required"
    exit 1
fi

mkdir -p ${TASK_DIR}/Components/${COMPONENT}

$RESOURCES/CMakeLists.txt.sh $@ > ${TASK_DIR}/Components/${COMPONENT}/CMakeLists.txt
$RESOURCES/Component.hpp.sh $@ > ${TASK_DIR}/Components/${COMPONENT}/${COMPONENT}Component.hpp
$RESOURCES/Component.cpp.sh $@ > ${TASK_DIR}/Components/${COMPONENT}/${COMPONENT}Component.cpp
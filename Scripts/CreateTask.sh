#!/bin/bash
if [ "$1" = "--help" ] || [ "$1" = "" ]; then
    echo "usage Scripts/CreateTask.sh <TaskName> <TaskType>"
    echo "TaskType: Periodic, Continual"
    exit 0
fi

if [ "$2" = "" ]; then
    echo "usage Scripts/CreateTask.sh <TaskName> <TaskType>"
    echo "TaskType: Periodic, Continual"
    exit 0
fi

SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Task
TASK_DIR=$PROJECT_DIR/Tasks/$1Task
TASK_NAME=$1
TASK_TYPE=$2

mkdir -p ${TASK_DIR}/Test
mkdir -p ${TASK_DIR}/Components

$RESOURCES/CMakeLists.txt.sh $@ > ${TASK_DIR}/CMakeLists.txt
$RESOURCES/Task.hpp.sh $@ > ${TASK_DIR}/${TASK_NAME}Task.hpp
$RESOURCES/Task.cpp.sh $@ > ${TASK_DIR}/${TASK_NAME}Task.cpp
$RESOURCES/TaskTest.cpp.sh $@ > ${TASK_DIR}/Test/${TASK_NAME}TaskTest.cpp
$RESOURCES/CMakeLists.txt.Test.sh $@ > ${TASK_DIR}/Test/CMakeLists.txt
$RESOURCES/CMakeLists.txt.Components.sh $@ > ${TASK_DIR}/Components/CMakeLists.txt

cp ${RESOURCES}/${TASK_TYPE}TaskConfig.py ${TASK_DIR}/config.py

#usage Scripts/CreateTask.sh Example Periodic
#usage Scripts/CreateTask.sh Example Continual

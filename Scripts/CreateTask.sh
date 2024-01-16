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

echo "Creating Task $1 of type $2"

SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Task
TASK_DIR=$PROJECT_DIR/Tasks/$1Task
TASK_NAME=$1
TASK_TYPE=$2
mkdir -p ${TASK_DIR}/Test

m4 --define=taskName=$TASK_NAME ${RESOURCES}/CMakeLists.txt.m4 > ${TASK_DIR}/CMakeLists.txt
m4 --define=taskName=$TASK_NAME --define=taskType=${TASK_TYPE} ${RESOURCES}/Task.hpp.m4 > ${TASK_DIR}/${TASK_NAME}Task.hpp
m4 --define=taskName=$TASK_NAME ${RESOURCES}/Task.cpp.m4 > ${TASK_DIR}/${TASK_NAME}Task.cpp
m4 --define=taskName=$TASK_NAME ${RESOURCES}/TaskTest.cpp.m4 > ${TASK_DIR}/Test/${TASK_NAME}TaskTest.cpp
m4 --define=taskName=$TASK_NAME ${RESOURCES}/CMakeLists.txt.Test.m4 > ${TASK_DIR}/Test/CMakeLists.txt

cp ${RESOURCES}/${TASK_TYPE}TaskConfig.py ${TASK_DIR}/config.py
echo "Created Task $1 of type $2"
#usage Scripts/CreateTask.sh Example Periodic
#usage Scripts/CreateTask.sh Example Continual

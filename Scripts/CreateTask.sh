SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Task
TASK_DIR=$PROJECT_DIR/Tasks/$1Task

mkdir -p ${TASK_DIR}/Test

m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.m4 > ${TASK_DIR}/CMakeLists.txt
m4 --define=taskName=$1 --define=TaskType=$2 ${RESOURCES}/Task.hpp.m4 > ${TASK_DIR}/$1Task.hpp
m4 --define=taskName=$1 ${RESOURCES}/Task.cpp.m4 > ${TASK_DIR}/$1Task.cpp
m4 --define=taskName=$1 ${RESOURCES}/TaskTest.cpp.m4 > ${TASK_DIR}/Test/$1TaskTest.cpp
m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.Test.m4 > ${TASK_DIR}/Test/CMakeLists.txt

cp ${RESOURCES}/$2Config.json ${TASK_DIR}/config.json

#usage Scripts/CreateTask Example PeriodicTask
#usage Scripts/CreateTask Example ContinualTask
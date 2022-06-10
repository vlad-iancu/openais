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

#usage Scripts/CreateTask Example Periodic
#usage Scripts/CreateTask Example Continual

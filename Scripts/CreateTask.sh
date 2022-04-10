SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Task
TASK_DIR=$PROJECT_DIR/Tasks/$1Task

mkdir -p ${TASK_DIR}

m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.m4 > ${TASK_DIR}/CMakeLists.txt
m4 --define=taskName=$1 ${RESOURCES}/Task.hpp.m4 > ${TASK_DIR}/$1Task.hpp
m4 --define=taskName=$1 ${RESOURCES}/Task.cpp.m4> ${TASK_DIR}/$1Task.cpp

cp ${RESOURCES}/config.json ${TASK_DIR}/config.json

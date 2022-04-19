SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Task
TASK_DIR=$PROJECT_DIR/Tasks/$1Task

mkdir -p ${TASK_DIR}/Test

echo "created dirs"
echo "m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.m4 > ${TASK_DIR}/CMakeLists.txt"
m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.m4 > ${TASK_DIR}/CMakeLists.txt
echo "created CMakeLists.txt"
m4 --define=taskName=$1 ${RESOURCES}/Task.hpp.m4 > ${TASK_DIR}/$1Task.hpp
echo "created header"
m4 --define=taskName=$1 ${RESOURCES}/Task.cpp.m4 > ${TASK_DIR}/$1Task.cpp
echo "created source"
m4 --define=taskName=$1 ${RESOURCES}/TaskTest.cpp.m4 > ${TASK_DIR}/Test/$1TaskTest.cpp
echo "created test"
m4 --define=taskName=$1 ${RESOURCES}/CMakeLists.txt.Test.m4 > ${TASK_DIR}/Test/CMakeLists.txt
echo "created Test/CMakeLists.txt"

cp ${RESOURCES}/config.json ${TASK_DIR}/config.json

SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_NAME=$1
INTERFACE_TYPE=$2
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Output${INTERFACE_NAME}Interface

mkdir -p ${INTERFACE_DIR}

m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/CMakeLists.txt.Output.m4 > ${INTERFACE_DIR}/CMakeLists.txt
m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/OutputInterface.hpp.m4 > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.hpp
m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/OutputInterface.cpp.m4 > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.cpp
SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Input${INTERFACE_NAME}Interface

mkdir -p ${INTERFACE_DIR}

m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/CMakeLists.txt.Input.m4 > ${INTERFACE_DIR}/CMakeLists.txt
m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/InputInterface.hpp.m4 > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.hpp
m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/InputInterface.cpp.m4 > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.cpp
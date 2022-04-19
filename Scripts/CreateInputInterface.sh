SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Input$1Interface

mkdir -p ${INTERFACE_DIR}

m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/CMakeLists.txt.Input.m4 > ${INTERFACE_DIR}/CMakeLists.txt
m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/InputInterface.hpp.m4 > ${INTERFACE_DIR}/Input$1Interface.hpp
m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/InputInterface.cpp.m4 > ${INTERFACE_DIR}/Input$1Interface.cpp
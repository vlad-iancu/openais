SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Output$1Interface

mkdir -p ${INTERFACE_DIR}

m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/CMakeLists.txt.Output.m4 > ${INTERFACE_DIR}/CMakeLists.txt
m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/OutputInterface.hpp.m4 > ${INTERFACE_DIR}/Output$1Interface.hpp
m4 --define=interfaceName=$1 --define=interfaceType=$2 ${RESOURCES}/OutputInterface.cpp.m4 > ${INTERFACE_DIR}/Output$1Interface.cpp
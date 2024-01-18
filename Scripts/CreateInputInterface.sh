#!/bin/bash
SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_NAME=$1
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Input${INTERFACE_NAME}Interface

mkdir -p ${INTERFACE_DIR}

#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/CMakeLists.txt.Input.m4 > ${INTERFACE_DIR}/CMakeLists.txt
#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/InputInterface.hpp.m4 > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.hpp
#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$2 ${RESOURCES}/InputInterface.cpp.m4 > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.cpp

interfaceType=$2
#Create CMakeLists.txt
TargetName=Input$1Interface
cat > ${INTERFACE_DIR}/CMakeLists.txt << EOF
add_library($TargetName STATIC $TargetName.cpp)
target_include_directories($TargetName PUBLIC \${CMAKE_CURRENT_SOURCE_DIR} \${CMAKE_SOURCE_DIR}/openais \${CMAKE_SOURCE_DIR}/Serialization)
set_target_properties($TargetName PROPERTIES ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/Lib)
target_link_libraries($TargetName PRIVATE ${interfaceType})
EOF

#Create Interface.hpp
NAME=$(echo $1 | tr '[:upper:]' '[:lower:]')
HEADER_GUARD="OPENAIS_INPUT_"$NAME"_INTERFACE_H"
ClassName="Input"$1"Interface"
cat > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.hpp << EOF

#ifndef $HEADER_GUARD
#define $HEADER_GUARD

#include <Interface/InputInterface.hpp>
#include <$interfaceType/$interfaceType.pb.h>
#include <string>

namespace openais 
{
    namespace interfaces
    {
        class $ClassName : public interface::InputInterface<$interfaceType>
        {
            private:
                static $ClassName _interface;
                $ClassName();
                $ClassName(const $ClassName &other);
            
            public:
                std::string GetInterfaceName() const override;
                interface::Interface *Clone() const override;
                bool Start() override;
                bool Stop() override;
        };
    } //namespace interfaces

} //namespace openais

#endif

EOF

#Create Interface.cpp
cat > ${INTERFACE_DIR}/Input${INTERFACE_NAME}Interface.cpp << EOF
#include <$ClassName.hpp>
#include <chrono>
using namespace openais::interfaces;

$ClassName $ClassName::_interface;

$ClassName::$ClassName()
{
    openais::interface::Interface::RegisterInterface(this);
}

$ClassName::$ClassName(const $ClassName &other)
{
}

openais::interface::Interface *$ClassName::Clone() const
{
    return new $ClassName(*this);
}

std::string $ClassName::GetInterfaceName() const
{
    return "$interfaceName";
}

bool $ClassName::Start()
{
    SetActive(true);
    return true;
}

bool $ClassName::Stop()
{
    SetActive(false);
    return true;
}
EOF




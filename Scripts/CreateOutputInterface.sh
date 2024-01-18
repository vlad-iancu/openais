#!/bin/bash
SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
RESOURCES=$SCRIPTS/Resources/Interface
INTERFACE_NAME=$1
INTERFACE_TYPE=$2
INTERFACE_DIR=$PROJECT_DIR/Interfaces/Output${INTERFACE_NAME}Interface

mkdir -p ${INTERFACE_DIR}

#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/CMakeLists.txt.Output.m4 > ${INTERFACE_DIR}/CMakeLists.txt
#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/OutputInterface.hpp.m4 > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.hpp
#m4 --define=interfaceName=$INTERFACE_NAME --define=interfaceType=$INTERFACE_TYPE ${RESOURCES}/OutputInterface.cpp.m4 > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.cpp

ClassName="Output"$1"Interface"

#Create CMakeLists.txt
TargetName=Output$1Interface
interfaceType=$2
cat > ${INTERFACE_DIR}/CMakeLists.txt << EOF
add_library($TargetName STATIC $TargetName.cpp)
target_include_directories($TargetName PUBLIC \${CMAKE_CURRENT_SOURCE_DIR} \${CMAKE_SOURCE_DIR}/openais \${CMAKE_SOURCE_DIR}/Serialization)
set_target_properties($TargetName PROPERTIES ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/Lib)
target_link_libraries($TargetName PRIVATE ${interfaceType})
EOF

#Create OutputInterface.cpp
cat > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.cpp << EOF
#include <$ClassName.hpp>

using namespace openais::interfaces;

$ClassName $ClassName::_interface;

$ClassName::$ClassName()
{
    openais::interface::Interface::RegisterInterface(this);
}

$ClassName::$ClassName(const $ClassName &other)
{

}

void $ClassName::Publish(const $INTERFACE_TYPE &data)
{

}

std::string $ClassName::GetInterfaceName() const
{
    return "$INTERFACE_NAME";
}

openais::interface::Interface *$ClassName::Clone() const
{
    return new $ClassName(*this);
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

#Create OutputInterface.hpp
NAME=$(echo $1 | tr '[:upper:]' '[:lower:]')
HEADER_GUARD="OPENAIS_OUTPUT_"$NAME"_INTERFACE_H"
cat > ${INTERFACE_DIR}/Output${INTERFACE_NAME}Interface.hpp << EOF

#ifndef $HEADER_GUARD
#define $HEADER_GUARD

#include <Interface/OutputInterface.hpp>
#include <$interfaceType/$interfaceType.pb.h>
#include <string>

namespace openais 
{
    namespace interfaces
    {
        class $ClassName : public interface::OutputInterface<$interfaceType>
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
                void Publish(const $interfaceType &data) override;
        };
    } //namespace interfaces

} //namespace openais

#endif

EOF
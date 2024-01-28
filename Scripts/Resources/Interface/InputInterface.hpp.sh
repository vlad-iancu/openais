#!/bin/bash

interfaceType=$2
#Create CMakeLists.txt
TargetName=Input$1Interface

NAME=$(echo $1 | tr '[:upper:]' '[:lower:]')
HEADER_GUARD="OPENAIS_INPUT_"$NAME"_INTERFACE_H"
ClassName="Input"$1"Interface"
# echo "ClassName: $ClassName"
# echo "interfaceType: $interfaceType"
# exit 0
cat << EOF

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
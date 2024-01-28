#!/bin/bash

ClassName=Output$1Interface
interfaceType=$2

NAME=$(echo $1 | tr '[:upper:]' '[:lower:]')
HEADER_GUARD="OPENAIS_OUTPUT_"$NAME"_INTERFACE_H"
cat << EOF

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
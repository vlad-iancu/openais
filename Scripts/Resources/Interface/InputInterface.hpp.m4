define(NAME, translit(interfaceName, `a-z', `A-Z'))dnl
define(HEADER_GUARD, `OPENAIS_INPUT_'NAME`_INTERFACE_H')dnl
define(ClassName, ``Input'interfaceName`Interface'')dnl
`#ifndef' HEADER_GUARD
`#define' HEADER_GUARD

`#include <Interface/InputInterface.hpp>'

`#include <string>'

namespace openais 
{
    namespace interfaces
    {
        class ClassName : public interface::InputInterface<interfaceType>
        {
            private:
                static ClassName _interface;
                ClassName`()';
                ClassName`('const ClassName &other`)';
            
            public:
                std::string GetInterfaceName`()' const override;
                interface::Interface *Clone`()' const override;
                bool Start`()' override;
                bool Stop`()' override;
        };
    } //namespace interfaces

} //namespace openais

`#endif'
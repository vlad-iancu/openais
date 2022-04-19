define(NAME, translit(interfaceName, `a-z', `A-Z'))dnl
define(HEADER_GUARD, `OPENAIS_INTERFACE_OUTPUT'NAME`_H')dnl
define(ClassName, ``Output'interfaceName`Interface'')dnl
`#ifndef' HEADER_GUARD
`#define' HEADER_GUARD

`#include <Interface/OutputInterface.hpp>'

`#include <string>'

namespace openais
{
    namespace interfaces
    {
        class ClassName : public interface::OutputInterface<interfaceType>
        {
        private:
            static ClassName _interface;
            ClassName`()';
        
        public:
            void `Publish'(const interfaceType &data) override;
            std::string `GetInterfaceName'() const override;
            openais::interface::Interface *`Clone'() const override;
            bool Start`()';
            bool Stop`()';

        public:
            ClassName`('const ClassName &other`)';
        };
    } //namespace interfaces

} //namespace openais

`#endif'
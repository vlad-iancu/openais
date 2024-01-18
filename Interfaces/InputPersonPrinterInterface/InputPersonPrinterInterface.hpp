
#ifndef OPENAIS_INPUT_personprinter_INTERFACE_H
#define OPENAIS_INPUT_personprinter_INTERFACE_H

#include <Interface/InputInterface.hpp>
#include <Person/Person.pb.h>
#include <string>

namespace openais 
{
    namespace interfaces
    {
        class InputPersonPrinterInterface : public interface::InputInterface<Person>
        {
            private:
                static InputPersonPrinterInterface _interface;
                InputPersonPrinterInterface();
                InputPersonPrinterInterface(const InputPersonPrinterInterface &other);
            
            public:
                std::string GetInterfaceName() const override;
                interface::Interface *Clone() const override;
                bool Start() override;
                bool Stop() override;
        };
    } //namespace interfaces

} //namespace openais

#endif


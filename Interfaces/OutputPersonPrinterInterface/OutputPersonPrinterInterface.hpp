
#ifndef OPENAIS_OUTPUT_personprinter_INTERFACE_H
#define OPENAIS_OUTPUT_personprinter_INTERFACE_H

#include <Interface/OutputInterface.hpp>
#include <Person/Person.pb.h>
#include <string>

namespace openais 
{
    namespace interfaces
    {
        class OutputPersonPrinterInterface : public interface::OutputInterface<Person>
        {
            private:
                static OutputPersonPrinterInterface _interface;
                OutputPersonPrinterInterface();
                OutputPersonPrinterInterface(const OutputPersonPrinterInterface &other);
            
            public:
                std::string GetInterfaceName() const override;
                interface::Interface *Clone() const override;
                bool Start() override;
                bool Stop() override;
                void Publish(const Person &data) override;
        };
    } //namespace interfaces

} //namespace openais

#endif


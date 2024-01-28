
#ifndef OPENAIS_OUTPUT_something_INTERFACE_H
#define OPENAIS_OUTPUT_something_INTERFACE_H

#include <Interface/OutputInterface.hpp>
#include <Person/Person.pb.h>
#include <string>

namespace openais 
{
    namespace interfaces
    {
        class OutputSomethingInterface : public interface::OutputInterface<Person>
        {
            private:
                static OutputSomethingInterface _interface;
                OutputSomethingInterface();
                OutputSomethingInterface(const OutputSomethingInterface &other);
            
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


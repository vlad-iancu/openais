#ifndef OPENAIS_INPUT_NUMBERSTRINGPROVIDER_INTERFACE_H
#define OPENAIS_INPUT_NUMBERSTRINGPROVIDER_INTERFACE_H

#include <Interface/InputInterface.hpp>

#include <string>
#include <thread>

namespace openais 
{
    namespace interfaces
    {
        class InputNumberStringProviderInterface : public interface::InputInterface<std::string>
        {
            private:
                static InputNumberStringProviderInterface _interface;
                InputNumberStringProviderInterface();
                InputNumberStringProviderInterface(const InputNumberStringProviderInterface &other);
                std::thread m_counterThread;
                int m_counter;
                
            public:
                std::string GetInterfaceName() const override;
                interface::Interface *Clone() const override;
                bool Start() override;
                bool Stop() override;
        };
    } //namespace interfaces

} //namespace openais

#endif
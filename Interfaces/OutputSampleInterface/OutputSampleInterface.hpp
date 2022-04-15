#ifndef OPENAIS_INTERFACE_OUTPUTSAMPLE_H
#define OPENAIS_INTERFACE_OUTPUTSAMPLE_H

#include <Interface/OutputInterface.hpp>

#include <string>

namespace openais
{
    namespace interfaces
    {
        class OutputSampleInterface : public interface::OutputInterface<int>
        {
        private:
            static OutputSampleInterface _interface;
            OutputSampleInterface();
        
        public:
            void Publish(const int &data) override;
            std::string GetInterfaceName() const override;
            openais::interface::Interface *Clone() const override;

        public:
            OutputSampleInterface(const OutputSampleInterface &other);
        };
    } //namespace interfaces

} //namespace openais

#endif
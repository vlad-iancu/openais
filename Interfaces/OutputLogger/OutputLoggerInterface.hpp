#ifndef OPENAIS_INTERFACE_OUTPUTLOGGER_H
#define OPENAIS_INTERFACE_OUTPUTLOGGER_H

#include <Interface/OutputInterface.hpp>

#include <string>

namespace openais
{
    namespace interfaces
    {
        class OutputLoggerInterface : public interface::OutputInterface<std::string>
        {
        private:
            static OutputLoggerInterface _interface;
            OutputLoggerInterface();

        public:
            void Publish(const std::string &data) override;
            std::string GetInterfaceName() const override;
            openais::interface::Interface *Clone() const override;

        public:
            OutputLoggerInterface(const OutputLoggerInterface &other);
        };
    } // namespace interfaces

} // namespace openais

#endif
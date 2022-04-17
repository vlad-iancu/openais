#ifndef OPENAIS_INTERFACE_OUTPUTCONSOLELOGGER_H
#define OPENAIS_INTERFACE_OUTPUTCONSOLELOGGER_H

#include <Interface/OutputInterface.hpp>

#include <string>

namespace openais
{
    namespace interfaces
    {
        class OutputConsoleLoggerInterface : public interface::OutputInterface<std::string>
        {
        private:
            static OutputConsoleLoggerInterface _interface;
            OutputConsoleLoggerInterface();
        
        public:
            void Publish(const std::string &data) override;
            std::string GetInterfaceName() const override;
            openais::interface::Interface *Clone() const override;
            bool Start();
            bool Stop();

        public:
            OutputConsoleLoggerInterface(const OutputConsoleLoggerInterface &other);
        };
    } //namespace interfaces

} //namespace openais

#endif
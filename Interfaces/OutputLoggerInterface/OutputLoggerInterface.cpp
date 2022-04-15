#include <OutputLoggerInterface.hpp>
#include <iostream>

using namespace openais::interfaces;

OutputLoggerInterface OutputLoggerInterface::_interface;

OutputLoggerInterface::OutputLoggerInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

void OutputLoggerInterface::Publish(const std::string &data)
{
    std::cout << "[OutputLoggerInterface]: " << data << std::endl;
}

std::string OutputLoggerInterface::GetInterfaceName() const
{
    return "ConsoleLogger";
}

openais::interface::Interface *OutputLoggerInterface::Clone() const
{
    return new OutputLoggerInterface(*this);
}

OutputLoggerInterface::OutputLoggerInterface(const OutputLoggerInterface &other): openais::interface::OutputInterface<std::string>(other)
{

}


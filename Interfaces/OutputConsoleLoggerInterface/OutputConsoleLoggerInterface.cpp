#include<OutputConsoleLoggerInterface.hpp>

#include <iostream>

using namespace openais::interfaces;

OutputConsoleLoggerInterface OutputConsoleLoggerInterface::_interface;

OutputConsoleLoggerInterface::OutputConsoleLoggerInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

OutputConsoleLoggerInterface::OutputConsoleLoggerInterface(const OutputConsoleLoggerInterface &other)
{

}

void OutputConsoleLoggerInterface::Publish(const std::string &data)
{
    std::cout << data << std::endl;
}

std::string OutputConsoleLoggerInterface::GetInterfaceName() const
{
    return "ConsoleLogger";
}

openais::interface::Interface *OutputConsoleLoggerInterface::Clone() const
{
    return new OutputConsoleLoggerInterface(*this);
}

bool OutputConsoleLoggerInterface::Start()
{
    IsActive(true);
    return true;
}

bool OutputConsoleLoggerInterface::Stop()
{
    IsActive(false);
    return true;
}

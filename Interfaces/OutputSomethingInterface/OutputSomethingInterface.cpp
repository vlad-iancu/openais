#include <OutputSomethingInterface.hpp>

using namespace openais::interfaces;

OutputSomethingInterface OutputSomethingInterface::_interface;

OutputSomethingInterface::OutputSomethingInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

OutputSomethingInterface::OutputSomethingInterface(const OutputSomethingInterface &other)
{

}

void OutputSomethingInterface::Publish(const Person &data)
{

}

std::string OutputSomethingInterface::GetInterfaceName() const
{
    return "";
}

openais::interface::Interface *OutputSomethingInterface::Clone() const
{
    return new OutputSomethingInterface(*this);
}

bool OutputSomethingInterface::Start()
{
    SetActive(true);
    return true;
}

bool OutputSomethingInterface::Stop()
{
    SetActive(false);
    return true;
}

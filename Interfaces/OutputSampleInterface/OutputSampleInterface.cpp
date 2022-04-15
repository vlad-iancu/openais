#include<OutputSampleInterface.hpp>
#include<iostream>

using namespace openais::interfaces;

OutputSampleInterface OutputSampleInterface::_interface;

OutputSampleInterface::OutputSampleInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

OutputSampleInterface::OutputSampleInterface(const OutputSampleInterface &other)
{

}

void OutputSampleInterface::Publish(const int &data)
{
    std::cout << "OutputSampleInterface publishes" << std::endl;
}

std::string OutputSampleInterface::GetInterfaceName() const
{
    return "Sample";
}

openais::interface::Interface *OutputSampleInterface::Clone() const
{
    return new OutputSampleInterface(*this);
}


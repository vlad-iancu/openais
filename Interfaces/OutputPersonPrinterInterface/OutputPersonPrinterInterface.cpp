#include <OutputPersonPrinterInterface.hpp>

using namespace openais::interfaces;

OutputPersonPrinterInterface OutputPersonPrinterInterface::_interface;

OutputPersonPrinterInterface::OutputPersonPrinterInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

OutputPersonPrinterInterface::OutputPersonPrinterInterface(const OutputPersonPrinterInterface &other)
{

}

void OutputPersonPrinterInterface::Publish(const Person &data)
{
    
    std::cout << "PersonPrinter: " << data.name() << " " << data.age() << " " << data.id() << std::endl;

}

std::string OutputPersonPrinterInterface::GetInterfaceName() const
{
    return "PersonPrinter";
}

openais::interface::Interface *OutputPersonPrinterInterface::Clone() const
{
    return new OutputPersonPrinterInterface(*this);
}

bool OutputPersonPrinterInterface::Start()
{
    SetActive(true);
    return true;
}

bool OutputPersonPrinterInterface::Stop()
{
    SetActive(false);
    return true;
}

#include <InputPersonPrinterInterface.hpp>
#include <chrono>
using namespace openais::interfaces;

InputPersonPrinterInterface InputPersonPrinterInterface::_interface;

InputPersonPrinterInterface::InputPersonPrinterInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

InputPersonPrinterInterface::InputPersonPrinterInterface(const InputPersonPrinterInterface &other)
{
}

openais::interface::Interface *InputPersonPrinterInterface::Clone() const
{
    return new InputPersonPrinterInterface(*this);
}

std::string InputPersonPrinterInterface::GetInterfaceName() const
{
    return "";
}

bool InputPersonPrinterInterface::Start()
{
    SetActive(true);
    return true;
}

bool InputPersonPrinterInterface::Stop()
{
    SetActive(false);
    return true;
}

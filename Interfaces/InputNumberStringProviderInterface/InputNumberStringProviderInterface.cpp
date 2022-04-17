
#include <InputNumberStringProviderInterface.hpp>

#include <chrono>

#include <boost/lexical_cast.hpp>

using namespace openais::interfaces;

InputNumberStringProviderInterface InputNumberStringProviderInterface::_interface;

InputNumberStringProviderInterface::InputNumberStringProviderInterface()
{
    openais::interface::Interface::RegisterInterface(this);
}

InputNumberStringProviderInterface::InputNumberStringProviderInterface(const InputNumberStringProviderInterface &other)
{
}

openais::interface::Interface *InputNumberStringProviderInterface::Clone() const
{
    return new InputNumberStringProviderInterface(*this);
}

std::string InputNumberStringProviderInterface::GetInterfaceName() const
{
    return "NumberStringProvider";
}

bool InputNumberStringProviderInterface::Start()
{
    m_counter = 0;
    IsActive(true);
    m_counterThread = std::thread([&] {
        while (IsActive()) 
        {
            m_callback(boost::lexical_cast<std::string>(m_counter));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            m_counter++;
        }
        
    });
    return true;
}

bool InputNumberStringProviderInterface::Stop()
{
    if(m_counterThread.joinable())
    {
        m_counterThread.join();
    }
    IsActive(false);
    return true;
}

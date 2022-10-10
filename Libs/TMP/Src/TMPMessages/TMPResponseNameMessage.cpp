#include <TMPMessages/TMPResponseNameMessage.hpp>

#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace openais::TMP;

TMP_MESSAGE_IMPL(TMPResponseNameMessage)

TMPResponseNameMessage::TMPResponseNameMessage(const std::string &name)
    :m_name(name)
{
}

TMPResponseNameMessage::TMPResponseNameMessage()
    :m_name("")
{
}

std::string TMPResponseNameMessage::GetName() const
{
    return m_name; 
}

void TMPResponseNameMessage::SetName(const std::string &name)
{
    m_name = name; 
}


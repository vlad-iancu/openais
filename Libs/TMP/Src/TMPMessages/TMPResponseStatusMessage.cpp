#include <TMPMessages/TMPResponseStatusMessage.hpp>


#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace openais::TMP;

TMP_MESSAGE_IMPL(TMPResponseStatusMessage)

TMPResponseStatusMessage::TMPResponseStatusMessage()
{
  m_status = TMPStatus::EXITED;
}
TMPResponseStatusMessage::TMPResponseStatusMessage(TMPStatus status)
  : m_status(status)
{
}

TMPID TMPResponseStatusMessage::GetStatus() const
{
  return (TMPID)(m_status);
}

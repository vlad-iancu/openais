#include <TMPMessage.hpp>

using namespace openais::TMP;

TMPID TMPMessage::GetId() const
{
    return (TMPID)m_id;
}

void TMPMessage::SetId(TMPID id)
{
    m_id = (int)id;
}

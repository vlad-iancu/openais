#ifndef OPENAIS_LIBS_TMP_TMPRESPONSESTATUSMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPRESPONSESTATUSMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPResponseStatusMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL
            TMPResponseStatusMessage();
            TMPResponseStatusMessage(TMPStatus status);
            TMPID GetStatus() const;

        public:
            SERIALIZATION_DECL({ar & m_status;})

        private:
            TMPStatus m_status;
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPResponseStatusMessage, 1)
#endif

#ifndef OPENAIS_LIBS_TMP_TMPREQUESTSTATUSMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPREQUESTSTATUSMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPRequestStatusMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL
        
        public:
            SERIALIZATION_DECL({})
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPRequestStatusMessage, 1)
#endif

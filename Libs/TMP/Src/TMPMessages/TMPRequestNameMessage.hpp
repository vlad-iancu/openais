#ifndef OPENAIS_LIBS_TMP_TMPREQUESTNAMEMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPREQUESTNAMEMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPRequestNameMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL

        public:
            SERIALIZATION_DECL({});
        };
    }
}

BOOST_CLASS_VERSION(openais::TMP::TMPRequestNameMessage, 1)
#endif

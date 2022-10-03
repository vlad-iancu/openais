#ifndef OPENAIS_LIBS_TMP_TMPPAUSEMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPPAUSEMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPPauseMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL

        public:
            SERIALIZATION_DECL({})
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPPauseMessage, 1)
#endif

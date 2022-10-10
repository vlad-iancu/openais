#ifndef OPENAIS_LIBS_TMP_TMPSTOPMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPSTOPMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPStopMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL
        
        public:
            SERIALIZATION_DECL({})
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPStopMessage, 1)
#endif

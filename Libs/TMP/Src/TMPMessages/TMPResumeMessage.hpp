#ifndef OPENAIS_LIBS_TMP_TMPRESUMEMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPRESUMEMESSAGE_H

#include <TMPMessage.hpp>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPResumeMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL
        
        public:
            SERIALIZATION_DECL({})
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPResumeMessage, 1)
#endif

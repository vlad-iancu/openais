#ifndef OPENAIS_LIBS_TMP_TMPRESPONSENAMEMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPRESPONSENAMEMESSAGE_H

#include <TMPMessage.hpp>
#include <string>
#include <boost/serialization/version.hpp>

namespace openais
{
    namespace TMP
    {
        class TMPResponseNameMessage: public TMPMessage
        {
        public:
            TMP_MESSAGE_DECL
            TMPResponseNameMessage(const std::string &name);
            TMPResponseNameMessage();

        public:
            SERIALIZATION_DECL({ar & m_name;})
            std::string GetName() const;
            void SetName(const std::string &name);

        private:
            std::string m_name;
        };
    }
}
BOOST_CLASS_VERSION(openais::TMP::TMPResponseNameMessage, 1)
#endif


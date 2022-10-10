#ifndef OPENAIS_LIBS_TMP_TMPMESSAGE_H
#define OPENAIS_LIBS_TMP_TMPMESSAGE_H

#include <TMP.hpp>
#include <string>
#include <memory>

#define TMP_MESSAGE_DECL \
    std::string Save() const override; \
    void Load(const std::string &archive) override;

#define TMP_MESSAGE_IMPL(TMPMessage_t) \
    std::string TMPMessage_t::Save() const \
    { \
        std::ostringstream ostr; \
        boost::archive::text_oarchive oa(ostr); \
        oa << *this; \
        return ostr.str(); \
    } \
 \
    void TMPMessage_t::Load(const std::string &archive) \
    { \
        std::istringstream istr(archive); \
        boost::archive::text_iarchive ia(istr); \
        ia >> *this; \
    }

#define SERIALIZATION_DECL(field_serialization ) \
    template<typename Archive> \
    void serialize(Archive &ar, const unsigned int version) \
    { \
        ar & m_id; \
        field_serialization \
    } \
 

namespace openais
{
    namespace TMP
    {
        class TMPMessage;
        using TMPMessagePtr = std::shared_ptr<openais::TMP::TMPMessage>;

        class TMPMessage
        {
        public:
            static TMPMessagePtr LoadMessage(const std::string &archive);
            TMPID GetId() const;
            void SetId(TMPID id);
            virtual std::string Save() const = 0;
            virtual void Load(const std::string &archive) = 0;
        
        protected:
            int m_id;
        };
    }
}

#endif

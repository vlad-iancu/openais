#ifndef OPENAIS_OUTPUTINTERFACE_H
#define OPENAIS_OUTPUTINTERFACE_H

#include <Interface/Interface.hpp>

namespace openais
{
    namespace interface
    {
        template <typename T>
        class OutputInterface : public Interface
        {
        public:
            virtual void Publish(const T &data) = 0;
        };
    } // namespace interface

} // namespace openais

#endif
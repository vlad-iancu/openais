#ifndef OPENAIS_OUTPUTINTERFACE_H
#define OPENAIS_OUTPUTINTERFACE_H

#include <Interface/Interface.hpp>

namespace openais
{
    namespace interface
    {
        /**
         * @brief This class represents an Interface which publishes data provided by the object user to an external source
         *
         * 
         * @tparam T the kind of data that this interface publishes
         */
        template <typename T>
        class OutputInterface : public Interface
        {
        public:
            /**
             * @brief publishes data
             * 
             * @param data 
             */
            virtual void Publish(const T &data) = 0;
        };
    } // namespace interface

} // namespace openais

#endif
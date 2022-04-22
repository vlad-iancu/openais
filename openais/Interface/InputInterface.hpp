#ifndef OPENAIS_INPUTINTERFACE_H
#define OPENAIS_INPUTINTERFACE_H

#include <Interface/Interface.hpp>
#include <functional>

namespace openais
{
    namespace interface
    {
        template <typename T>
        using Callback = std::function<void(T)>;

        /**
         * @brief This class represents an Interface which provides data to the object user via a Callback that is called when 
         * that information is available
         * 
         * @tparam T the kind of data that this interface produces
         */
        template <typename T>
        class InputInterface : public Interface
        {
        protected:
            Callback<T> m_callback;

        public:
            /**
             * @brief Set the Callback object that will be called as soon as data will be available
             * 
             * @param callback 
             */
            void SetCallback(Callback<T> callback)
            {
                m_callback = callback;
            }
        };
    } // namespace interface

} // namespace openais

#endif
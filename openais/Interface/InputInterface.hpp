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

        template <typename T>
        class InputInterface : public Interface
        {
        private:
            Callback<T> m_callback;

        public:
            void SetCallback(Callback<T> callback)
            {
                m_callback = callback;
            }
        };
    } // namespace interface

} // namespace openais

#endif
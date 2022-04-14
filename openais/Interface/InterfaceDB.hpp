#ifndef OPENAIS_INTERFACEDB_H
#define OPENAIS_INTERFACEDB_H

#include <map>
#include <string>
#include <Interface/Interface.hpp>

namespace openais
{
    namespace interface
    {
        class InterfaceDB
        {
        private:
            static std::map<std::string, Interface*> interfaces;

        public:
            static void Register(const std::string &name, Interface *interface);

            template<typename T>
            static T *GetInterface(const std::string &interface)
            {
                return dynamic_cast<T*>(interfaces[interface]->Clone());
            }
        };
    } // namespace interface

} // namespace openais

#endif
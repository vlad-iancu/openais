#ifndef OPENAIS_INTERFACEDB_H
#define OPENAIS_INTERFACEDB_H

#include <Interface/Interface.hpp>

#include <stdexcept>
#include <map>
#include <string>
#include <iostream>

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
                if(interfaces.find(interface) == interfaces.end())
                {
                    std::cout << "Warning: " << "InterfaceDB was unable to find interface \"" << interface << "\"" << std::endl;
                    return nullptr;
                }
                T* iface = dynamic_cast<T*>(interfaces[interface]->Clone());
                if(!iface)
                {
                    std::cout << "Warning: " << "Incorrect interface type for \"" << interface << "\"" << std::endl;
                }
                return iface;
            }
        };
    } // namespace interface

} // namespace openais

#endif
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
        /**
         * @brief This class serves as a key-value store for Self-registered interface objects
         * 
         */
        class InterfaceDB
        {
        private:
            static std::map<std::string, Interface*> interfaces;

        public:
            /**
             * @brief Registers an interface under a specific name
             * 
             * @param name the name that will be associated with the interface parameter
             * @param interface the interface
             */
            static void Register(const std::string &name, Interface *interface);

            /**
             * @brief Gets a pointer to the interface of a provided type that was registered under a specific name
             * 
             * @tparam T the Interface type
             * @param interface the name that was used when InterfaceDB::Register was called on the registered interface
             * @return T* a pointer to a clone of the registered interface
             */
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
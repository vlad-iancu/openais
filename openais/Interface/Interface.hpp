#ifndef OPENAIS_INTERFACE_H
#define OPENAIS_INTERFACE_H

#include <string>

#ifndef MAX_INTERFACES
#define MAX_INTERFACES 1000
#endif

namespace openais
{
    namespace interface
    {
        /**
         * @brief An Interface represents generally an object where information can be sent to/taken from.
         * This is the base class for all interfaces from which you should extend.
         * 
         */
        class Interface
        {
        private:
            /**
             * @brief Counter of self-registering prototypes
             * 
             */
            static int counter;

            /**
             * @brief Self-registered prototypes storage
             * 
             */
            static Interface *interfaces[MAX_INTERFACES];

        protected:
            static void RegisterInterface(Interface *interface);
            
        public:
            /**
             * @brief Gets an Interface prototype at the specified index
             * 
             * @param index 
             * @return Interface* 
             */
            static Interface *GetInterface(int index);

            /**
             * @brief Gets an Interface prototype
             * 
             * @param name 
             * @return Interface* 
             */
            static Interface *GetInterface(const std::string &name);

            /**
             * @brief Get the number of interface prototypes
             * 
             * @return int 
             */
            static int GetInterfaceCount();
            
        public:
            /**
             * @brief Creates a clone of the current Interface object
             * 
             * @return Interface* 
             */
            virtual Interface *Clone() const = 0;

            /**
             * @brief Get the name of the current Interface.
             * This name is used as value in the `Interfaces` python dict in Task `config.py` files
             * 
             * @return std::string 
             */
            virtual std::string GetInterfaceName() const = 0;

            /**
             * @brief Starts the current Interface object
             * 
             * @return true if the operation was successful, false otherwise
             */
            virtual bool Start() = 0;

            /**
             * @brief Stops the interface
             * 
             * @return true if the operation was successful, false otherwise
             */
            virtual bool Stop() = 0;

            /** 
             * 
             * @return wheter the interface is active or not
             */
            bool IsActive() const;

            /**
             * @brief Marks the current Interface object as active or inactive
             * 
             * @param active
             */
            void SetActive(bool active);

        private:
            bool m_active = false;
        };
    } // namespace interface

} // namespace openais

#endif
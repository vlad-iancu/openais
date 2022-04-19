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
        class Interface
        {
        private:
            static int counter;
            static Interface *interfaces[MAX_INTERFACES];

        private:
            bool m_active = false;

        protected:
            static void RegisterInterface(Interface *interface);
            
        public:
            static Interface *GetInterface(int index);
            static Interface *GetInterface(const std::string &name);
            static int GetInterfaceCount();
            
        public:
            virtual Interface *Clone() const = 0;
            virtual std::string GetInterfaceName() const = 0;
            virtual bool Start() = 0;
            virtual bool Stop() = 0;
            bool IsActive() const;
            void IsActive(bool active);
        };
    } // namespace interface

} // namespace openais

#endif
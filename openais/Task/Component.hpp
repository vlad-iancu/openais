#ifndef OPENAIS_COMPONENT_H
#define OPENAIS_COMPONENT_H

#include <Task/Config.hpp>

#ifndef MAX_COMPONENTS
#define MAX_COMPONENTS 1000
#endif
namespace openais
{
    namespace task
    {
        class Component
        {
        private:
            static int counter;
            static Component *components[MAX_COMPONENTS];
            
        protected:
            bool mActive = false;
            double mFrequencyHz = 0;

        public:
            static Component *GetComponent(int index);
            virtual ~Component();
            virtual void Initialize(const Config &config) = 0;
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void Execute() = 0;
            virtual bool IsActive() const;
            virtual void SetActive(bool active);
            virtual void SetFrequency(double frequency);
            virtual double GetFrequency() const;
            virtual Component *Clone() const = 0;
            static int GetCounter();
            virtual std::string GetName() const = 0;
            void RegisterComponent(Component *component);
        };
    } // namespace task
} // namespace openais

#endif // OPENAIS_COMPONENT_H
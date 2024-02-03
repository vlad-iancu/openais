#include <Task/Component.hpp>
#include <iostream>
using namespace openais::task;

int Component::counter = 0;
Component *Component::components[MAX_COMPONENTS];

Component *Component::GetComponent(int index)
{
    return components[index];
}

Component::~Component()
{
}

bool Component::IsActive() const
{
    return mActive;
}

void Component::SetActive(bool active)
{
    mActive = active;
}

void Component::RegisterComponent(Component *component)
{
    std::cout << "Registering component " << component->GetName() << std::endl;
    components[counter++] = component->Clone();
    std::cout << components[counter - 1]->GetName() << std::endl;
}

void Component::SetFrequency(double frequency)
{
    mFrequencyHz = frequency;
}

double Component::GetFrequency() const
{
    return mFrequencyHz;
}

int Component::GetCounter()
{
    return counter;
}
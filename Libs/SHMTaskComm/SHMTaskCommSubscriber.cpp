#include "SHMTaskCommClient.hpp"

#include <iceoryx_posh/popo/subscriber.hpp>
#include <iceoryx_posh/runtime/posh_runtime.hpp>
#include <iox/signal_watcher.hpp>

struct RadarObject
{
    double x;
    double y;
    double z;
};
int main()
{
    const char APP_NAME[] = "SHMTaskCommSubscriber";
    iox::runtime::PoshRuntime::initRuntime(APP_NAME);

    iox::popo::Subscriber<RadarObject> subscriber({"Radar", "FrontLeft", "Object"});
    RadarObject defaultObj;
    while (!iox::hasTerminationRequested())
    {
        auto takeResult = subscriber.take();
        if (takeResult.has_error())
        {
            std::cout << "Error receiving data: " << takeResult.get_error() << std::endl;
        }
        else
        {

            auto sample = takeResult.value().get();
            std::cout << "Received data: " << sample->x << ", " << sample->y << ", " << sample->z << std::endl;
        }
       // publisher.publishCopyOf(obj);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    return 0;
    // Create a shared memory object.
    // Remove any previous shared memory with the name
    // and create the shared memory segment.
}

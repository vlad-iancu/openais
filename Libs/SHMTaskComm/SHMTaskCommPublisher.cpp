#include "SHMBlock.hpp"

#include <boost/interprocess/mapped_region.hpp>
#include <KeepAlive.pb.h>
#include <thread>
#include <chrono>

#include <iceoryx_posh/popo/publisher.hpp>
#include <iceoryx_posh/runtime/posh_runtime.hpp>
#include <iox/signal_watcher.hpp>

using namespace openais::comm;
namespace ipc = boost::interprocess;
/*
   Every SHMTaskCommClient will write a periodic keep-alive message with its PID
   and a timestamp to the SHMBlock, this way the SHMTaskCommServer can check if
   the client is still alive.
   The SHMTaskCommServer will use this information so that every time a new message it
   is written it will give the chance to every connected client to read it.
   The keep-alive message will be used to check if the client is still alive, if not,
   the server will not wait for it to read the message.

*/
struct RadarObject
{
   double x;
   double y;
   double z;
};
int main()
{
   const char APP_NAME[] = "SHMTaskCommPublisher";
   iox::runtime::PoshRuntime::initRuntime(APP_NAME);

   iox::popo::Publisher<RadarObject> publisher({"Radar", "FrontLeft", "Object"});
   iox::popo::Publisher<RadarObject> pub();
   iox::capro::ServiceDescription serviceDescription());
   while(!iox::hasTerminationRequested())
   {
      RadarObject obj;
      auto loanResult = publisher.loan();
      auto &sample = loanResult.value();
      if(!loanResult.has_error())
      {
         sample.get()->x = 1.0;
         sample.get()->y = 2.0;
         sample.get()->z = 4.0;
         sample.publish();
      }
      else
      {
         std::cout << "Error publishing sample" << std::endl;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }
   return 0;
   //Create a shared memory object.
   //Remove any previous shared memory with the name
   //and create the shared memory segment.
   

}
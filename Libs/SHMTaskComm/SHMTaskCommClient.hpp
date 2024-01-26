#include "SHMBlock.hpp"
#include <functional>
#include <thread>

using namespace openais::comm;
namespace ipc = boost::interprocess;
namespace openais
{
    namespace comm
    {
        using SHMReadCallback = std::function<void(const char *data, unsigned int size)>;
        class SHMTaskCommClient
        {
        private:
            std::shared_ptr<SHMBlock> pShmBlock;
            std::thread mKeepAliveThread;
            unsigned int mKeepAliveMillis;
            SHMReadCallback mReadCallback;
            std::string mShmBlockName;
            bool mIsRunning;
            unsigned int mProcIndex;
        public:
            SHMTaskCommClient(
                const std::string &shmBlockName, 
                unsigned int shmBlockSize,
                unsigned int keepAliveMillis,
                unsigned int maxNrProcs,
                SHMReadCallback readCallback);
            ~SHMTaskCommClient();
            
            void Start();
            void Stop();

            void Write(const char *data, unsigned int size);
            void Read(char *data, unsigned int size);
            
        };
    }
}
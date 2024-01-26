#include "SHMTaskCommClient.hpp"

using namespace openais::comm;

SHMTaskCommClient::SHMTaskCommClient(
    const std::string &shmBlockName,
    unsigned int shmBlockSize,
    unsigned int keepAliveMillis,
    unsigned int maxNrProcs,
    SHMReadCallback readCallback)
    :
    mKeepAliveMillis(keepAliveMillis),
    mReadCallback(readCallback),
    mShmBlockName(shmBlockName)
{
    // Constructor implementation
    // ...
    pShmBlock = std::make_shared<SHMBlock>(
        shmBlockName,
        maxNrProcs,
        shmBlockSize);
    
    mProcIndex = pShmBlock->AddProc();
    std::cout << "ProcIndex: " << mProcIndex << std::endl;
}

SHMTaskCommClient::~SHMTaskCommClient()
{
    // Destructor implementation
    // ...
    Stop();
    if (mKeepAliveThread.joinable())
    {
        mKeepAliveThread.join();
    }
}

void SHMTaskCommClient::Start()
{
    // Start implementation
    // ...
    mIsRunning = true;
    mKeepAliveThread = std::thread([this](){
        while (mIsRunning)
        {
            KeepAlive keepAlive;
            keepAlive.set_pid(getpid());
            keepAlive.set_time(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count());
            // Keep alive implementation
            // ...
            pShmBlock->WriteKeepAlive(keepAlive, mProcIndex);
            std::this_thread::sleep_for(std::chrono::milliseconds(mKeepAliveMillis));
        }
    });
    mKeepAliveThread.detach();
}

void SHMTaskCommClient::Stop()
{
    // Stop implementation
    // ...
    mIsRunning = false;
}

void SHMTaskCommClient::Write(const char *data, unsigned int size)
{
    // Write implementation
    // ...
}

void SHMTaskCommClient::Read(char *data, unsigned int size)
{
    // Read implementation
    // ...
}

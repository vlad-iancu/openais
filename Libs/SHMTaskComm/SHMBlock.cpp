#include "SHMBlock.hpp"
#include <boost/interprocess/sync/named_mutex.hpp>

using namespace openais::comm;

SHMBlock::SHMBlock(
    const std::string &shmBlockName, 
    unsigned int maxNrProcs,
    unsigned int shmBlockSize)
    :
    mShmBlockSize(shmBlockSize),
    mMaxNrProcs(maxNrProcs)
{
    // Constructor implementation
    // ...
    mShmKeepAliveBlock = ipc::shared_memory_object(
        ipc::open_or_create,
        (shmBlockName + "_keepAlive").c_str(),
        ipc::read_write);
    mShmKeepAliveBlock.truncate(maxNrProcs * sizeof(SHMClientInfo));
    mShmRegion = ipc::mapped_region(
        mShmKeepAliveBlock,
        ipc::read_write);
    mShmBlockName = shmBlockName;

    mShmDataBlock = ipc::shared_memory_object(
        ipc::open_or_create,
        (shmBlockName + "_data").c_str(),
        ipc::read_write);

    mShmDataBlock.truncate(shmBlockSize);

    mNrProcsBlock = ipc::shared_memory_object(
        ipc::open_or_create,
        (shmBlockName + "_nrProcs").c_str(),
        ipc::read_write);

    mNrProcsBlock.truncate(sizeof(unsigned int));
    // {
    //     ipc::mapped_region region(
    //         mNrProcsBlock,
    //         ipc::read_write);
    //     //Set mNrProcs to 0
    //     unsigned int *nrProcsPtr = static_cast<unsigned int*>(region.get_address());
    //     *nrProcsPtr = 0;
    // }

    pProcCountMutex = std::shared_ptr<ipc::named_mutex>(new ipc::named_mutex(
        ipc::open_or_create,
        (shmBlockName + "_procCount").c_str(),
        ipc::read_write));

    // SetNrProcs(0);
}

void SHMBlock::remove(const std::string &shmBlockName)
{
    ipc::shared_memory_object::remove((shmBlockName + "_keepAlive").c_str());
    ipc::shared_memory_object::remove((shmBlockName + "_data").c_str());
    ipc::shared_memory_object::remove((shmBlockName + "_nrProcs").c_str());
    ipc::named_mutex::remove((shmBlockName + "_procCount").c_str());
}

SHMBlock::~SHMBlock()
{
    // Destructor implementation
    // ...
    ipc::shared_memory_object::remove(mShmKeepAliveBlock.get_name());
    ipc::shared_memory_object::remove(mShmDataBlock.get_name());
}

void SHMBlock::WriteData(const char *data, unsigned int dataSize)
{
    std::memcpy(mShmRegion.get_address(), data, dataSize);
    // Write data implementation
    // ...

    if (dataSize > mShmRegion.get_size())
    {
        throw std::runtime_error("Data size is larger than shared memory block size");
    }
}

void SHMBlock::ReadData(char *data, unsigned int dataSize)
{
    std::memcpy(data, mShmRegion.get_address(), dataSize);
    // Read data implementation
    // ...
    if (dataSize > mShmRegion.get_size())
    {
        throw std::runtime_error("Data size is larger than shared memory block size");
    }
}

void SHMBlock::WriteKeepAlive(
    const KeepAlive &keepAlive,
    unsigned int index)
{
    // Write keep-alive implementation
    // ...
    if (index >= mMaxNrProcs)
    {
        throw std::runtime_error("Index is larger than maximum number of processes");
    }

    SHMClientInfo *shmClientInfo = static_cast<SHMClientInfo*>(mShmRegion.get_address());
    shmClientInfo[index].keepAlive = keepAlive;
}

void SHMBlock::ReadKeepAlive(
    KeepAlive &keepAlive,
    unsigned int index)
{
    // Read keep-alive implementation
    // ...
    if (index >= mMaxNrProcs)
    {
        throw std::runtime_error("Index is larger than maximum number of processes");
    }

    SHMClientInfo *shmClientInfo = static_cast<SHMClientInfo*>(mShmRegion.get_address());
    keepAlive = shmClientInfo[index].keepAlive;
}

void SHMBlock::SetNrProcs(unsigned int nrProcs)
{
    // Set number of processes implementation
    // ...
    if (nrProcs > mMaxNrProcs)
    {
        throw std::runtime_error("Number of processes is larger than maximum number of processes");
    }

    ipc::mapped_region region(
        mNrProcsBlock,
        ipc::read_write);
    
    unsigned int *nrProcsPtr = static_cast<unsigned int*>(region.get_address());
    *nrProcsPtr = nrProcs;
}

unsigned int SHMBlock::GetNrProcs()
{
    // Get number of processes implementation
    // ...
    ipc::scoped_lock<ipc::named_mutex> lock(*pProcCountMutex);
    ipc::mapped_region region(
        mNrProcsBlock,
        ipc::read_write);
    
    unsigned int *nrProcsPtr = static_cast<unsigned int*>(region.get_address());
    return *nrProcsPtr;
}

unsigned int SHMBlock::AddProc()
{
    // Add process implementation
    // ...
    ipc::scoped_lock<ipc::named_mutex> lock(*pProcCountMutex);
    ipc::mapped_region region(
        mNrProcsBlock,
        ipc::read_write);
    unsigned int *nrProcsPtr = static_cast<unsigned int*>(region.get_address());
    unsigned int nrProcs = *nrProcsPtr;
    std::cout << "We have " << nrProcs << " processes" << std::endl;
    if (nrProcs >= mMaxNrProcs)
    {
        throw std::runtime_error("Number of processes is larger than maximum number of processes");
    }

    *nrProcsPtr = nrProcs + 1;
    std::cout << "Now we should have " << *nrProcsPtr << " processes" << std::endl;
    return nrProcs;
}
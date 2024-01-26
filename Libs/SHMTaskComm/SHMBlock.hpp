#ifndef OPENAIS_SHMBLOCK_HPP
#define OPENAIS_SHMBLOCK_HPP

#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <memory>

#include <KeepAlive.pb.h>

namespace ipc = boost::interprocess;
namespace openais
{
    namespace comm
    {
        struct SHMClientInfo
        {
            KeepAlive keepAlive;
            //This condition will be notified when a listener should read a data message
            ipc::interprocess_condition cond;
        };
        class SHMBlock
        {
        private:
            unsigned int mShmBlockSize;
            unsigned int mMaxNrProcs;
            ipc::shared_memory_object mShmKeepAliveBlock;
            ipc::shared_memory_object mShmDataBlock;
            ipc::shared_memory_object mNrProcsBlock;
            std::shared_ptr<ipc::named_mutex> pProcCountMutex;
            ipc::mapped_region mShmRegion;
            std::string mShmBlockName;

        public:
            static void remove(const std::string &shmBlockName);
            
        public:
            SHMBlock(
                const std::string &shmBlockName,
                unsigned int maxNrProcs,
                unsigned int shmBlockSize);
            ~SHMBlock();

            void WriteData(const char *data, unsigned int size);
            void ReadData(char *data, unsigned int size);

            void WriteKeepAlive(
                const KeepAlive &keepAlive,
                unsigned int index);
            
            void ReadKeepAlive(
                KeepAlive &keepAlive,
                unsigned int index);

            void SetNrProcs(unsigned int nrProcs);

            unsigned int GetNrProcs();

            unsigned int AddProc();
        };
    }
}
#endif // OPENAIS_SHMBLOCK_HPP

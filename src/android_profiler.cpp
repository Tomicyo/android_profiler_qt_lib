#include "android_profiler.h"

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include <memory>

#include "profiler_service.h"
#include "cpu_service.h"

namespace android
{
    namespace profiler
    {
        using namespace ::grpc;
        
        class PerfDClientImpl
        {
        public:
            PerfDClientImpl(std::shared_ptr<Channel> channel)
                : m_Channel(channel)
            {
            }
            ~PerfDClientImpl()
            {
            }
            std::shared_ptr<Channel> channel() const
            {
                return m_Channel;
            }
        private:
            std::shared_ptr<Channel> m_Channel;

        };

        PerfDClient::PerfDClient(const char* ServerAddress)
            : d(new PerfDClientImpl(grpc::CreateChannel(ServerAddress,
                grpc::InsecureChannelCredentials())))
        {
            
        }
        PerfDClient::~PerfDClient()
        {
            if (d)
            {
                delete d;
            }
        }

        GpuService::~GpuService()
        {

        }

        CpuService::CpuService(PerfDClientImpl* pd)
        {
            d = new CpuServiceImpl(pd->channel());
        }

        CpuService::~CpuService()
        {
            if (d)
            {
                delete d;
            }
        }
        void CpuService::GetThreads(int pid, std::vector<ThreadInfo>& infos)
        {
            d->GetThreads(pid, infos);
        }
    }
}
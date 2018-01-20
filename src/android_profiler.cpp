#include "android_profiler.h"

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include <memory>

#include "profiler_service.h"
#include "memory_service.h"
#include "gpu_service.h"
#include "cpu_service.h"

namespace android
{
    namespace profiler
    {
        using namespace ::grpc;
        
        class ANDROPROF_API PerfDClientImpl
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

            std::shared_ptr<CpuService> getCpuService()
            {
                if (!m_CpuService)
                {
                    m_CpuService = std::make_unique<CpuService>(this);
                }
                return std::move(m_CpuService);
            }

            std::shared_ptr<ProfilerService> getProfilerService()
            {
                if (!m_ProfilerService)
                {
                    m_ProfilerService = std::make_unique<ProfilerService>(this);
                }
                return std::move(m_ProfilerService);
            }

        private:
            std::shared_ptr<Channel>            m_Channel;
            std::unique_ptr<CpuService>         m_CpuService;
            std::unique_ptr<ProfilerService>    m_ProfilerService;
        };

        PerfDClient::PerfDClient(const char* ServerAddress)
            : d(std::make_unique<PerfDClientImpl>(
                grpc::CreateChannel(ServerAddress,
                grpc::InsecureChannelCredentials())))
        {
            
        }
        PerfDClient::~PerfDClient()
        {
        }

        std::shared_ptr<ProfilerService> PerfDClient::GetProfilerService()
        {
            return d->getProfilerService();
        }

        std::shared_ptr<CpuService> PerfDClient::GetCpuService()
        {
            return d->getCpuService();
        }
/*
        std::shared_ptr<MemoryService> PerfDClient::GetMemoryService()
        {
            return std::shared_ptr<MemoryService>();
        }*/

        GpuService::GpuService(PerfDClientImpl * pd)
        {
        }

        GpuService::~GpuService()
        {

        }

        CpuService::CpuService(PerfDClientImpl* pd)
        {
            d = std::make_unique<CpuServiceImpl>(pd->channel());
        }

        CpuService::~CpuService()
        {
        }
        void CpuService::GetThreads(int pid, std::vector<ThreadInfo>& infos)
        {
            d->GetThreads(pid, infos);
        }


        MemoryService::~MemoryService()
        {
        }

        ProfilerService::ProfilerService(PerfDClientImpl* pd)
        {
            d = std::make_unique<ProfilerServiceImpl>(pd->channel());
        }
        ProfilerService::~ProfilerService()
        {
        }
        void ProfilerService::GetDevices(std::vector<DeviceInfo>& devices)
        {
            d->GetDevices(devices);
        }
        void ProfilerService::GetVersion(std::string & version)
        {
            d->GetVersion(version);
        }
    }
}
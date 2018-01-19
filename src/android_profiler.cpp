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
        
        class ClientImpl
        {
        public:
            ClientImpl(std::shared_ptr<Channel> channel)
                : m_ProfSrv(std::make_unique<CProfilerService>(channel))
                , m_CpuSrv(std::make_unique<CCpuService>(channel))
            {
                m_CpuSrv->GetThreads(10151);
                m_ProfSrv->GetVersion();
            }
            ~ClientImpl()
            {
            }

        private:
            std::unique_ptr<CProfilerService>   m_ProfSrv;
            std::unique_ptr<CCpuService>        m_CpuSrv;
        };

        Client::Client(const char* ServerAddress)
            : d(new ClientImpl(grpc::CreateChannel(ServerAddress,
                grpc::InsecureChannelCredentials())))
        {
            
        }
        Client::~Client()
        {
            if (d)
            {
                delete d;
            }
        }
    }
}
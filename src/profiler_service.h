#pragma once

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "profiler_service.grpc.pb.h"
#include "android_profiler.h"
namespace android
{
    namespace profiler
    {
        using namespace ::grpc;

        class ANDROPROF_API ProfilerServiceImpl
        {
        public:

            ProfilerServiceImpl(std::shared_ptr<Channel> channel);
            ~ProfilerServiceImpl();

            void GetVersion(std::string& version);
            void GetDevices(std::vector<DeviceInfo>& devices);

        private:
            std::unique_ptr< ::profiler::proto::ProfilerService::Stub > m_Stub;
        };
    }
}

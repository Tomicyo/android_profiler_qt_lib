#pragma once

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "profiler_service.grpc.pb.h"
/*
namespace profiler
{
    class ProfilerService : public proto::ProfilerService::Service 
    {
    public:
        ProfilerService();
        ~ProfilerService();

        grpc::Status GetCurrentTime(grpc::ServerContext* context,
            const profiler::proto::TimeRequest* request,
            profiler::proto::TimeResponse* response) override;

        grpc::Status GetVersion(grpc::ServerContext* context,
            const profiler::proto::VersionRequest* request,
            profiler::proto::VersionResponse* response) override;

        grpc::Status GetBytes(grpc::ServerContext* context,
            const profiler::proto::BytesRequest* request,
            profiler::proto::BytesResponse* response) override;

        grpc::Status GetAgentStatus(
            grpc::ServerContext* context,
            const profiler::proto::AgentStatusRequest* request,
            profiler::proto::AgentStatusResponse* response) override;

        grpc::Status GetDevices(
            grpc::ServerContext* context,
            const profiler::proto::GetDevicesRequest* request,
            profiler::proto::GetDevicesResponse* response) override;

        grpc::Status AttachAgent(
            grpc::ServerContext* context,
            const profiler::proto::AgentAttachRequest* request,
            profiler::proto::AgentAttachResponse* response) override;
    };
}
*/

namespace android
{
    namespace profiler
    {
        using namespace ::profiler::proto;
        using namespace ::grpc;

        class CProfilerService
        {
        public:

            CProfilerService(std::shared_ptr<Channel> channel);
            ~CProfilerService();

            std::string GetVersion();

            void AttachAgent();

        private:
            std::unique_ptr< ProfilerService::Stub > m_Stub;
        };
    }
}

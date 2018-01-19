#pragma once

#include "android_profiler.h"
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "cpu.grpc.pb.h"
/*
namespace profiler
{
    class CpuService : public proto::CpuService::Service
    {
    public:
        CpuService();
        ~CpuService();

        grpc::Status GetData(grpc::ServerContext* context,
            const profiler::proto::CpuDataRequest* request,
            profiler::proto::CpuDataResponse* response) override;

        grpc::Status GetThreads(
            grpc::ServerContext* context,
            const profiler::proto::GetThreadsRequest* request,
            profiler::proto::GetThreadsResponse* response) override;

        // TODO: Handle the case if there is no such a running process.
        grpc::Status StartMonitoringApp(
            grpc::ServerContext* context,
            const profiler::proto::CpuStartRequest* request,
            profiler::proto::CpuStartResponse* response) override;

        grpc::Status StopMonitoringApp(
            grpc::ServerContext* context,
            const profiler::proto::CpuStopRequest* request,
            profiler::proto::CpuStopResponse* response) override;

        grpc::Status StartProfilingApp(
            grpc::ServerContext* context,
            const profiler::proto::CpuProfilingAppStartRequest* request,
            profiler::proto::CpuProfilingAppStartResponse* response) override;

        grpc::Status StopProfilingApp(
            grpc::ServerContext* context,
            const profiler::proto::CpuProfilingAppStopRequest* request,
            profiler::proto::CpuProfilingAppStopResponse* response) override;

        grpc::Status CheckAppProfilingState(
            grpc::ServerContext* context,
            const profiler::proto::ProfilingStateRequest* request,
            profiler::proto::ProfilingStateResponse* response) override;
    };
}
*/
namespace android
{
    namespace profiler
    {
        using namespace ::profiler::proto;
        using namespace ::grpc;

        // android o supports
        class CpuServiceImpl
        {
        public:
            CpuServiceImpl(std::shared_ptr<Channel> channel);
            ~CpuServiceImpl();

            void GetData();
            void GetThreads(int processId, std::vector<ThreadInfo>& infos);

        private:
            std::unique_ptr< ::profiler::proto::CpuService::Stub > m_Stub;
        };

    }
}
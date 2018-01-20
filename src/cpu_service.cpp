#include "cpu_service.h"

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

namespace android
{
namespace profiler
{
    using namespace ::grpc;
    using ::profiler::proto::GetThreadsRequest;
    using ::profiler::proto::GetThreadsResponse;
    using ::profiler::proto::CpuDataRequest;
    using ::profiler::proto::CpuDataResponse;

    CpuServiceImpl::CpuServiceImpl(std::shared_ptr<Channel> channel)
        : m_Stub(::profiler::proto::CpuService::NewStub(channel))
    {
    }

    CpuServiceImpl::~CpuServiceImpl()
    {
    }

    void CpuServiceImpl::GetData()
    {
        ClientContext context;
        CpuDataRequest request;
        //request.set_allocated_session()
        ::profiler::proto::CpuDataResponse response;
        Status status = m_Stub->GetData(&context, request, &response);

    }

    void CpuServiceImpl::GetThreads(int processId, std::vector<ThreadInfo>& infos)
    {
        ClientContext context;
        GetThreadsRequest request;
        request.set_process_id(processId);
        GetThreadsResponse response;
        Status status = m_Stub->GetThreads(&context, request, &response);
        for (const auto& thr : response.threads())
        {
            ThreadInfo info{std::move(thr.name()), thr.tid()};
            infos.push_back(std::move(info));
        }
    }

}
}
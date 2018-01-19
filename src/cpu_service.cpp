#include "cpu_service.h"

namespace android
{
namespace profiler
{
    CpuServiceImpl::CpuServiceImpl(std::shared_ptr<Channel> channel)
        : m_Stub(CpuService::NewStub(channel))
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
        CpuDataResponse response;
        Status status = m_Stub->GetData(&context, request, &response);

    }

    void CpuServiceImpl::GetThreads(int processId, std::vector<ThreadInfo>& infos)
    {
        ClientContext context;
        GetThreadsRequest request;
        request.set_process_id(processId);
        GetThreadsResponse response;
        Status status = m_Stub->GetThreads(&context, request, &response);
        for (const GetThreadsResponse_Thread& thr : response.threads())
        {
            ThreadInfo info{std::move(thr.name()), thr.tid()};
            infos.push_back(std::move(info));
        }
    }

}
}
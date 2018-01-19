#include "cpu_service.h"

namespace android
{
namespace profiler
{
    CCpuService::CCpuService(std::shared_ptr<Channel> channel)
        : m_Stub(CpuService::NewStub(channel))
    {
    }

    CCpuService::~CCpuService()
    {
    }

    void CCpuService::GetData()
    {
        ClientContext context;
        CpuDataRequest request;
        //request.set_allocated_session()
        CpuDataResponse response;
        Status status = m_Stub->GetData(&context, request, &response);

    }

    void CCpuService::GetThreads(int processId)
    {
        ClientContext context;
        GetThreadsRequest request;
        request.set_process_id(processId);
        GetThreadsResponse response;
        Status status = m_Stub->GetThreads(&context, request, &response);
        auto thrs = response.threads().size();
        //thrs.data();
    }

}
}
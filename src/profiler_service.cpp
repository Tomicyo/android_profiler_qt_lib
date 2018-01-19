#include "profiler_service.h"

namespace android 
{
    namespace profiler
    {
        CProfilerService::CProfilerService(std::shared_ptr<Channel> channel)
            : m_Stub(ProfilerService::NewStub(channel))
        {

        }
        CProfilerService::~CProfilerService()
        {
        }
        std::string CProfilerService::GetVersion()
        {
            VersionRequest request;
            VersionResponse response;
            ClientContext context;
            Status status = m_Stub->GetVersion(&context, request, &response);
            return response.version();
        }
        void CProfilerService::AttachAgent()
        {
            ClientContext context;
            AgentAttachRequest request;
            request.set_process_id(0);
            AgentAttachResponse response;
            Status status = m_Stub->AttachAgent(&context, request, &response);

        }
    }
}

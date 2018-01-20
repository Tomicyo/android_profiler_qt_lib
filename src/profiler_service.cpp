#include "profiler_service.h"

namespace android 
{
    namespace profiler
    {
        using ::profiler::proto::VersionRequest;
        using ::profiler::proto::VersionResponse;
        using ::profiler::proto::GetDevicesRequest;
        using ::profiler::proto::GetDevicesResponse;

        ProfilerServiceImpl::ProfilerServiceImpl(std::shared_ptr<Channel> channel)
            : m_Stub(::profiler::proto::ProfilerService::NewStub(channel))
        {
        }
        ProfilerServiceImpl::~ProfilerServiceImpl()
        {
        }
        void ProfilerServiceImpl::GetVersion(std::string & version)
        {
            VersionRequest request;
            VersionResponse response;
            ClientContext context;
            request.set_allocated_session(nullptr);
            Status status = m_Stub->GetVersion(&context, request, &response);
            version = std::move(response.version());
        }
        void ProfilerServiceImpl::GetDevices(std::vector<DeviceInfo>& devices)
        {
            GetDevicesRequest request;
            GetDevicesResponse response;
            ClientContext context;
            Status status = m_Stub->GetDevices(&context, request, &response);
            for (const auto&device : response.device())
            {
                DeviceInfo info = { 
                    std::move(device.manufacturer()),
                    std::move(device.model()),
                    std::move(device.serial()),
                    std::move(device.version()),
                    (DeviceState)device.state()
                };
                devices.push_back(std::move(info));
            }
        }
    }
}

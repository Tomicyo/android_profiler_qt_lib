#include "android_profiler.h"

int main(int argc, const char* argv[])
{
    android::profiler::PerfDClient c("localhost:12389");
    auto profiler = c.GetProfilerService();
    std::string version;
    profiler->GetVersion(version);
    std::vector<android::profiler::DeviceInfo> deviceInfos;
    profiler->GetDevices(deviceInfos);

    return 0;
}
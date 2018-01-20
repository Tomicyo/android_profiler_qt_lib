#ifndef __android_profiler_h__
#define __android_profiler_h__
#pragma once

#if _WIN32 || _MSC_VER
//#if defined(LIB_BUILD)
#if defined(BUILD_SHARED_LIB)
#define ANDROPROF_API __declspec(dllexport)
#else
#define ANDROPROF_API __declspec(dllimport)
#endif
//#else
//#define ANDROPROF_API     
//#endif
#else
#define ANDROPROF_API __attribute__((visibility("default"))) 
#endif

#include <string>
#include <memory>
#include <vector>

namespace android
{
    namespace profiler
    {
        class PerfDClientImpl;
        class ProfilerServiceImpl;
        class CpuServiceImpl;
        class MemoryServiceImpl;
//        class GpuServiceImpl;

        struct ThreadInfo
        {
            std::string Name;
            int         Id;
        };

        enum class DeviceState
        {
            Alive = 1,
            Dead
        };

        struct DeviceInfo
        {
            std::string Vendor; // manufacturer
            std::string Model;
            std::string Serial;
            std::string Version; // Os Version
            DeviceState State;
        };

        class ANDROPROF_API ProfilerService
        {
        public:
            explicit ProfilerService(PerfDClientImpl* pd);
            ~ProfilerService();

            void GetDevices(std::vector<DeviceInfo>& devices);
            void GetVersion(std::string& version);

        private:
            std::unique_ptr<ProfilerServiceImpl> d;
        };

        class ANDROPROF_API CpuService
        {
        public:
            explicit CpuService(PerfDClientImpl* pd);
            ~CpuService();

            //void GetData();
            void GetThreads(int pid, std::vector<ThreadInfo>& infos);

            /*void StartMonitoringApp();
            void StopMonitoringApp();

            void StartProfilingApp();
            void StopProfilingApp();

            void CheckAppProfilingState();*/

        private:
            
            std::unique_ptr<CpuServiceImpl> d;
        };

        class ANDROPROF_API MemoryService
        {
        public:
            explicit MemoryService(PerfDClientImpl* pd);
            ~MemoryService();

        private:
            std::unique_ptr<MemoryServiceImpl> d;
        };


        class ANDROPROF_API GpuService
        {
        public:
            explicit GpuService(PerfDClientImpl* pd);
            ~GpuService();

        private:
//            std::unique_ptr<GpuServiceImpl> d;
        };

        class ANDROPROF_API PerfDClient
        {
        public:
            explicit PerfDClient(const char* ServerAddress);
            ~PerfDClient();

            std::shared_ptr<ProfilerService>    GetProfilerService();
            std::shared_ptr<CpuService>         GetCpuService();
        private:
            std::unique_ptr<PerfDClientImpl> d;
        };
    }
}

#endif
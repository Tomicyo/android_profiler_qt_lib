#ifndef __android_profiler_h__
#define __android_profiler_h__
#pragma once

#if _WIN32 || _MSC_VER
#if defined(LIB_BUILD)
#if defined(BUILD_SHARED_LIB)
#define ANDROPROF_API __declspec(dllexport)
#else
#define ANDROPROF_API __declspec(dllimport)
#endif
#else
#define ANDROPROF_API     
#endif
#else
#define NGFX_API __attribute__((visibility("default"))) 
#endif

#include <string>
#include <vector>

namespace android
{
    // Need Kaleido3D Core ?....
    namespace profiler
    {
        class PerfDClientImpl;
        class ProfilerServiceImpl;
        class CpuServiceImpl;
        class MemoryServiceImpl;
        class GpuServiceImpl;

        class ANDROPROF_API ProfilerService
        {

        };

        struct ThreadInfo
        {
            std::string Name;
            int         Id;
        };

        class ANDROPROF_API CpuService
        {
        public:
            ~CpuService();

            //void GetData();
            void GetThreads(int pid, std::vector<ThreadInfo>& infos);

            /*void StartMonitoringApp();
            void StopMonitoringApp();

            void StartProfilingApp();
            void StopProfilingApp();

            void CheckAppProfilingState();*/

        private:
            explicit CpuService(PerfDClientImpl* pd);
            
            CpuServiceImpl* d;
        };

        class ANDROPROF_API MemoryService
        {
        public:
            ~MemoryService();

        private:
            explicit MemoryService(PerfDClientImpl* pd);

        private:
            MemoryServiceImpl* d;
        };


        class ANDROPROF_API GpuService
        {
        public:
            ~GpuService();

        private:
            explicit GpuService(PerfDClientImpl* pd);

        private:
            GpuServiceImpl * d;
        };

        class ANDROPROF_API PerfDClient
        {
        public:
            explicit PerfDClient(const char* ServerAddress);
            ~PerfDClient();

            CpuService*     GetCpuService();
            MemoryService*  GetMemoryService();
        private:
            PerfDClientImpl* d;
        };
    }
}

#endif
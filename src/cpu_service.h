#pragma once

#include "cpu.grpc.pb.h"
#include <grpc++/channel.h>
#include "android_profiler.h"

namespace android
{
    namespace profiler
    {
        // android o supports
        class ANDROPROF_API CpuServiceImpl
        {
        public:
            CpuServiceImpl(std::shared_ptr<grpc::Channel> channel);
            ~CpuServiceImpl();

            void GetData();
            void GetThreads(int processId, std::vector<ThreadInfo>& infos);

        private:
            std::unique_ptr< ::profiler::proto::CpuService::Stub > m_Stub;
        };

    }
}
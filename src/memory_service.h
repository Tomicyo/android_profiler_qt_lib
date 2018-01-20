#pragma once

#include "memory.grpc.pb.h"

namespace android
{
    namespace profiler
    {
        class MemoryServiceImpl
        {
        public:
            MemoryServiceImpl(std::shared_ptr<grpc::Channel> channel);
            ~MemoryServiceImpl();

        private:
            std::unique_ptr< ::profiler::proto::MemoryService::Stub > m_Stub;
        };
    }
}
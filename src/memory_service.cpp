#include "memory_service.h"

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

namespace android
{
    namespace profiler
    {
        MemoryServiceImpl::MemoryServiceImpl(std::shared_ptr<grpc::Channel> channel)
            : m_Stub(::profiler::proto::MemoryService::NewStub(channel))
        {
        }
        MemoryServiceImpl::~MemoryServiceImpl()
        {
        }
    }
}


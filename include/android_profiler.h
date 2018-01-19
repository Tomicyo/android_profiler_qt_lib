#ifndef __android_profiler_h__
#define __android_profiler_h__
#pragma once

#ifndef BUILD_STATIC_LIB
#ifndef ANDROPROF_API
#define ANDROPROF_API  
#endif
#else
#define ANDROPROF_API  
#endif

namespace android
{
    namespace profiler
    {
        class Client ANDROPROF_API
        {
        public:
            explicit Client(const char* ServerAddress);
            ~Client();


        private:
            class ClientImpl* d;
        };
    }
}

#endif
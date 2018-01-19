#include "android_profiler.h"

int main(int argc, const char* argv[])
{
    android::profiler::Client c("localhost:12389");
    
    return 0;
}
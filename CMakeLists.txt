cmake_minimum_required (VERSION 3.6)
project (AndroidProfiler)

if(POLICY CMP0054)
  cmake_policy(SET CMP0054 OLD)
endif()

find_package(PythonInterp)
set(K3D_DEPENDS_PATH ${AndroidProfiler_SOURCE_DIR}/build/dependencies)

if(EXISTS "${K3D_DEPENDS_PATH}/lib/cmake/third_party.cmake")
	message(STATUS "third_party exists")
else()
   	message(STATUS "have to download third_party....")
	execute_process(COMMAND 
		${PYTHON_EXECUTABLE} 
		${AndroidProfiler_SOURCE_DIR}/tools/GetThirdParty.py
		--output_dir ${K3D_DEPENDS_PATH} --target_os=Windows
		--ssl=1
	)
endif()

include(${K3D_DEPENDS_PATH}/lib/cmake/third_party.cmake)
include_directories(include)

set(_gRPC_SSL_LIBRARIES ${OPENSSL_LIBRARIES})
set(_gRPC_SSL_INCLUDE_DIR ${THIRD_PARTY_INCLUDE_DIR})
set(_gRPC_ZLIB_LIBRARIES ${ZLIB_LIBRARIES})
set(_gRPC_ZLIB_INCLUDE_DIR ${THIRD_PARTY_INCLUDE_DIR})

add_subdirectory(thirdparty/grpc)

add_library(libandroid_profiler
src/android_profiler.cpp
)
target_link_libraries(libandroid_profiler grpc grpc++ libprotobuf)
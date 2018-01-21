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

if(MSVC)
    include(${K3D_DEPENDS_PATH}/lib/cmake/third_party.cmake)
elseif(ANDROID)
    set(THIRD_PARTY_INCLUDE_DIR ${AndroidProfiler_SOURCE_DIR}/build/android_dep/include)
    set(OPENSSL_LIBRARIES "${AndroidProfiler_SOURCE_DIR}/build/android_dep/lib/armeabi-v7a/libssl.a;${AndroidProfiler_SOURCE_DIR}/build/android_dep/lib/armeabi-v7a/libcrypto.a")
    set(ZLIB_LIBRARIES z)
endif()
include_directories(include)

set(_gRPC_SSL_LIBRARIES ${OPENSSL_LIBRARIES})
set(_gRPC_SSL_INCLUDE_DIR ${THIRD_PARTY_INCLUDE_DIR})
set(_gRPC_ZLIB_LIBRARIES ${ZLIB_LIBRARIES})
set(_gRPC_ZLIB_INCLUDE_DIR ${THIRD_PARTY_INCLUDE_DIR})

add_subdirectory(thirdparty/grpc)

set(PROF_PROTO_GENS_DIR ${CMAKE_BINARY_DIR}/gens)
file(MAKE_DIRECTORY ${PROF_PROTO_GENS_DIR})
set(PROF_PROTO_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/proto)

function(target_add_proto TARGET)
    cmake_parse_arguments(${TARGET}
        ""
        "FOLDER"
        "PROTOS"
        ${ARGN}
    )
    foreach(PROTO IN LISTS ${TARGET}_PROTOS)
    	get_filename_component(ABS_PROTO ${PROTO} ABSOLUTE)
		add_custom_command(TARGET ${TARGET} PRE_BUILD COMMAND
			$<TARGET_FILE:protoc>
			--grpc_out=generate_mock_code=true:${PROF_PROTO_GENS_DIR}
			--cpp_out=${PROF_PROTO_GENS_DIR} 
			--plugin=protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin>
			-I ${PROF_PROTO_INC_DIR}
			${ABS_PROTO}
		)
    endforeach()
endfunction()

if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600 -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()

set(PROTO_SRCS 
    ${PROF_PROTO_GENS_DIR}/cpu.pb.cc
    ${PROF_PROTO_GENS_DIR}/cpu.grpc.pb.cc

    ${PROF_PROTO_GENS_DIR}/profiler.pb.cc
    ${PROF_PROTO_GENS_DIR}/profiler.grpc.pb.cc
    
    ${PROF_PROTO_GENS_DIR}/profiler_service.pb.cc
    ${PROF_PROTO_GENS_DIR}/profiler_service.grpc.pb.cc

    ${PROF_PROTO_GENS_DIR}/agent_service.pb.cc
    ${PROF_PROTO_GENS_DIR}/agent_service.grpc.pb.cc

    ${PROF_PROTO_GENS_DIR}/graphics.pb.cc
    ${PROF_PROTO_GENS_DIR}/graphics.grpc.pb.cc

    ${PROF_PROTO_GENS_DIR}/memory.pb.cc
    ${PROF_PROTO_GENS_DIR}/memory.grpc.pb.cc
)

include_directories(${PROF_PROTO_GENS_DIR})
set_source_files_properties(${PROTO_SRCS} PROPERTIES GENERATED TRUE)
source_group("service\\proto" FILES ${PROTO_SRCS})

set(SRV_SRCS
    src/profiler_service.h
    src/profiler_service.cpp
    src/cpu_service.h
    src/cpu_service.cpp
    src/gpu_service.h
    src/gpu_service.cpp
    src/memory_service.h
    src/memory_service.cpp
)
source_group("service\\impl" FILES ${SRV_SRCS})

set(INTER_SRCS
    include/android_profiler.h
    src/android_profiler.cpp
)
source_group(public FILES ${INTER_SRCS})

add_library(libandroid_profiler SHARED
    ${INTER_SRCS}
    ${SRV_SRCS}
    ${PROTO_SRCS}
)

target_add_proto(libandroid_profiler PROTOS
  src/proto/cpu.proto
  src/proto/profiler.proto
  src/proto/profiler_service.proto
  src/proto/agent_service.proto
  src/proto/graphics.proto
  src/proto/event.proto
  src/proto/io.proto
  src/proto/memory.proto
  src/proto/network.proto
)
if(MSVC)
add_definitions(/wd4146)
endif()
target_link_libraries(libandroid_profiler grpc grpc++ libprotobuf)
target_compile_definitions(libandroid_profiler PRIVATE LIB_BUILD=1 BUILD_SHARED_LIB=1)

add_executable(perfd_connector test/perfd_connect.cpp)
target_link_libraries(perfd_connector libandroid_profiler)
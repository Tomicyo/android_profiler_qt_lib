get_filename_component(_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

if(WIN32)
set(THIRD_PARTY_LIBDIR_DEBUG ${_install_prefix}/lib/win64_vc150d)
set(THIRD_PARTY_LIBDIR_RELEASE ${_install_prefix}/lib/win64_vc150r)
elseif(LINUX)
set(THIRD_PARTY_LIBDIR_DEBUG ${_install_prefix}/lib/linux64d)
set(THIRD_PARTY_LIBDIR_RELEASE ${_install_prefix}/lib/linux64r)
elseif(MACOS)
set(THIRD_PARTY_LIBDIR_DEBUG ${_install_prefix}/lib/osx64d)
set(THIRD_PARTY_LIBDIR_RELEASE ${_install_prefix}/lib/osx64r)
elseif(ANDROID)
set(THIRD_PARTY_LIBDIR_DEBUG ${_install_prefix}/lib/${ANDROID_ABI}_${ANDROID_STL}_debug)
set(THIRD_PARTY_LIBDIR_RELEASE ${_install_prefix}/lib/${ANDROID_ABI}_${ANDROID_STL}_release)
endif()

set(THIRD_PARTY_INCLUDE_DIR "${_install_prefix}/include")
include_directories(${_install_prefix}/include)

macro(_imported_target_properties LIBNS TNAME LIB_TYPE Configuration IMPLIB_NAME)
    set_property(TARGET ${LIBNS}::${TNAME} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})
    if("${LIB_TYPE}" STREQUAL "STATIC")
        set_target_properties(${LIBNS}::${TNAME} PROPERTIES
        "IMPORTED_LOCATION_${Configuration}" "${THIRD_PARTY_LIBDIR_${Configuration}}/${IMPLIB_NAME}")
    else()
        set_target_properties(${LIBNS}::${TNAME} PROPERTIES
        "IMPORTED_IMPLIB_${Configuration}" "${THIRD_PARTY_LIBDIR_${Configuration}}/${IMPLIB_NAME}")
    endif()
endmacro()

macro(_imported_target_with_debug_fix LIBNS TNAME LIB_TYPE)
    add_library(${LIBNS}::${TNAME} ${LIB_TYPE} IMPORTED)
    if(WIN32)
        _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "${TNAME}.lib" )
        _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "${TNAME}d.lib")
    elseif(UNIX OR ANDROID)
        if("${LIB_TYPE}" STREQUAL "SHARED")
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "lib${TNAME}.so" )
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "lib${TNAME}d.so")
        else()
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "lib${TNAME}.a" )
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "lib${TNAME}d.a")
        endif()
    endif()
endmacro()

_imported_target_with_debug_fix(KHR glslang STATIC)
_imported_target_with_debug_fix(KHR HLSL STATIC)
_imported_target_with_debug_fix(KHR OGLCompiler STATIC)
_imported_target_with_debug_fix(KHR OSDependent STATIC)
_imported_target_with_debug_fix(KHR SPIRV STATIC)
_imported_target_with_debug_fix(KHR SPVRemapper STATIC)

set(GLSLANG_LIBRARIES KHR::glslang KHR::HLSL KHR::OGLCompiler KHR::OSDependent KHR::SPIRV KHR::SPVRemapper)

_imported_target_with_debug_fix(GTEST gtest STATIC)
_imported_target_with_debug_fix(GTEST gtest_main STATIC)
_imported_target_with_debug_fix(GTEST gmock STATIC)
_imported_target_with_debug_fix(GTEST gmock_main STATIC)

set(GTEST_LIBRARIES GTEST::gtest GTEST::gtest_main)

macro(_imported_target LIBNS TNAME LIB_TYPE)
    add_library(${LIBNS}::${TNAME} ${LIB_TYPE} IMPORTED)
    if(WIN32)
        _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "${TNAME}.lib" )
        _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "${TNAME}.lib")
    elseif(UNIX OR ANDROID)
        if("${LIB_TYPE}" STREQUAL "SHARED")
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "lib${TNAME}.so" )
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "lib${TNAME}.so")
        else()
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} RELEASE "lib${TNAME}.a" )
            _imported_target_properties(${LIBNS} ${TNAME} ${LIB_TYPE} DEBUG "lib${TNAME}.a")
        endif()
    endif()
endmacro()

_imported_target(KHR spirv-cross-core STATIC)
_imported_target(KHR spirv-cross-cpp STATIC)
_imported_target(KHR spirv-cross-glsl STATIC)
_imported_target(KHR spirv-cross-hlsl STATIC)
_imported_target(KHR spirv-cross-msl STATIC)

set(SPIRVCROSS_LIBRARIES 
KHR::spirv-cross-core
KHR::spirv-cross-cpp
KHR::spirv-cross-glsl
KHR::spirv-cross-hlsl
KHR::spirv-cross-msl
)

_imported_target(KHR SPIRV-Tools STATIC)
_imported_target(KHR SPIRV-Tools-comp STATIC)
_imported_target(KHR SPIRV-Tools-opt STATIC)

set(SPIRVTOOLS_LIBRARIES 
KHR::SPIRV-Tools
KHR::SPIRV-Tools-comp
KHR::SPIRV-Tools-opt
)

_imported_target(SQL SQLite3 STATIC)
set(SQLITE3_LIB SQL::SQLite3)

if(WIN32)
    macro(_imported_target_only_release LIBNS TNAME)
    add_library(${LIBNS}::${TNAME} SHARED IMPORTED)
    set_property(TARGET ${LIBNS}::${TNAME} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
    set_property(TARGET ${LIBNS}::${TNAME} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
    if(WIN32)
        set_target_properties(${LIBNS}::${TNAME} PROPERTIES
        "IMPORTED_IMPLIB_DEBUG" "${THIRD_PARTY_LIBDIR_RELEASE}/${TNAME}.lib"
        )
        set_target_properties(${LIBNS}::${TNAME} PROPERTIES
        "IMPORTED_IMPLIB_RELEASE" "${THIRD_PARTY_LIBDIR_RELEASE}/${TNAME}.lib"
        )
    endif()
    endmacro()

    _imported_target_only_release(V8 v8.dll)
    _imported_target_only_release(V8 v8_libbase.dll)
    _imported_target_only_release(V8 v8_libplatform.dll)
    _imported_target_only_release(V8 icuuc.dll)
    _imported_target_only_release(V8 icui18n.dll)

    set(V8_LIBRARIES 
    V8::v8.dll V8::v8_libbase.dll V8::v8_libplatform.dll
    V8::icuuc.dll V8::icui18n.dll
    )

    _imported_target_with_debug_fix(tr plist STATIC)
    _imported_target_with_debug_fix(tr imobiledevice STATIC)
    set(IMOBILEDEVICE_LIBRARIES tr::plist tr::imobiledevice)

    _imported_target(VK vulkan-1 STATIC)
    set(VULKAN_LIBRARIES VK::vulkan-1)

    _imported_target_only_release(SSL libcrypto)
    _imported_target_only_release(SSL libssl)
    set(OPENSSL_LIBRARIES SSL::libcrypto SSL::libssl)

elseif(LINUX)
    find_library(VULKAN_LIB vulkan
            PATHS
            /usr/lib/x86_64-linux-gnu
            /usr/lib/x86-linux-gnu)
    set(VULKAN_LIBRARIES ${VULKAN_LIB})
elseif(ANDROID)
    set(VULKAN_LIBRARIES vulkan)
endif()

_imported_target(FREETYPE freetype STATIC)
set(FREETYPE_LIBRARIES FREETYPE::freetype)

if(NOT ANDROID)
    _imported_target_with_debug_fix(util zlib STATIC)
    set(ZLIB_LIBRARIES util::zlib)
endif()

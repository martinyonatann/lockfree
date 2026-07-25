cmake_minimum_required(VERSION 3.28)

project(lockfree
    VERSION 0.1.0
    DESCRIPTION "Modern C++ lock-free data structures"
    LANGUAGES CXX
)

add_library(lockfree INTERFACE)

target_compile_features(lockfree
    INTERFACE
        cxx_std_23
)

target_include_directories(lockfree
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(benchmark)
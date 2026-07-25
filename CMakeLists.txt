cmake_minimum_required(VERSION 3.20)
project(lockfree VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(lockfree INTERFACE)
target_include_directories(lockfree INTERFACE include)

# Enable testing
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Benchmarks
add_subdirectory(benchmark)
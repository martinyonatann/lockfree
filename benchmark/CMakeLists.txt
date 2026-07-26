find_package(benchmark REQUIRED)

add_executable(spsc_queue_benchmark
    spsc_queue_concurrent_benchmark.cpp
    spsc_queue_mutex_benchmark.cpp
    spsc_queue_pop_benchmark.cpp
    spsc_queue_push_benchmark.cpp
    spsc_queue_push_pop_benchmark.cpp
    mpsc_queue_benchmark.cpp
)

target_link_libraries(spsc_queue_benchmark
    PRIVATE
        lockfree
        benchmark::benchmark
)

target_compile_features(spsc_queue_benchmark PRIVATE cxx_std_20)
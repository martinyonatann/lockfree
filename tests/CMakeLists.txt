add_executable(cacheline_test
    cacheline_test.cpp
    atomic_test.cpp
    ring_buffer_test.cpp
)

target_link_libraries(cacheline_test
    PRIVATE
        lockfree
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(cacheline_test)
#include <atomic>
#include <gtest/gtest.h>
#include <lockfree/atomic.hpp>

TEST(Atomic, LoadAcquire)
{
    const int rhs = 42;
    std::atomic<int> value(rhs);
    EXPECT_EQ(lockfree::loadAcquire(value), rhs);
}

TEST(Atomic, StoreRelease)
{
    const int desired = 100;
    std::atomic<int> value{0};
    lockfree::storeRelease(value, desired);
    EXPECT_EQ(value.load(), desired);
}

TEST(Atomic, CompareExchangeStrong)
{
    std::atomic<int> value(1);
    int expected = 1;

    EXPECT_TRUE(lockfree::compareExchageStrong(value, expected, 2));
    EXPECT_EQ(value.load(), 2);
}
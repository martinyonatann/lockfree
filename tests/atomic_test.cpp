#include <atomic>
#include <gtest/gtest.h>
#include <lockfree/atomic.hpp>

TEST(Atomic, LoadAcquire)
{
    std::atomic<int> value(42);
    EXPECT_EQ(lockfree::loadAcquire(value), 42);
}

TEST(Atomic, StoreRelease)
{
    std::atomic<int> value{0};
    lockfree::storeRelease(value, 100);
    EXPECT_EQ(value.load(), 100);
}

TEST(Atomic, CompareExchangeStrong)
{
    std::atomic<int> value(1);
    int expected = 1;

    EXPECT_TRUE(lockfree::compareExchageStrong(value, expected, 2));
    EXPECT_EQ(value.load(), 2);
}
#include <lockfree/cacheline.hpp>

#include <gtest/gtest.h>

namespace
{
TEST(CacheLine, CacheLine)
{
    EXPECT_EQ(lockfree::cache_line_size, 64);
}

TEST(CacheLine, Alignment)
{
    EXPECT_EQ(alignof(lockfree::CacheAligned<int>), lockfree::cache_line_size);
}

TEST(CacheLine, PaddingSize)
{
    EXPECT_EQ(sizeof(lockfree::CachePadding), lockfree::cache_line_size);
}

TEST(CacheLine, CacheAlignedStoreValue)
{
    lockfree::CacheAligned<int> value{};
    value.value = 42;

    EXPECT_EQ(value.value, 42);
}
} // namespace
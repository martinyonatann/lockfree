#include <gtest/gtest.h>

#include <lockfree/ring_buffer.hpp>

TEST(RingBuffer, DefaultConstructedIsEmpty)
{
    lockfree::RingBuffer<int, 8> buffer;

    EXPECT_TRUE(buffer.empty());
    EXPECT_FALSE(buffer.full());

    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 8);
}

TEST(RingBuffer, PushOneElement)
{
    lockfree::RingBuffer<int, 8> buffer;

    EXPECT_TRUE(buffer.push(42));

    EXPECT_FALSE(buffer.empty());
    EXPECT_FALSE(buffer.full());
    EXPECT_EQ(buffer.size(), 1);
}
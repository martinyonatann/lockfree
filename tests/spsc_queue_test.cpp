#include <gtest/gtest.h>

#include <lockfree/spsc_queue.hpp>

TEST(SPSCQueue, DefaultConstructedIsEmpty)
{
    lockfree::SPSCQueue<int, 8> queue;

    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.full());
    EXPECT_EQ(queue.capacity(), 8);
}

TEST(SPSCQueue, PushOneElement)
{
    lockfree::SPSCQueue<int, 8> queue;
    EXPECT_TRUE(queue.push(42));
    EXPECT_FALSE(queue.empty());
}

TEST(SPSCQueue, PopOneElement)
{
    lockfree::SPSCQueue<int, 8> queue;
    ASSERT_TRUE(queue.push(42));

    int value = 0;

    ASSERT_TRUE(queue.pop(value));

    EXPECT_EQ(value, 42);
    EXPECT_TRUE(queue.empty());
}
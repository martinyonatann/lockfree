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

TEST(RingBuffer, PopOneElement)
{
    lockfree::RingBuffer<int, 8> buffer;
    ASSERT_TRUE(buffer.push(42));

    int value = 0;

    ASSERT_TRUE(buffer.pop(value));

    EXPECT_EQ(value, 42);
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);
}

TEST(RingBuffer, PopFromEmptyBuffer)
{
    lockfree::RingBuffer<int, 8> buffer;
    int value = 42;
    EXPECT_FALSE(buffer.pop(value));
    EXPECT_EQ(value, 42);
}

TEST(RingBuffer, PushIntoFullBuffer)
{
    lockfree::RingBuffer<int, 2> buffer;

    EXPECT_TRUE(buffer.push(1));
    EXPECT_TRUE(buffer.push(2));

    EXPECT_TRUE(buffer.full());
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_FALSE(buffer.push(3));
    EXPECT_EQ(buffer.size(), 2);
}

TEST(RingBuffer, PreservesFifoOrder)
{
    lockfree::RingBuffer<int, 8> buffer;
    ASSERT_TRUE(buffer.push(10));
    ASSERT_TRUE(buffer.push(20));
    ASSERT_TRUE(buffer.push(30));

    int value = 0;
    ASSERT_TRUE(buffer.pop(value));
    EXPECT_EQ(value, 10);
}

TEST(RingBuffer, WrapAround)
{
    lockfree::RingBuffer<int, 3> buffer;

    int value = 0;

    ASSERT_TRUE(buffer.push(1));
    ASSERT_TRUE(buffer.push(2));
    ASSERT_TRUE(buffer.push(3));

    ASSERT_TRUE(buffer.pop(value));
    EXPECT_EQ(value, 1);

    ASSERT_TRUE(buffer.push(4));

    ASSERT_TRUE(buffer.pop(value));
    EXPECT_EQ(value, 2);

    ASSERT_TRUE(buffer.pop(value));
    EXPECT_EQ(value, 3);

    ASSERT_TRUE(buffer.pop(value));
    EXPECT_EQ(value, 4);

    EXPECT_TRUE(buffer.empty());
}
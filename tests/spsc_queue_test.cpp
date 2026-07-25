#include <gtest/gtest.h>

#include <lockfree/spsc_queue.hpp>

constexpr int DEFAULT_CAPACITY = 8;

TEST(SPSCQueue, DefaultConstructedIsEmpty)
{
    lockfree::SPSCQueue<int, DEFAULT_CAPACITY> queue;

    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.full());
    EXPECT_EQ(queue.capacity(), 8);
}

TEST(SPSCQueue, PushOneElement)
{
    lockfree::SPSCQueue<int, DEFAULT_CAPACITY> queue;
    EXPECT_TRUE(queue.push(42));
    EXPECT_FALSE(queue.empty());
}

TEST(SPSCQueue, PopOneElement)
{
    lockfree::SPSCQueue<int, DEFAULT_CAPACITY> queue;
    ASSERT_TRUE(queue.push(42));

    int value = 0;

    ASSERT_TRUE(queue.pop(value));

    EXPECT_EQ(value, 42);
    EXPECT_TRUE(queue.empty());
}

TEST(SPSCQueue, QueueBecomesFullAfterCapacityMinusOneElements)
{
    lockfree::SPSCQueue<int, 4> queue;

    EXPECT_TRUE(queue.push(1));
    EXPECT_TRUE(queue.push(2));
    EXPECT_TRUE(queue.push(3));

    EXPECT_TRUE(queue.full());
    EXPECT_FALSE(queue.push(4));
}

TEST(SPSCQueue, PreservesFifoOrder)
{
    lockfree::SPSCQueue<int, DEFAULT_CAPACITY> queue;
    ASSERT_TRUE(queue.push(10));
    ASSERT_TRUE(queue.push(20));
    ASSERT_TRUE(queue.push(30));

    int value = 0;

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 10);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 20);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 30);

    EXPECT_TRUE(queue.empty());
}

TEST(SPSCQueue, WrapAround)
{
    lockfree::SPSCQueue<int, 4> queue;

    int value = 0;

    ASSERT_TRUE(queue.push(1));
    ASSERT_TRUE(queue.push(2));
    ASSERT_TRUE(queue.push(3));

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 1);

    ASSERT_TRUE(queue.push(4));

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 2);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 3);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 4);

    EXPECT_TRUE(queue.empty());
}

TEST(SPSCQueue, ProducerConsumer)
{
    lockfree::SPSCQueue<int, 1024> queue;

    constexpr int N = 100000;

    std::thread producer(
        [&]
        {
            for (int i = 0; i < N;)
            {
                if (queue.push(i))
                {
                    ++i;
                }
            }
        });

    std::thread consumer(
        [&]
        {
            int expected = 0;
            int value = 0;

            while (expected < N)
            {
                if (queue.pop(value))
                {
                    EXPECT_EQ(value, expected);
                    ++expected;
                }
            }
        });

    producer.join();
    consumer.join();
}
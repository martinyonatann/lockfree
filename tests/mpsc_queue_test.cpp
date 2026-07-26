#include <gtest/gtest.h>
#include <unordered_set>

#include "lockfree/mpsc_queue.hpp"

constexpr int DEFAULT_CAPACITY = 8;

TEST(MPSCQueue, DefaultConstructedIsEmpty)
{
    lockfree::MPSCQueue<int, DEFAULT_CAPACITY> queue;

    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.full());
    EXPECT_EQ(queue.capacity(), 8);
}

TEST(MPSCQueue, PushOneElement)
{
    lockfree::MPSCQueue<int, DEFAULT_CAPACITY> queue;

    EXPECT_TRUE(queue.push(10));
    EXPECT_FALSE(queue.empty());
}

TEST(MPSCQueue, PopOneElement)
{
    lockfree::MPSCQueue<int, DEFAULT_CAPACITY> queue;

    ASSERT_TRUE(queue.push(10));

    int value = 0;

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 10);
    EXPECT_TRUE(queue.empty());
}

TEST(MPSCQueue, PopFromEmptyQueue)
{
    lockfree::MPSCQueue<int, DEFAULT_CAPACITY> queue;

    int value = 0;

    EXPECT_FALSE(queue.pop(value));
    EXPECT_TRUE(queue.empty());
}

TEST(MPSCQueue, QueueBecomesFullAfterCapacityMinusOneElements)
{
    lockfree::MPSCQueue<int, 4> queue;

    EXPECT_TRUE(queue.push(1));
    EXPECT_TRUE(queue.push(2));
    EXPECT_TRUE(queue.push(3));

    EXPECT_TRUE(queue.full());

    EXPECT_FALSE(queue.push(4));
}

TEST(MPSCQueue, PreservesFifoOrder)
{
    lockfree::MPSCQueue<int, DEFAULT_CAPACITY> queue;

    int value = 0;

    ASSERT_TRUE(queue.push(10));
    ASSERT_TRUE(queue.push(20));
    ASSERT_TRUE(queue.push(30));

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 10);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 20);

    ASSERT_TRUE(queue.pop(value));
    EXPECT_EQ(value, 30);

    EXPECT_TRUE(queue.empty());
}

TEST(MPSCQueue, WrapAround)
{
    lockfree::MPSCQueue<int, 4> queue;

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

TEST(MPSCQueue, MultipleProducersCanPushConcurrently)
{
    constexpr std::size_t ProducerCount = 4;
    constexpr std::size_t ItemsPerProducer = 1000;

    lockfree::MPSCQueue<int, 8192> queue;

    std::vector<std::thread> producers;

    for (std::size_t producer = 0; producer < ProducerCount; ++producer)
    {
        producers.emplace_back(
            [&, producer]
            {
                const int start = static_cast<int>(producer * ItemsPerProducer);

                for (int i = 0; i < ItemsPerProducer; ++i)
                {
                    while (!queue.push(start + i))
                    {
                        std::this_thread::yield();
                    }
                }
            });
    }

    for (auto& producer : producers)
    {
        producer.join();
    }

    std::unordered_set<int> values;

    int value = 0;

    while (queue.pop(value))
    {
        values.insert(value);
    }

    EXPECT_EQ(values.size(), ProducerCount * ItemsPerProducer);

    for (int i = 0; i < static_cast<int>(ProducerCount * ItemsPerProducer); ++i)
    {
        EXPECT_TRUE(values.contains(i));
    }
}
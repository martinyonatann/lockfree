#include "lockfree/spsc_queue.hpp"
#include <benchmark/benchmark.h>
#include <thread>

static void BM_SPSCQueueProducerConsumer(benchmark::State& state)
{
    constexpr int kItems = 100000;

    for (auto _ : state)
    {
        lockfree::SPSCQueue<int, 1024> queue;

        std::thread producer(
            [&]()
            {
                for (int i = 0; i < kItems;)
                {
                    if (queue.push(i))
                    {
                        ++i;
                    }
                }
            });

        std::thread consumer(
            [&]()
            {
                int expected = 0;
                int value = 0;

                while (expected < kItems)
                {
                    if (queue.pop(value))
                    {
                        benchmark::DoNotOptimize(value);
                        ++expected;
                    }
                }
            });

        producer.join();
        consumer.join();
    }
}

BENCHMARK(BM_SPSCQueueProducerConsumer);
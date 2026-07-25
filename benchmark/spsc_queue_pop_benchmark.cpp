#include "lockfree/spsc_queue.hpp"
#include <benchmark/benchmark.h>

static void BM_SPSCQueuePop(benchmark::State& state)
{
    for (auto _ : state)
    {
        lockfree::SPSCQueue<int, 1024> queue;

        for (int i = 0; i < 1023; ++i)
        {
            queue.push(i);
        }

        int value{};

        for (int i = 0; i < 1023; ++i)
        {
            benchmark::DoNotOptimize(queue.pop(value));
            benchmark::DoNotOptimize(value);
        }
    }
}

BENCHMARK(BM_SPSCQueuePop);
BENCHMARK_MAIN();
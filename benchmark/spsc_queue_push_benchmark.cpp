#include "lockfree/spsc_queue.hpp"
#include <benchmark/benchmark.h>

// SPSC Queue - Push
static void BM_SPSCQueuePush(benchmark::State& state)
{
    for (auto _ : state)
    {
        lockfree::SPSCQueue<int, 1024> queue;

        for (int i = 0; i < 1023; ++i)
        {
            benchmark::DoNotOptimize(queue.push(i));
        }
    }
}

BENCHMARK(BM_SPSCQueuePush);
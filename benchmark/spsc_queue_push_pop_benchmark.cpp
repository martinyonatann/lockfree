#include "lockfree/spsc_queue.hpp"
#include <benchmark/benchmark.h>

static void BM_SPSCQueuePushPop(benchmark::State& state)
{
    lockfree::SPSCQueue<int, 1024> queue;

    for (auto _ : state)
    {
        int value{};

        benchmark::DoNotOptimize(queue.push(42));
        benchmark::DoNotOptimize(queue.pop(value));
        benchmark::DoNotOptimize(value);
    }
}

BENCHMARK(BM_SPSCQueuePushPop);
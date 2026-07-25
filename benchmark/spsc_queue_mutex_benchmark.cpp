#include <benchmark/benchmark.h>

#include <mutex>
#include <queue>

static void BM_StdQueueMutex(benchmark::State& state)
{
    std::queue<int> queue;
    std::mutex mutex;

    for (auto _ : state)
    {
        int value{};

        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(42);
        }

        {
            std::lock_guard<std::mutex> lock(mutex);

            value = queue.front();
            queue.pop();
        }

        benchmark::DoNotOptimize(value);
    }
}

BENCHMARK(BM_StdQueueMutex);
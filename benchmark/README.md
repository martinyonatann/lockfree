# Benchmarks

This document describes the benchmark suite used by the LockFree library.

## Goals

The benchmark suite is designed to:

- Measure latency and throughput
- Detect performance regressions
- Compare implementations across releases
- Validate optimization efforts

## Environment

| Item                | Value            |
| ------------------- | ---------------- |
| Benchmark Framework | Google Benchmark |
| Compiler            | Clang 18         |
| Build Type          | Release          |
| C++ Standard        | C++23            |

## Benchmarks

### SPSC Queue

- Push
- Pop
- Push + Pop
- Producer / Consumer

### Baseline

- std::queue + std::mutex

## Running Benchmarks

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

./build/benchmark/spsc_queue_benchmark
```

## Export Results

JSON

```bash
./build/benchmark/spsc_queue_benchmark \
    --benchmark_out=benchmark/benchmark-results/v0.2.0.json \
    --benchmark_out_format=json
```

Raw Output

```bash
./build/benchmark/spsc_queue_benchmark \
    > benchmark/benchmark-results/v0.2.0.txt
```

## Historical Results

Benchmark outputs are stored in:

```text
benchmark/benchmark-results/
```

Each tagged release includes its corresponding benchmark artifacts to allow performance tracking over time.

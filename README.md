# LockFree

> A modern C++23 library for learning and building lock-free data structures, low-latency algorithms, and high-performance concurrent systems inspired by High-Frequency Trading (HFT).

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Build](https://img.shields.io/badge/build-CMake-orange)

---

## Overview

**LockFree** is an educational, performance-oriented C++ project that explores the design and implementation of lock-free data structures using modern C++23.

The project focuses on understanding how professional low-latency systems are built, emphasizing correctness, performance, and clean engineering practices.

Topics include:

- Lock-free programming
- C++ memory model
- Memory ordering
- Cache-friendly data structures
- Low-latency system design
- High-throughput concurrent algorithms

Every component is developed incrementally using:

- Test-Driven Development (TDD)
- Benchmarks
- Performance analysis
- Documentation

---

## Current Status

### Implemented

- Cacheline utilities
- Atomic utilities
- Ring Buffer
- Lock-Free SPSC Queue
- Unit tests (GoogleTest)
- Benchmarks (Google Benchmark)

### In Progress

- Benchmark optimization
- Performance analysis
- Documentation

### Planned

- Memory Pool
- MPSC Queue
- SPMC Queue
- MPMC Queue
- Hazard Pointers
- Epoch-Based Reclamation

---

## Goals

- Learn modern C++23
- Master lock-free programming
- Understand the C++ memory model
- Build reusable concurrent data structures
- Benchmark and optimize performance
- Document design decisions and trade-offs
- Build a strong systems programming / HFT portfolio

---

## Roadmap

| Version | Milestone                                  | Status |
| ------- | ------------------------------------------ | :----: |
| v0.1.0  | Foundation (Cacheline, Atomic, RingBuffer) |   ✅   |
| v0.2.0  | Lock-Free SPSC Queue                       |   ✅   |
| v0.3.0  | Benchmark Suite                            |   🚧   |
| v0.4.0  | Memory Pool                                |   ⬜   |
| v0.5.0  | MPSC Queue                                 |   ⬜   |
| v0.6.0  | SPMC Queue                                 |   ⬜   |
| v0.7.0  | MPMC Queue                                 |   ⬜   |
| v1.0.0  | Stable Release                             |   ⬜   |

---

## Components

### Core

- Cacheline utilities
- Atomic helpers
- Memory barriers _(planned)_
- Lock-free memory pool _(planned)_

### Data Structures

- Ring Buffer
- SPSC Queue
- MPSC Queue _(planned)_
- SPMC Queue _(planned)_
- MPMC Queue _(planned)_

### Utilities

- Spinlock _(planned)_
- Object Pool _(planned)_
- Hazard Pointer _(planned)_
- Epoch-Based Reclamation _(planned)_

---

## Benchmarks

Benchmarks are implemented using **Google Benchmark** to measure throughput and latency.

### Environment

| Item      | Value                      |
| --------- | -------------------------- |
| CPU       | AMD Ryzen 7 5800H (8C/16T) |
| Compiler  | Clang 18                   |
| OS        | Ubuntu 24.04 LTS           |
| Framework | Google Benchmark           |

### Current Benchmarks

- SPSC Queue - Push
- SPSC Queue - Pop
- SPSC Queue - Push + Pop
- SPSC Queue - Producer / Consumer
- std::queue + std::mutex (baseline)

> **Note**
>
> Benchmark results are hardware-dependent and intended primarily for regression tracking between releases rather than absolute performance comparisons.

---

## Repository Structure

```text
lockfree/
├── benchmark/
├── docs/
├── examples/
├── include/
│   └── lockfree/
├── tests/
├── CMakeLists.txt
└── README.md
```

---

## Building

### Requirements

- C++23 compatible compiler
- CMake 3.20+
- GoogleTest
- Google Benchmark

### Build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run Tests

```bash
ctest --test-dir build --output-on-failure
```

### Run Benchmarks

```bash
./build/benchmark/spsc_queue_benchmark
```

---

## Technologies

| Category     | Technology                 |
| ------------ | -------------------------- |
| Language     | C++23                      |
| Build System | CMake                      |
| Testing      | GoogleTest                 |
| Benchmark    | Google Benchmark           |
| Formatter    | clang-format               |
| Linter       | clang-tidy                 |
| CI           | GitHub Actions _(planned)_ |

---

## Learning Topics

This repository explores:

- Modern C++
- Concurrency
- `std::atomic`
- Memory Ordering
- Compare-and-Swap (CAS)
- Lock-Free Programming
- Cache Coherency
- False Sharing
- NUMA
- CPU Cache
- Performance Profiling
- High-Performance Data Structures

---

## Design Philosophy

Every component in this repository should provide:

- Correctness before optimization
- Clean and maintainable code
- Clear thread-safety guarantees
- Unit tests
- Benchmarks
- Design documentation
- Performance discussion

---

## References

- _Effective Modern C++_ — Scott Meyers
- _C++ Concurrency in Action_ — Anthony Williams
- _Computer Systems: A Programmer's Perspective_
- _The Art of Multiprocessor Programming_
- Intel® 64 and IA-32 Architectures Optimization Reference Manual

---

## License

This project is licensed under the MIT License.

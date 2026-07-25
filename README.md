# LockFree

> A modern C++23 lock-free programming library focused on building high-performance, low-latency systems for High-Frequency Trading (HFT), real-time applications, and systems programming.

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Build](https://img.shields.io/badge/build-CMake-orange)

---

## Overview

**LockFree** is an educational and production-oriented project that explores the implementation of lock-free data structures and concurrent algorithms using modern C++.

The primary goal is to understand **how professional low-latency systems are built**, with a strong emphasis on:

- Lock-free programming
- Memory ordering
- Cache-friendly data structures
- Low-latency design
- High-throughput concurrent algorithms

This repository is being built incrementally, with each component designed, benchmarked, and documented in detail.

---

## Goals

- Learn modern C++23
- Master lock-free programming
- Understand the C++ memory model
- Build reusable concurrent data structures
- Measure performance through benchmarks
- Document design decisions and trade-offs
- Serve as a foundation for future HFT projects

---

## Roadmap

| Version | Component           | Status |
| ------- | ------------------- | :----: |
| v0.1    | Project Setup       |   ⬜   |
| v0.2    | Cacheline Utilities |   ⬜   |
| v0.3    | Atomic Utilities    |   ⬜   |
| v0.4    | Ring Buffer         |   ⬜   |
| v0.5    | SPSC Queue          |   ⬜   |
| v0.6    | Memory Pool         |   ⬜   |
| v0.7    | MPMC Queue          |   ⬜   |
| v0.8    | Benchmarks          |   ⬜   |
| v0.9    | Documentation       |   ⬜   |
| v1.0    | Stable Release      |   ⬜   |

---

## Planned Components

### Core

- Cacheline utilities
- Atomic helpers
- Memory barriers
- Lock-free memory pool

### Data Structures

- Ring Buffer
- SPSC Queue
- MPSC Queue
- SPMC Queue
- MPMC Queue

### Utilities

- Spinlock
- Object Pool
- Hazard Pointer _(planned)_
- Epoch-Based Reclamation _(planned)_

### Benchmark

- Throughput
- Latency
- Memory usage
- Cache efficiency
- False sharing analysis

---

## Repository Structure

```text
lockfree/
├── benchmark/
├── docs/
├── examples/
├── include/
│   └── lockfree/
├── src/
├── tests/
├── CMakeLists.txt
└── README.md
```

---

## Technologies

| Category     | Technology       |
| ------------ | ---------------- |
| Language     | C++23            |
| Build System | CMake            |
| Testing      | GoogleTest       |
| Benchmark    | Google Benchmark |
| Formatter    | clang-format     |
| Linter       | clang-tidy       |
| CI           | GitHub Actions   |

---

## Learning Topics

This project covers topics including:

- Modern C++
- Concurrency
- std::atomic
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

## Philosophy

This project prioritizes:

1. Correctness
2. Readability
3. Performance
4. Benchmarking
5. Documentation

Every component should include:

- Design explanation
- Complexity analysis
- Thread-safety guarantees
- Unit tests
- Benchmarks
- Performance discussion

---

## References

- Effective Modern C++
- C++ Concurrency in Action
- Computer Systems: A Programmer's Perspective
- The Art of Multiprocessor Programming
- Intel® 64 and IA-32 Architectures Optimization Reference Manual

---

## License

MIT License

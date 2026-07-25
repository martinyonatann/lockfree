#pragma once

#include <cstddef>

namespace lockfree
{
/// Typical cache line size on modern x86_64 processors.
/// Most Intel and AMD CPUs use a 64-byte cache line.
inline constexpr std::size_t cache_line_size = 64;

/// Align a type to the CPU cache line size.
///
/// Example:
/// CacheAligned<std::atomic<uint64_t> counter;
template <typename T> struct alignas(cache_line_size) CacheAligned
{
    T value;
};

/// Paddomg utility to separate frequently modified data and
/// reduce the chance of false sharing.
struct alignas(cache_line_size) CachePadding
{
    std::byte data[cache_line_size];
};

} // namespace lockfree
#pragma once
#include <atomic>

namespace lockfree
{
using std::memory_order;
using std::memory_order_acq_rel;
using std::memory_order_acquire;
using std::memory_order_relaxed;
using std::memory_order_release;
using std::memory_order_seq_cst;

template <typename T>
[[nodiscard]]
inline T loadAcquire(const std::atomic<T>& value) noexcept
{
    return value.load(std::memory_order_acquire);
}

template <typename T> inline void storeRelease(std::atomic<T>& value, T desired) noexcept
{
    value.store(desired, std::memory_order_release);
}

template <typename T>
[[nodiscard]]
inline bool compareExchangeWeak(std::atomic<T>& value, T& expected, T desired,
                                std::memory_order success = std::memory_order_acq_rel,
                                std::memory_order failure = std::memory_order_acquire) noexcept
{
    return value.compare_exchange_weak(expected, desired, success, failure);
}

template <typename T>
[[nodiscard]]
inline bool compareExchageStrong(std::atomic<T>& value, T& expected, T disired,
                                 std::memory_order success = std::memory_order_acq_rel,
                                 std::memory_order failure = std::memory_order_acquire)
{
    return value.compare_exchange_strong(expected, disired, success, failure);
}
} // namespace lockfree
#pragma once

#include "lockfree/atomic.hpp"
#include <array>
#include <atomic>
#include <cstddef>

using std::atomic;

namespace lockfree
{
template <typename T, std::size_t Capacity> class MPSCQueue
{
  public:
    MPSCQueue() = default;

    auto push(const T& value) -> bool;
    auto pop(T& value) -> bool;

    auto empty() const noexcept -> bool;
    auto full() const noexcept -> bool;
    constexpr auto capacity() const noexcept -> std::size_t;

  private:
    std::array<T, Capacity> buffer_;
    atomic<std::size_t> head_{0};
    atomic<std::size_t> tail_{0};
};

template <typename T, std::size_t Capacity>
constexpr auto MPSCQueue<T, Capacity>::capacity() const noexcept -> std::size_t
{
    return Capacity;
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::full() const noexcept -> bool
{
    const auto tail = lockfree::loadAcquire(tail_);
    const auto head = lockfree::loadAcquire(head_);

    return ((tail + 1) % Capacity) == head;
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::empty() const noexcept -> bool
{
    return lockfree::loadAcquire(head_) == lockfree::loadAcquire(tail_);
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::push(const T& value) -> bool
{
    if (full())
    {
        return false;
    }

    const auto tail = lockfree::loadAcquire(tail_);
    const auto next_tail = (tail + 1) % Capacity;

    buffer_[tail] = value;

    lockfree::storeRelease(tail_, next_tail);

    return true;
}

template <typename T, std::size_t Capacity> auto MPSCQueue<T, Capacity>::pop(T& value) -> bool
{
    if (empty())
    {
        return false;
    }

    const auto head = lockfree::loadAcquire(head_);
    const auto next_head = (head + 1) % Capacity;

    value = buffer_[head];

    lockfree::storeRelease(head_, next_head);

    return true;
}

} // namespace lockfree
#pragma once

#include <array>
#include <atomic>
#include <cstddef>
namespace lockfree
{
template <typename T, std::size_t Capacity> class MPSCQueue
{
  public:
    auto push(const T& value) -> bool;
    auto pop(T& value) -> bool;

    auto empty() const noexcept -> bool;
    auto full() const noexcept -> bool;
    constexpr auto capacity() const noexcept -> std::size_t;

  private:
    std::array<T, Capacity> buffer_{};

    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};
};

template <typename T, std::size_t Capacity>
constexpr auto MPSCQueue<T, Capacity>::capacity() const noexcept -> std::size_t
{
    return Capacity;
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::full() const noexcept -> bool
{
    const auto tail = tail_.load(std::memory_order_acquire);
    const auto head = head_.load(std::memory_order_acquire);

    return ((tail + 1) % Capacity) == head;
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::empty() const noexcept -> bool
{
    return head_.load(std::memory_order_acquire) == tail_.load(std::memory_order_acquire);
}

template <typename T, std::size_t Capacity>
auto MPSCQueue<T, Capacity>::push(const T& value) -> bool
{
    if (full())
    {
        return false;
    }

    const auto tail = tail_.load(std::memory_order_relaxed);
    const auto next_tail = (tail + 1) % Capacity;

    buffer_[tail] = value;
    tail_.store(next_tail, std::memory_order_release);

    return true;
}

template <typename T, std::size_t Capacity> auto MPSCQueue<T, Capacity>::pop(T& value) -> bool
{
    if (empty())
    {
        return false;
    }

    const auto head = head_.load(std::memory_order_relaxed);
    const auto next_head = (head + 1) % Capacity;

    value = buffer_[head];
    head_.store(next_head, std::memory_order_release);
    return true;
}
} // namespace lockfree
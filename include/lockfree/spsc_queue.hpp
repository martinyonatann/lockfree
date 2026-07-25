#pragma once

#include <array>
#include <atomic>
#include <cstddef>
namespace lockfree
{
template <typename T, std::size_t Capacity> class SPSCQueue
{
  public:
    auto push(const T& value) -> bool;
    auto pop(T& value) -> bool;

    [[nodiscard]]
    auto empty() const noexcept -> bool;

    [[nodiscard]]
    auto full() const noexcept -> bool;

    [[nodiscard]]
    constexpr auto capacity() const noexcept -> std::size_t;

  private:
    std::array<T, Capacity> buffer_{};

    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};

    [[nodiscard]]
    static constexpr auto next_index(std::size_t index) noexcept -> std::size_t
    {
        return (index + 1) % Capacity;
    }
};

template <typename T, std::size_t Capacity>
constexpr auto SPSCQueue<T, Capacity>::capacity() const noexcept -> std::size_t
{
    return Capacity;
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::full() const noexcept -> bool
{
    const auto tail = tail_.load(std::memory_order_acquire);
    const auto head = head_.load(std::memory_order_acquire);

    return ((tail + 1) % Capacity) == head;
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::empty() const noexcept -> bool
{
    return head_.load(std::memory_order_acquire) == tail_.load(std::memory_order_acquire);
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::push(const T& value) -> bool
{
    const auto tail = tail_.load(std::memory_order_relaxed);
    const auto head = head_.load(std::memory_order_acquire);

    const auto next_tail = next_index(tail);

    if (next_tail == head)
    {
        return false;
    }

    buffer_[tail] = value;

    tail_.store(next_tail, std::memory_order_release);

    return true;
}

template <typename T, std::size_t Capacity> auto SPSCQueue<T, Capacity>::pop(T& value) -> bool
{
    const auto head = head_.load(std::memory_order_relaxed);
    const auto tail = tail_.load(std::memory_order_acquire);

    if (head == tail)
    {
        return false;
    }

    value = buffer_[head];

    const auto next_head = (head + 1) % Capacity;

    head_.store(next_head, std::memory_order_release);

    return true;
}
} // namespace lockfree

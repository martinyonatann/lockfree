#pragma once

#include <array>
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

    std::size_t head_{0};
    std::size_t tail_{0};
    bool empty_{true};
};

template <typename T, std::size_t Capacity>
constexpr auto SPSCQueue<T, Capacity>::capacity() const noexcept -> std::size_t
{
    return Capacity;
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::full() const noexcept -> bool
{
    return false;
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::empty() const noexcept -> bool
{
    return empty_;
}

template <typename T, std::size_t Capacity>
auto SPSCQueue<T, Capacity>::push(const T& value) -> bool
{
    if (full())
    {
        return false;
    }

    buffer_[tail_] = value;
    ++tail_;
    empty_ = false;

    return true;
}

template <typename T, std::size_t Capacity> auto SPSCQueue<T, Capacity>::pop(T& value) -> bool
{
    if (empty())
    {
        return false;
    }

    value = buffer_[head_];
    ++head_;

    empty_ = true;

    return true;
}
} // namespace lockfree

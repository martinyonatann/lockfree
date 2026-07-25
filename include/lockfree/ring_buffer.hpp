#pragma once

#include <array>
#include <cstddef>

namespace lockfree
{

template <typename T, std::size_t Capacity> class RingBuffer
{
  public:
    RingBuffer() = default;

    auto push(const T&) -> bool;

    [[nodiscard]]
    auto empty() const noexcept -> bool;

    [[nodiscard]]
    auto full() const noexcept -> bool;

    [[nodiscard]]
    auto size() const noexcept -> std::size_t;

    [[nodiscard]]
    constexpr auto capacity() const noexcept -> std::size_t;

  private:
    std::array<T, Capacity> buffer_{};

    std::size_t head_{0};
    std::size_t tail_{0};
    std::size_t size_{0};
};

template <typename T, std::size_t Capacity>
auto RingBuffer<T, Capacity>::empty() const noexcept -> bool
{
    return size_ == 0;
}

template <typename T, std::size_t Capacity>
auto RingBuffer<T, Capacity>::full() const noexcept -> bool
{
    return size_ == Capacity;
}

template <typename T, std::size_t Capacity>
auto RingBuffer<T, Capacity>::size() const noexcept -> std::size_t
{
    return size_;
}

template <typename T, std::size_t Capacity>
constexpr auto RingBuffer<T, Capacity>::capacity() const noexcept -> std::size_t
{
    return Capacity;
}

template <typename T, std::size_t Capacity>
auto RingBuffer<T, Capacity>::push(const T& value) -> bool
{
    if (full())
    {
        return false;
    }

    buffer_[tail_] = value;
    ++tail_;
    ++size_;

    return true;
}

} // namespace lockfree
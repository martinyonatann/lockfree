#pragma once

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
    // TODO
};
} // namespace lockfree
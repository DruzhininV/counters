#ifndef COUNTERS_COUNTER_ARRAY_H
#define COUNTERS_COUNTER_ARRAY_H

#include "index_range.h"

#include <array>

namespace tools {

template<typename T, typename Range>
class CounterArray {
public:
    using Index = typename Range::index_type;
    using Array = std::array<T, Range::size()>;

    constexpr CounterArray() noexcept { reset(); }

    constexpr void increment(Index value) noexcept {
      ++counters_[Range::index(value)];
    }

    constexpr T count(Index value) const noexcept {
      return counters_[Range::index(value)];
    }

    static constexpr bool is_index_valid(Index value) noexcept {
      return Range::is_valid(value);
    }

    constexpr void reset() noexcept {
      for(std::size_t i = 0; i < counters_.size(); ++i) {
        counters_[i] = T{0};
      }
    }

    constexpr CounterArray &operator+=(const CounterArray &rhs) noexcept {
      for (std::size_t i = 0; i < counters_.size(); ++i) {
        counters_[i] += rhs.counters_[i];
      }
      return *this;
    }

    friend constexpr CounterArray operator+(CounterArray lhs, const CounterArray &rhs) noexcept {
      lhs += rhs;
      return lhs;
    }

private:
    Array counters_{};
};


}


#endif //COUNTERS_COUNTER_ARRAY_H

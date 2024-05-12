#ifndef COUNTERS_INDEX_RANGE_H
#define COUNTERS_INDEX_RANGE_H

#include <type_traits>

namespace tools {

template<typename T>
constexpr auto underlying_value(T value) noexcept -> std::enable_if_t<std::is_integral_v<T>, T> {
  return value;
}

template<typename T>
constexpr auto underlying_value(T value) noexcept -> std::enable_if_t<std::is_enum_v<T>, std::underlying_type_t<T>> {
  return static_cast<std::underlying_type_t<T>>(value);
}

//IndexRange[First, Last]
template<typename Index, Index First, Index Last>
struct IndexRange {
    static_assert(First < Last);
    using index_type = Index;

    static constexpr std::size_t size() noexcept {
      return underlying_value(Last) - underlying_value(First) + 1;
    }

    //Returns the zero-based index
    static constexpr std::size_t index(index_type value) noexcept {
      return underlying_value(value) - underlying_value(First);
    }

    static constexpr bool is_valid(index_type value) noexcept {
      return First <= value && value <= Last;
    }
};


}


#endif //COUNTERS_INDEX_RANGE_H

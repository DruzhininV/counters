
#include "counter_array.h"
#include "index_range.h"

#include <utility>

namespace {
using namespace tools;

constexpr int first = -5;
constexpr int last = 15;
constexpr int mid = 0;
constexpr auto val1 = 12;
constexpr auto val2 = 18;
constexpr auto val3 = 4;

using IntRange = IndexRange<int, first, last>;
using Array = CounterArray<int, IntRange>;

template<typename Index, Index offset, Index... indexes>
constexpr bool int_index(std::integer_sequence<Index, indexes...> index_seq) {
  constexpr Array counters{};

  static_assert((... && (counters.count(indexes + offset) == 0)));

  return true;
}

static_assert(int_index<int, -5>(std::make_integer_sequence<int, 16>()));

template<typename Index>
constexpr Array make_array(Index index, std::size_t count) {
  Array counters{};

  for (std::size_t i = 0; i < count; ++i) {
    counters.increment(index);
  }

  return counters;
}

constexpr void increment_test() {
  constexpr auto arr1 = make_array(first, val1);
  static_assert(arr1.count(first) == val1);
  static_assert(arr1.count(mid) == 0);
  static_assert(arr1.count(last) == 0);

  constexpr auto arr2 = make_array(last, val2);
  static_assert(arr2.count(first) == 0);
  static_assert(arr2.count(mid) == 0);
  static_assert(arr2.count(last) == val2);

  constexpr auto arr3 = make_array(mid, val3);
  static_assert(arr3.count(first) == 0);
  static_assert(arr3.count(mid) == val3);
  static_assert(arr3.count(last) == 0);
}

constexpr void sum_test() {
  constexpr auto arr1 = make_array(first, val1);
  static_assert(arr1.count(first) == val1);
  static_assert(arr1.count(mid) == 0);
  static_assert(arr1.count(last) == 0);

  constexpr auto arr2 = make_array(last, val2);
  static_assert(arr2.count(first) == 0);
  static_assert(arr2.count(mid) == 0);
  static_assert(arr2.count(last) == val2);

  constexpr auto arr3 = make_array(mid, val3);
  static_assert(arr3.count(first) == 0);
  static_assert(arr3.count(mid) == val3);
  static_assert(arr3.count(last) == 0);

  constexpr auto sum = arr1 + arr2 + arr3;
  static_assert(sum.count(first) == val1);
  static_assert(sum.count(mid) == val3);
  static_assert(sum.count(last) == val2);
}

} // namespace;

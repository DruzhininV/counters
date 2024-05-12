
#include "index_range.h"

#include <cstdint>

// tests
namespace {

template<typename Enum>
constexpr auto enum_cast(std::underlying_type_t<Enum> value) -> std::enable_if_t<std::is_enum_v<Enum>, Enum> {
  return static_cast<Enum>(value);
}

using namespace tools;

static_assert(underlying_value(0) == 0);
static_assert(underlying_value(-7) == -7);
static_assert(underlying_value(1ULL) == 1);

enum class Test1 : uint8_t {
    V1, V2, V3,
};

static_assert(underlying_value(Test1::V1) == 0);
static_assert(underlying_value(Test1::V2) == 1);
static_assert(underlying_value(Test1::V3) == 2);

using Range1 = IndexRange<Test1, Test1::V1, Test1::V3>;
static_assert(Range1::size() == 3);
static_assert(Range1::index(Test1::V1) == 0);
static_assert(Range1::index(Test1::V2) == 1);
static_assert(Range1::index(Test1::V3) == 2);
static_assert(Range1::is_valid(Test1::V2));
static_assert(Range1::is_valid(enum_cast<Test1>(0)));
static_assert(!Range1::is_valid(enum_cast<Test1>(3)));

enum class Test2 {
    V1 = -5,
    V2,
    V3,
};

static_assert(underlying_value(Test2::V1) == -5);
static_assert(underlying_value(Test2::V2) == -4);
static_assert(underlying_value(Test2::V3) == -3);

using Range2 = IndexRange<Test2, Test2::V1, Test2::V3>;
static_assert(Range2::index(Test2::V1) == 0);
static_assert(Range2::index(Test2::V2) == 1);
static_assert(Range2::index(Test2::V3) == 2);
static_assert(Range2::is_valid(enum_cast<Test2>(-5)));
static_assert(!Range2::is_valid(enum_cast<Test2>(0)));

enum class Test3 {
    V1 = -1,
    V2,
    V3,
};

static_assert(underlying_value(Test3::V1) == -1);
static_assert(underlying_value(Test3::V2) == 0);
static_assert(underlying_value(Test3::V3) == 1);

using Range3 = IndexRange<Test3, Test3::V1, Test3::V3>;
static_assert(Range3::index(Test3::V1) == 0);
static_assert(Range3::index(Test3::V2) == 1);
static_assert(Range3::index(Test3::V3) == 2);

enum class Test4 : uint8_t {
    V1, V2, V3, V4, V5
};

using Range4 = IndexRange<Test4, Test4::V2, Test4::V4>;
static_assert(Range4::index(Test4::V2) == 0);
static_assert(Range4::index(Test4::V3) == 1);
static_assert(Range4::index(Test4::V4) == 2);
static_assert(!Range4::is_valid(Test4::V1));
static_assert(!Range4::is_valid(Test4::V5));
static_assert(!Range4::is_valid(enum_cast<Test4>(0)));


} //namespace

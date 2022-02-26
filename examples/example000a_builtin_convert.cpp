///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local
{
  template<typename NumericType>
  WIDE_INTEGER_CONSTEXPR auto fabs(NumericType a) -> NumericType
  {
    return ((a < NumericType(0)) ? -a : a);
  }
} // namespace local

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example000a_builtin_convert() -> bool
#else
auto math::wide_integer::example000a_builtin_convert() -> bool
#endif
{
  bool result_is_ok = true;

  using math::wide_integer::int256_t;

  {
    WIDE_INTEGER_CONSTEXPR int256_t n = -1234567.89; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    WIDE_INTEGER_CONSTEXPR bool result_n_is_ok = (n == -1234567); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_n_is_ok, "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_n_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR int256_t n = "-12345678900000000000000000000000";

    WIDE_INTEGER_CONSTEXPR auto f = static_cast<float>(n);

    using local::fabs;

    WIDE_INTEGER_CONSTEXPR float closeness     = fabs(1.0F - fabs(f / -1.23456789E31F)); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    WIDE_INTEGER_CONSTEXPR bool result_f_is_ok = (closeness < std::numeric_limits<float>::epsilon());

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_f_is_ok, "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_f_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR int256_t     n   = "-123456789000000000";

    WIDE_INTEGER_CONSTEXPR auto n64 = static_cast<std::int64_t>(n);

    WIDE_INTEGER_CONSTEXPR bool result_n_is_ok = (n64 == INT64_C(-123456789000000000));

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert((n64 == INT64_C(-123456789000000000)), "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_n_is_ok;
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE000A_BUILTIN_CONVERT)

#include <iomanip>
#include <iostream>

int main()
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const bool result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example000a_builtin_convert();
  #else
  const bool result_is_ok = math::wide_integer::example000a_builtin_convert();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

#endif

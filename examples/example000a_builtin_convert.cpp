///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local
{
  template<typename NumericType>
  WIDE_INTEGER_CONSTEXPR NumericType fabs(NumericType a)
  {
    return ((a < NumericType(0)) ? -a : a);
  }
}

bool math::wide_integer::example000a_builtin_convert()
{
  bool result_is_ok = true;

  using int256_t = math::wide_integer::int256_t;

  {
    WIDE_INTEGER_CONSTEXPR int256_t n = -1234567.89;

    WIDE_INTEGER_CONSTEXPR bool result_n_is_ok = (n == -1234567);

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_n_is_ok == true, "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_n_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR int256_t n = "-12345678900000000000000000000000";

    WIDE_INTEGER_CONSTEXPR float    f = (float) n;

    using local::fabs;

    WIDE_INTEGER_CONSTEXPR float closeness     = fabs(1.0F - fabs(f / -1.23456789E31F));
    WIDE_INTEGER_CONSTEXPR bool result_f_is_ok = (closeness < std::numeric_limits<float>::epsilon());

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_f_is_ok == true, "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_f_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR int256_t     n   = "-123456789000000000";

    WIDE_INTEGER_CONSTEXPR std::int64_t n64 = (std::int64_t) n;

    WIDE_INTEGER_CONSTEXPR bool result_n_is_ok = (n64 == INT64_C(-123456789000000000));

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert((n64 == INT64_C(-123456789000000000)), "Error: example000a_builtin_convert not OK!");
    #endif

    result_is_ok &= result_n_is_ok;
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example000a_builtin_convert();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

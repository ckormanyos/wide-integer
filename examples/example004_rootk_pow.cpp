///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

bool math::wide_integer::example004_rootk_pow()
{
  bool result_is_ok = true;

  {
    using uint256_t = math::wide_integer::uint256_t;

    WIDE_INTEGER_CONSTEXPR uint256_t x("0x95E0E51079E1D11737D3FD01429AA745582FEB4381D61FA56948C1A949E43C32");
    WIDE_INTEGER_CONSTEXPR uint256_t r = rootk(x, 7U);

    WIDE_INTEGER_CONSTEXPR bool result_is_ok_root = (r == UINT64_C(0x16067D1894));

    result_is_ok &= result_is_ok_root;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_is_ok_root == true, "Error: example004_rootk_pow not OK!");
    #endif
  }

  {
    using uint256_t = math::wide_integer::uint256_t;

    WIDE_INTEGER_CONSTEXPR uint256_t r(UINT64_C(0x16067D1894));
    WIDE_INTEGER_CONSTEXPR uint256_t p = pow(r, 7U);

    WIDE_INTEGER_CONSTEXPR bool result_is_ok_pow = (p == "0x95E0E5104B2F636571834936C982E40EFA25682E7370CD1C248051E1CDC34000");

    result_is_ok &= result_is_ok_pow;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_is_ok_pow == true, "Error: example004_rootk_pow not OK!");
    #endif
  }

  {
    using int256_t = math::wide_integer::int256_t;

    WIDE_INTEGER_CONSTEXPR int256_t x("-17791969125525294590007745776736486317864490689865550963808715359713140948018");
    WIDE_INTEGER_CONSTEXPR int256_t r = cbrt(x);

    WIDE_INTEGER_CONSTEXPR bool result_is_ok_root = (r == int256_t("-26106060416733621800766427"));

    result_is_ok &= result_is_ok_root;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_is_ok_root == true, "Error: example004_rootk_pow not OK!");
    #endif
  }

  {
    using int256_t = math::wide_integer::int256_t;

    WIDE_INTEGER_CONSTEXPR int256_t x("-17791969125525294590007745776736486317864490689865550963808715359713140948018");
    WIDE_INTEGER_CONSTEXPR int256_t r = rootk(x, 3);

    WIDE_INTEGER_CONSTEXPR bool result_is_ok_root = (r == int256_t("-26106060416733621800766427"));

    result_is_ok &= result_is_ok_root;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_is_ok_root == true, "Error: example004_rootk_pow not OK!");
    #endif
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example004_rootk_pow();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example001_mul_div() -> bool
#else
auto math::wide_integer::example001_mul_div() -> bool
#endif
{
  using math::wide_integer::uint256_t;

  WIDE_INTEGER_CONSTEXPR uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  WIDE_INTEGER_CONSTEXPR uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

  WIDE_INTEGER_CONSTEXPR uint256_t c = (a * b);
  WIDE_INTEGER_CONSTEXPR uint256_t d = (a / b);

  WIDE_INTEGER_CONSTEXPR bool result_is_ok = (   (c == "0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076")
                                              && (std::uint_fast8_t(d) == 10U));

  #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
  static_assert(result_is_ok, "Error: example001_mul_div not OK!");
  #endif

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const bool result_is_ok = WIDE_INTEGER_NAMESPACE::wide_integer::example001_mul_div();
  #else
  const bool result_is_ok = wide_integer::example001_mul_div();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

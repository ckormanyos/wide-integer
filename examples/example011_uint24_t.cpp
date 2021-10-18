///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

bool math::wide_integer::example011_uint24_t()
{
  using uint24_t = math::wide_integer::uintwide_t<24U, std::uint8_t>;

  using distribution_type  = math::wide_integer::uniform_int_distribution<24U, typename uint24_t::limb_type>;
  using random_engine_type = std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

  random_engine_type generator(UINT32_C(0xDEADBEEF));

  distribution_type distribution;

  const std::uint32_t a32 = static_cast<std::uint32_t>(distribution(generator));
  const std::uint32_t b32 = static_cast<std::uint32_t>(distribution(generator));

  const uint24_t a(a32);
  const uint24_t b(b32);

  const uint24_t c_add = (a + b);
  const uint24_t c_sub = (a - b);
  const uint24_t c_mul = (a * b);
  const uint24_t c_div = (a / b);

  const bool result_is_ok = (   (   (c_add == ((a32 + b32) & 0x00FFFFFFULL))
                                 && (c_sub == ((a32 - b32) & 0x00FFFFFFULL))
                                 && (c_mul == ((a32 * b32) & 0x00FFFFFFULL))
                                 && (c_div == ((a32 / b32) & 0x00FFFFFFULL)))
                             &&
                                (   ((std::uint64_t) c_add == ((a32 + b32) & 0x00FFFFFFULL))
                                 && ((std::uint64_t) c_sub == ((a32 - b32) & 0x00FFFFFFULL))
                                 && ((std::uint64_t) c_mul == ((a32 * b32) & 0x00FFFFFFULL))
                                 && ((std::uint64_t) c_div == ((a32 / b32) & 0x00FFFFFFULL))));

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example011_uint24_t();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

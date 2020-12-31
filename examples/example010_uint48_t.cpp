///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>

#include <wide_integer/generic_template_uintwide_t.h>

bool wide_integer::example010_uint48_t()
{
  using uint48_t = wide_integer::generic_template::uintwide_t<48U, std::uint8_t>;

  using distribution_type  = wide_integer::generic_template::uniform_int_distribution<48U, typename uint48_t::limb_type>;
  using random_engine_type = std::minstd_rand;

  random_engine_type generator(0xF00DCAFEULL);

  distribution_type distribution;

  const std::uint64_t a64 = static_cast<std::uint64_t>(distribution(generator));
  const std::uint64_t b64 = static_cast<std::uint64_t>(distribution(generator));

  const uint48_t a(a64);
  const uint48_t b(b64);

  const uint48_t c_add = (a + b);
  const uint48_t c_sub = (a - b);
  const uint48_t c_mul = (a * b);
  const uint48_t c_div = (a / b);

  const bool result_is_ok = (   (   (c_add == ((a64 + b64) & 0x0000FFFFFFFFFFFFULL))
                                 && (c_sub == ((a64 - b64) & 0x0000FFFFFFFFFFFFULL))
                                 && (c_mul == ((a64 * b64) & 0x0000FFFFFFFFFFFFULL))
                                 && (c_div == ((a64 / b64) & 0x0000FFFFFFFFFFFFULL)))
                             &&
                                (   ((std::uint64_t) c_add == ((a64 + b64) & 0x0000FFFFFFFFFFFFULL))
                                 && ((std::uint64_t) c_sub == ((a64 - b64) & 0x0000FFFFFFFFFFFFULL))
                                 && ((std::uint64_t) c_mul == ((a64 * b64) & 0x0000FFFFFFFFFFFFULL))
                                 && ((std::uint64_t) c_div == ((a64 / b64) & 0x0000FFFFFFFFFFFFULL))));

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example010_uint48_t();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

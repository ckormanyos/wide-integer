///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>
#include <string>

#include <wide_integer/generic_template_uintwide_t.h>

namespace
{
  template<typename LimbType>
  bool generate()
  {
    using random_engine_type = std::mt19937;

    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint32_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::limb_type>;

    // Generate a random number with wide_integer_type having limbs of type LimbType.
    random_engine_type generator(123U);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    const bool result_is_ok =
      (n == wide_integer_type("0xB81A3C118D22F6E6B0DDD4623A12EFDC6DB0454249406D7EB6843D6DB24BCDFE"));

    return result_is_ok;
  }
}

bool wide_integer::example007_random_generator()
{
  const bool result_08_is_ok = generate<std::uint8_t> ();
  const bool result_16_is_ok = generate<std::uint16_t>();
  const bool result_32_is_ok = generate<std::uint32_t>();

  const bool result_is_ok = (   result_08_is_ok
                             && result_16_is_ok
                             && result_32_is_ok);

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example007_random_generator();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

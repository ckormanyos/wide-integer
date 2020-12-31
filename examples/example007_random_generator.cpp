///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>
#include <string>

#include <wide_integer/generic_template_uintwide_t.h>

// TBD: Compare with an actual expected value.
// This test obtains different numerical results on CI server.
// Suspect a possible byte order erroneous dependency in
// uintwide_t random distribution generator code.
// TBD: For the moment, test that the generated randoms
// are != 0.

bool wide_integer::example007_random_generator()
{
  using random_engine_type = std::mt19937;

  bool result_is_ok = true;

  {
    // Generate a random number with wide_integer_type having 32-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint32_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::limb_type>;

    random_engine_type generator(123U);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n != 0U);
  }

  {
    // Generate a random number with wide_integer_type having 16-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint16_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::limb_type>;

    random_engine_type generator(123U);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n != 0U);
  }

  {
    // Generate a random number with wide_integer_type having 8-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint8_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::limb_type>;

    random_engine_type generator(123U);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n != 0U);
  }

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

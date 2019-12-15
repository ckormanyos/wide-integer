///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 -2019.                  //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>

#include <wide_integer/generic_template_uintwide_t.h>

bool wide_integer::example007_random_generator()
{
  bool result_is_ok = true;

  {
    // Generate a random number with wide_integer_type having 32-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint32_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
    using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

    random_engine_type::value_type seed(1332597477ULL);

    random_engine_type generator(seed);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "103688572923999614683274548975545468793316802532402235278881055800362044212101");
  }

  {
    // Generate a random number with wide_integer_type having 16-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint16_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
    using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

    random_engine_type::value_type seed(1332597477ULL);

    random_engine_type generator(seed);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "103688572923999614683274548975545468793316802532402235278881055800362044212101");
  }

  {
    // Generate a random number with wide_integer_type having 8-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint8_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
    using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

    random_engine_type::value_type seed(1332597477ULL);

    random_engine_type generator(seed);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "103688572923999614683274548975545468793316802532402235278881055800362044212101");
  }

  return result_is_ok;
}

#if !defined(WIDE_INTEGER_DISABLE_MAIN_IN_STANDALONE_EXAMPLES)

int main()
{
  const bool result_is_ok = wide_integer::example007_random_generator();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

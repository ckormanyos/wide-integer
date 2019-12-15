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

    random_engine_type generator(1332597477ULL);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "42243275513152172878699293211523558801283070860992524724214371136543908833813");
  }

  {
    // Generate a random number with wide_integer_type having 16-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint16_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
    using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

    random_engine_type generator(1332597477ULL);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "42243275513152172878699293211523558801283070860992524724214371136543908833813");
  }

  {
    // Generate a random number with wide_integer_type having 8-bit limbs.
    using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U, std::uint8_t>;
    using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
    using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

    random_engine_type generator(1332597477ULL);

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    result_is_ok &= (n == "42243275513152172878699293211523558801283070860992524724214371136543908833813");
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

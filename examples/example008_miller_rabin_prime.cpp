///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 -2019.                  //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This Miller-Rabin primality test is loosely based on
// an adaptation of some code from Boost.Multiprecision.
// The Boost.Multiprecision code can be found here:
// https://www.boost.org/doc/libs/1_68_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

#include <wide_integer/generic_template_uintwide_t.h>

bool wide_integer::example008_miller_rabin_prime()
{
  using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U>;
  using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
  using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

  // Use a fixed seed in order to obtain deterministic
  // and reproducible result for this test.

  random_engine_type generator1(305419969ULL);
  random_engine_type generator2;

  distribution_type distribution1;
  distribution_type distribution2;

  bool result_is_ok = false;

  for(std::uint_fast32_t index = 0U; index < UINT32_C(10000); ++index)
  {
    const wide_integer_type n = distribution1(generator1);

    bool miller_rabin_result = miller_rabin(n,
                                            25U,
                                            distribution2,
                                            generator2);

    if(miller_rabin_result)
    {
      // We will now find out if [(n - 1) / 2] is also prime.
      miller_rabin_result = miller_rabin((n - 1U) >> 1U,
                                         25U,
                                         distribution2,
                                         generator2);

      result_is_ok =
        (   (miller_rabin_result == true)
         && (n == "44314879133400045088401570410731290767415555827427735336410270823316569902579")
         && (index == 694U));

      if(result_is_ok)
      {
        break;
      }
    }
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example008_miller_rabin_prime();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

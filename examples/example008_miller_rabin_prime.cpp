///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iomanip>
#include <iostream>

#include <wide_integer/generic_template_uintwide_t.h>

int main()
{
  using wide_integer_type  = wide_integer::generic_template::uintwide_t<256U>;
  using distribution_type  = wide_integer::generic_template::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::value_type>;
  using random_engine_type = wide_integer::generic_template::default_random_engine   <wide_integer_type::my_digits, typename wide_integer_type::value_type>;

  // Use fixed seeds in order to obtain deterministic
  // and reproducible results for this test.
  constexpr typename random_engine_type::value_type seed1(1332597477ULL);

  random_engine_type generator1(seed1);
  random_engine_type generator2;

  distribution_type distribution1;
  distribution_type distribution2;

  bool result_is_ok = false;

  for(std::uint_fast32_t index = 0U; index < UINT32_C(100000); ++index)
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
         && (n == "3401859042787836548530328760785776956582810521344014846856283581144486333919")
         && (index == 458U));

      if(result_is_ok)
      {
        break;
      }
    }
  }

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This Miller-Rabin primality test is loosely based on
// an adaptation of some code from Boost.Multiprecision.
// The Boost.Multiprecision code can be found here:
// https://www.boost.org/doc/libs/1_76_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

#include <ctime>
#include <random>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#endif

#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/uintwide_t_backend.hpp>

#include <examples/example_uintwide_t.h>

bool math::wide_integer::example008a_miller_rabin_prime()
{
  using wide_integer_type = boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<512U>,
                                                          boost::multiprecision::et_off>;

  boost::random::mt11213b base_gen(static_cast<typename boost::random::mt11213b::result_type>(std::clock()));

  boost::random::independent_bits_engine<boost::random::mt11213b,
                                         std::numeric_limits<wide_integer_type>::digits,
                                         wide_integer_type>
  gen(base_gen);

  using random_engine2_type =
    std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

  random_engine2_type gen2(static_cast<typename random_engine2_type::result_type>(std::clock()));

  wide_integer_type p0;
  wide_integer_type p1;

  for(;;)
  {
    p0 = gen();

    const bool miller_rabin_result = boost::multiprecision::miller_rabin_test(p0, 25U, gen2);

    if(miller_rabin_result)
    {
      break;
    }
  }

  for(;;)
  {
    p1 = gen();

    const bool miller_rabin_result = boost::multiprecision::miller_rabin_test(p1, 25U, gen2);

    if(miller_rabin_result)
    {
      break;
    }
  }

  const wide_integer_type gd = gcd(p0, p1);

  const bool result_is_ok = (   (p0 != 0U)
                             && (p1 != 0U)
                             && (p0 != p1)
                             && (gd == 1U));

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example008a_miller_rabin_prime();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic pop
#endif

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif

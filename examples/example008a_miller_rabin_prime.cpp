///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This Miller-Rabin primality test is loosely based on
// an adaptation of some code from Boost.Multiprecision.
// The Boost.Multiprecision code can be found here:
// https://www.boost.org/doc/libs/1_78_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

#include <ctime>
#include <random>
#include <sstream>
#include <string>

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

namespace local_miller_rabin
{
  template<typename UnsignedIntegralType>
  auto lexical_cast(const UnsignedIntegralType& u) -> std::string
  {
    std::stringstream ss;

    ss << u;

    return ss.str();
  }
}

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example008a_miller_rabin_prime() -> bool
#else
auto math::wide_integer::example008a_miller_rabin_prime() -> bool
#endif
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  using boost_wide_integer_type =
    boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(UINT32_C(512))>,
                                  boost::multiprecision::et_off>;
  #else
  using boost_wide_integer_type =
    boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<static_cast<math::wide_integer::size_t>(UINT32_C(512))>,
                                  boost::multiprecision::et_off>;
  #endif

  using local_wide_integer_type = math::wide_integer::uintwide_t              <static_cast<math::wide_integer::size_t>(std::numeric_limits<boost_wide_integer_type>::digits), std::uint32_t>;
  using local_distribution_type = math::wide_integer::uniform_int_distribution<static_cast<math::wide_integer::size_t>(std::numeric_limits<boost_wide_integer_type>::digits), typename local_wide_integer_type::limb_type>;

  using random_engine1_type = std::mt19937;

  using random_engine2_type =
    std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

  random_engine2_type gen2(static_cast<typename random_engine2_type::result_type>(std::clock()));

  boost_wide_integer_type p0;
  boost_wide_integer_type p1;

  random_engine2_type generator(static_cast<std::mt19937::result_type>(std::clock()));

  local_distribution_type
    distribution
    {
      // Select prime candidates from a range of 10^150 ... uint512_t-max.
      local_wide_integer_type
      (
        std::string(std::string("1") + std::string(150U, static_cast<char>('0'))).c_str() // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ),
      (std::numeric_limits<local_wide_integer_type>::max)()
    };

  for(;;)
  {
    {
      const local_wide_integer_type n0 = distribution(generator);

      p0 = boost_wide_integer_type(local_miller_rabin::lexical_cast(n0));
    }

    const bool miller_rabin_result = boost::multiprecision::miller_rabin_test(p0, 25U, gen2);

    if(miller_rabin_result)
    {
      break;
    }
  }

  for(;;)
  {
    {
      const local_wide_integer_type n1 = distribution(generator);

      p1 = boost_wide_integer_type(local_miller_rabin::lexical_cast(n1));
    }

    const bool miller_rabin_result = boost::multiprecision::miller_rabin_test(p1, 25U, gen2);

    if(miller_rabin_result)
    {
      break;
    }
  }

  const boost_wide_integer_type gd = gcd(p0, p1);

  const bool result_is_ok = (   (p0 != 0U)
                             && (p1 != 0U)
                             && (p0 != p1)
                             && (gd == 1U));

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE008A_MILLER_RABIN_PRIME)

#include <iomanip>
#include <iostream>

int main()
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const bool result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example008a_miller_rabin_prime();
  #else
  const bool result_is_ok = math::wide_integer::example008a_miller_rabin_prime();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
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

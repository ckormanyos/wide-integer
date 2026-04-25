///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This Miller-Rabin primality test is loosely based on
// an adaptation of some code from Boost.Multiprecision.
// The Boost.Multiprecision code can be found here:
// https://www.boost.org/doc/libs/1_90_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>
#include <util/utility/util_pseudorandom_time_point_seed.h>

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

namespace local_solovay_strassen {

// Forward declarations

template<typename BigInteger>
int jacobi(BigInteger a, BigInteger n);

template<typename UnsignedIntegerType,
         typename DistributionType,
         typename GeneratorType>
bool solovay_strassen(const UnsignedIntegerType& n, const int iterations, DistributionType& distribution, GeneratorType& generator)
{
  // --- Solovay-Strassen Test ---
  if (n < 2) { return false; }
  if (n == 2) { return true; }
  if ((n % 2) == 0) { return false; }

  using local_distribution_type = DistributionType;

  using local_wide_integer_type = UnsignedIntegerType;

  using local_param_type = typename DistributionType::param_type;

  const local_param_type
    params
    {
      local_wide_integer_type { unsigned { UINT8_C(2) } },
      local_wide_integer_type { n - unsigned { UINT8_C(1) } }
    };

  local_distribution_type dist { local_wide_integer_type { 2 }, { local_wide_integer_type { n - 1 } } };

  for(int i = 0; i < iterations; ++i)
  {
    local_wide_integer_type a { distribution(generator) };

    local_wide_integer_type g = gcd(a, n);

    if(g > 1)
    {
      return false;
    }

    const int jac = jacobi(a, n);

    if(jac == 0)
    {
      return false;
    }

    local_wide_integer_type exponent { (n - 1) / 2 };
    local_wide_integer_type mod_exp { powm(a, exponent, n) };

    local_wide_integer_type jacobian { (jac == -1) ? n - 1 : jac };

    if(mod_exp != (jacobian % n))
    {
      return false;
    }
  }

  // The candidate is probably prime.
  return true;
}

// --- Jacobi Symbol ---
template<typename BigInteger>
int jacobi(BigInteger a, BigInteger n)
{
  if (n <= 0 || n % 2 == 0)
  {
    return 0;
  }

  a = a % n;

  int result = 1;

  while (a != 0)
  {
    while (a % 2 == 0)
    {
      a /= 2;

      BigInteger r = n % 8;

      if (r == 3 || r == 5)
      {
        result = -result;
      }
    }

    std::swap(a, n);

    if (a % 4 == 3 && n % 4 == 3)
    {
      result = -result;
    }

    a = a % n;
  }

  return (n == 1) ? result : 0;
}

} // namespace local_solovay_strassen

namespace local_example008b_solovay_strassen_prime
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  using wide_integer_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(UINT32_C(512))>;
  using distribution_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uniform_int_distribution<wide_integer_type::my_width2, typename wide_integer_type::limb_type>;
  #else
  using wide_integer_type = ::math::wide_integer::uintwide_t<static_cast<math::wide_integer::size_t>(UINT32_C(512))>;
  using distribution_type = ::math::wide_integer::uniform_int_distribution<wide_integer_type::my_width2, typename wide_integer_type::limb_type>;
  #endif

  using random_engine1_type = std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;
  using random_engine2_type = std::mt19937;

  auto example008b_solovay_strassen_prime_run() -> bool;

  auto example008b_solovay_strassen_prime_run() -> bool
  {
    // Use a pseudo-random seed for this test.

    random_engine1_type generator1(util::util_pseudorandom_time_point_seed::value<typename random_engine1_type::result_type>());
    random_engine2_type generator2(util::util_pseudorandom_time_point_seed::value<typename random_engine2_type::result_type>());

    distribution_type distribution1;
    distribution_type distribution2;

    wide_integer_type p0;

    bool result_is_ok { false };

    constexpr int max_trials { 2048 };

    int trials { 0 };

    for( ; trials < 2048; ++trials)
    {
      p0 = distribution1(generator1);

      const bool solovay_strassen_result =
        local_solovay_strassen::solovay_strassen
        (
          p0,
          32U,
          distribution2,
          generator2
        );

      const bool miller_rabin_ctrl =
        miller_rabin
        (
          p0,
          32U,
          distribution2,
          generator2
        );

      result_is_ok = (solovay_strassen_result == miller_rabin_ctrl);

      if(solovay_strassen_result)
      {
        break;
      }
    }

    result_is_ok = ((trials < max_trials) && result_is_ok);

    return result_is_ok;
  }
} // namespace local_example008b_solovay_strassen_prime

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example008b_solovay_strassen_prime() -> bool
#else
auto ::math::wide_integer::example008b_solovay_strassen_prime() -> bool
#endif
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  using wide_integer_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(UINT32_C(512))>;
  using distribution_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uniform_int_distribution<wide_integer_type::my_width2, typename wide_integer_type::limb_type>;
  #else
  using wide_integer_type = ::math::wide_integer::uintwide_t<static_cast<math::wide_integer::size_t>(UINT32_C(512))>;
  using distribution_type = ::math::wide_integer::uniform_int_distribution<wide_integer_type::my_width2, typename wide_integer_type::limb_type>;
  #endif

  using random_engine1_type = std::mt19937;
  using random_engine2_type = std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

  const auto seed_start = ::util::util_pseudorandom_time_point_seed::value<std::uint64_t>();

  random_engine1_type gen1(static_cast<typename random_engine1_type::result_type>(seed_start));
  random_engine2_type gen2(static_cast<typename random_engine2_type::result_type>(seed_start));

  // Select prime candidates from a range of 10^150 ... max(uint512_t)-1.
  constexpr wide_integer_type
    dist_min
    (
      "1"
      "00000000000000000000000000000000000000000000000000"
      "00000000000000000000000000000000000000000000000000"
      "00000000000000000000000000000000000000000000000000"
    );

  constexpr auto dist_max =
    wide_integer_type
    {
        (std::numeric_limits<wide_integer_type>::max)()
      - static_cast<int>(INT8_C(1))
    };

  distribution_type
    dist
    {
      dist_min,
      dist_max
    };

  auto result_is_ok = true;

  for(auto   i = static_cast<unsigned>(UINT8_C(0));
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
             i < static_cast<unsigned>(UINT8_C(16));
  #else
             i < static_cast<unsigned>(UINT8_C(4));
  #endif
           ++i)
  {
    const auto result_prime_run_is_ok =
      local_example008b_solovay_strassen_prime::example008b_solovay_strassen_prime_run();

    result_is_ok = (result_prime_run_is_ok && result_is_ok);
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE008B_SOLOVAY_STRASSEN_PRIME)

#include <iomanip>
#include <iostream>

auto main() -> int // NOLINT(bugprone-exception-escape)
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const auto result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example008b_solovay_strassen_prime();
  #else
  const auto result_is_ok = ::math::wide_integer::example008b_solovay_strassen_prime();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

#endif

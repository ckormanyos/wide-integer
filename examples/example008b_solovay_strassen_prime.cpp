///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>
#include <util/utility/util_pseudorandom_time_point_seed.h>

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

namespace local_solovay_strassen {

namespace detail {

template<typename UnsignedIntegerType>
auto jacobi(UnsignedIntegerType a, UnsignedIntegerType n) -> int;

template<typename UnsignedIntegerType>
auto jacobi(UnsignedIntegerType a, UnsignedIntegerType n) -> int
{
  // Calculate the integer's Jacobi symbol.
  if(    (static_cast<unsigned>(n) == 0U)
     || ((static_cast<unsigned>(n) % 2U) == 0U))
  {
    return 0;
  }

  a %= n;

  int result = 1;

  while(a != 0)
  {
    while((static_cast<unsigned>(a) % 2U) == 0U)
    {
      a /= 2U;

      UnsignedIntegerType r { n % 8U }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

      if(   ((static_cast<unsigned>(r) == 3U) && (r == 3U))  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
         || ((static_cast<unsigned>(r) == 5U) && (r == 5U))) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      {
        result = -result;
      }
    }

    std::swap(a, n);

    const unsigned a_mod_4 { static_cast<unsigned>(a % 4U) }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    const unsigned n_mod_4 { static_cast<unsigned>(n % 4U) }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    if((a_mod_4 == 3U) && (n_mod_4 == 3U)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    {
      result = -result;
    }

    a %= n;
  }

  return ((n == 1) ? result : 0);
}

} // namespace detail

template<typename UnsignedIntegerType,
         typename DistributionType,
         typename GeneratorType>
auto solovay_strassen(const UnsignedIntegerType& n, const int iterations, DistributionType& distribution, GeneratorType& generator) -> bool;

template<typename UnsignedIntegerType,
         typename DistributionType,
         typename GeneratorType>
auto solovay_strassen(const UnsignedIntegerType& n, const int iterations, DistributionType& distribution, GeneratorType& generator) -> bool
{
  // Perform a Solovay-Strassen primality test.

  // If this ever goes to production, then testing a lot more semi-small
  // primes, as done in the library's Miller-Rabin, would make sense here.

  if((static_cast<unsigned>(n)  < 2U) && (n < 2)) { return false; }
  if((static_cast<unsigned>(n) == 2U) && (n == 2)) { return true; }
  if((static_cast<unsigned>(n)  % 2U) == 0U) { return false; }

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

    const int jac = detail::jacobi(a, n);

    if(jac == 0)
    {
      return false;
    }

    local_wide_integer_type exponent { (n - 1) / 2 };
    local_wide_integer_type mod_exp { powm(a, exponent, n) };

    local_wide_integer_type jacobian { (jac == -1) ? (n - 1) : jac };

    if(mod_exp != (jacobian % n))
    {
      return false;
    }
  }

  // The candidate is probably prime.
  return true;
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

  using random_engine1_type = std::mt19937;
  using random_engine2_type = std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

  const auto seed_start = ::util::util_pseudorandom_time_point_seed::value<std::uint64_t>(); // NOLINT(cert-err58-cpp)

  random_engine1_type gen1(static_cast<typename random_engine1_type::result_type>(seed_start)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
  random_engine2_type gen2(static_cast<typename random_engine2_type::result_type>(seed_start)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

  auto example008b_solovay_strassen_prime_run() -> bool;

  auto example008b_solovay_strassen_prime_run() -> bool
  {
    // Use a pseudo-random seed for this test.

    random_engine1_type generator1(util::util_pseudorandom_time_point_seed::value<typename random_engine1_type::result_type>());
    random_engine2_type generator2(util::util_pseudorandom_time_point_seed::value<typename random_engine2_type::result_type>());

    // Select prime candidates from a range of 10^150 ... max(uint512_t)-1.
    constexpr wide_integer_type
      dist_min
      (
        "1"
        "00000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000"
      );

    distribution_type
      distribution1
      {
        dist_min,
        (std::numeric_limits<wide_integer_type>::max)()
      };

    distribution_type distribution2;

    bool result_is_ok { false };

    constexpr int max_trials { 2048 }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    int trials { 0 };

    for( ; trials < max_trials; ++trials)
    {
      // Perform a Solovay-Strassen versus Miller-Rabin primality comparison.
      // Each one should detect prime/non-prime with the same Boolean result
      // for a given prime candidate p0.

      const wide_integer_type p0 { distribution1(generator1) };

      const bool result_solovay_strassen_is_prime =
        local_solovay_strassen::solovay_strassen
        (
          p0,
          32,
          distribution2,
          generator2
        );

      const bool result_miller_rabin_ctrl_is_prime =
        miller_rabin
        (
          p0,
          25,
          distribution2,
          generator2
        );

      result_is_ok = (result_solovay_strassen_is_prime == result_miller_rabin_ctrl_is_prime);

      if(result_solovay_strassen_is_prime)
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
  bool result_is_ok { true };

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

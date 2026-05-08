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
#include <utility>

#if defined(__clang__)
  #if defined __has_feature && __has_feature(thread_sanitizer)
  #define UINTWIDE_T_REDUCE_TEST_DEPTH
  #endif
#elif defined(__GNUC__)
  #if defined(__SANITIZE_THREAD__) || defined(WIDE_INTEGER_HAS_COVERAGE)
  #define UINTWIDE_T_REDUCE_TEST_DEPTH
  #endif
#elif defined(_MSC_VER)
  #if defined(_DEBUG)
  #define UINTWIDE_T_REDUCE_TEST_DEPTH
  #endif
#endif

namespace local_solovay_strassen {

namespace detail {

template<typename UnsignedIntegerType>
auto jacobi(UnsignedIntegerType a, UnsignedIntegerType n) -> int;

template<typename UnsignedIntegerType>
auto jacobi(UnsignedIntegerType a, UnsignedIntegerType n) -> int
{
  // Calculate the integer's Jacobi symbol.

  // LCOV_EXCL_START
  if(   ((static_cast<std::uint_fast8_t>(n) == 0U) && (n== 0U))
     || ((static_cast<std::uint_fast8_t>(n) % 2U) == 0U))
  {
    return 0;
  }
  // LCOV_EXCL_STOP

  a %= n;

  int result = 1;

  while(a != 0)
  {
    while((static_cast<std::uint_fast8_t>(a) % 2U) == 0U)
    {
      a /= 2U;

      UnsignedIntegerType r { n % 8U }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

      if(   ((static_cast<std::uint_fast8_t>(r) == 3U) && (r == 3U))  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
         || ((static_cast<std::uint_fast8_t>(r) == 5U) && (r == 5U))) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      {
        result = -result;
      }
    }

    std::swap(a, n);

    const unsigned a_mod_4 { static_cast<std::uint_fast8_t>(a % 4U) }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    const unsigned n_mod_4 { static_cast<std::uint_fast8_t>(n % 4U) }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    if((a_mod_4 == 3U) && (n_mod_4 == 3U)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    {
      result = -result;
    }

    a %= n;
  }

  const bool n_is_one { ((static_cast<std::uint_fast8_t>(n) == 1U) && (n == 1U)) };

  return (n_is_one ? result : 0);
}

} // namespace detail

template<typename UnsignedIntegerType,
         typename DistributionType,
         typename GeneratorType>
auto solovay_strassen(const UnsignedIntegerType& np, const int iterations, DistributionType& distribution, GeneratorType& generator) -> bool; // NOLINT(readability-avoid-const-params-in-decls)

template<typename UnsignedIntegerType,
         typename DistributionType,
         typename GeneratorType>
auto solovay_strassen(const UnsignedIntegerType& np, const int iterations, DistributionType& distribution, GeneratorType& generator) -> bool // NOLINT(readability-avoid-const-params-in-decls,readability-function-cognitive-complexity)
{
  // Perform a Solovay-Strassen primality test.

  using local_wide_integer_type = UnsignedIntegerType;
  using local_limb_type         = typename local_wide_integer_type::limb_type;

  // Table[Prime[i], {i, 2, 49, 1}] =
  // {
  //     3,   5,   7,  11,  13,  17,  19,  23,
  //    29,  31,  37,  41,  43,  47,  53,  59,
  //    61,  67,  71,  73,  79,  83,  89,  97,
  //   101, 103, 107, 109, 113, 127, 131, 137,
  //   139, 149, 151, 157, 163, 167, 173, 179,
  //   181, 191, 193, 197, 199, 211, 223, 227
  // }
  // See also:
  // https://www.wolframalpha.com/input/?i=Table%5BPrime%5Bi%5D%2C+%7Bi%2C+2%2C+49%7D%5D

  const std::array<local_limb_type, static_cast<std::size_t>(UINT8_C(48))> small_primes =
  {
    static_cast<local_limb_type>(UINT8_C(  3)), static_cast<local_limb_type>(UINT8_C(  5)), static_cast<local_limb_type>(UINT8_C(  7)), static_cast<local_limb_type>(UINT8_C( 11)), static_cast<local_limb_type>(UINT8_C( 13)), static_cast<local_limb_type>(UINT8_C( 17)), static_cast<local_limb_type>(UINT8_C( 19)), static_cast<local_limb_type>(UINT8_C( 23)),
    static_cast<local_limb_type>(UINT8_C( 29)), static_cast<local_limb_type>(UINT8_C( 31)), static_cast<local_limb_type>(UINT8_C( 37)), static_cast<local_limb_type>(UINT8_C( 41)), static_cast<local_limb_type>(UINT8_C( 43)), static_cast<local_limb_type>(UINT8_C( 47)), static_cast<local_limb_type>(UINT8_C( 53)), static_cast<local_limb_type>(UINT8_C( 59)),
    static_cast<local_limb_type>(UINT8_C( 61)), static_cast<local_limb_type>(UINT8_C( 67)), static_cast<local_limb_type>(UINT8_C( 71)), static_cast<local_limb_type>(UINT8_C( 73)), static_cast<local_limb_type>(UINT8_C( 79)), static_cast<local_limb_type>(UINT8_C( 83)), static_cast<local_limb_type>(UINT8_C( 89)), static_cast<local_limb_type>(UINT8_C( 97)),
    static_cast<local_limb_type>(UINT8_C(101)), static_cast<local_limb_type>(UINT8_C(103)), static_cast<local_limb_type>(UINT8_C(107)), static_cast<local_limb_type>(UINT8_C(109)), static_cast<local_limb_type>(UINT8_C(113)), static_cast<local_limb_type>(UINT8_C(127)), static_cast<local_limb_type>(UINT8_C(131)), static_cast<local_limb_type>(UINT8_C(137)),
    static_cast<local_limb_type>(UINT8_C(139)), static_cast<local_limb_type>(UINT8_C(149)), static_cast<local_limb_type>(UINT8_C(151)), static_cast<local_limb_type>(UINT8_C(157)), static_cast<local_limb_type>(UINT8_C(163)), static_cast<local_limb_type>(UINT8_C(167)), static_cast<local_limb_type>(UINT8_C(173)), static_cast<local_limb_type>(UINT8_C(179)),
    static_cast<local_limb_type>(UINT8_C(181)), static_cast<local_limb_type>(UINT8_C(191)), static_cast<local_limb_type>(UINT8_C(193)), static_cast<local_limb_type>(UINT8_C(197)), static_cast<local_limb_type>(UINT8_C(199)), static_cast<local_limb_type>(UINT8_C(211)), static_cast<local_limb_type>(UINT8_C(223)), static_cast<local_limb_type>(UINT8_C(227))
  };

  {
    // Handle even numbers.
    const auto n0 = static_cast<local_limb_type>(np);

    const auto n_is_even =
      (static_cast<local_limb_type>(n0 & static_cast<local_limb_type>(UINT8_C(1))) == static_cast<local_limb_type>(UINT8_C(0)));

    if(n_is_even)
    {
        // If true:
        // Handle the trivial special case of 2, which is prime.

        // If false:
        // The prime candidate is not prime because it is either
        // even and larger than 2 or equal to zero. Herewith, we
        // handle non-prime even numbers and the non-primality of 0.
        const bool
          is_prime_two_or_is_non_prime_even
          {
            ((n0 == static_cast<local_limb_type>(UINT8_C(2))) && (np == unsigned { UINT8_C(2) }))
          };

        return is_prime_two_or_is_non_prime_even;
    }

    if((n0 <= small_primes.back()) && (np <= small_primes.back()))
    {
      // This handles the trivial special case of the (non-primality) of 1.
      if(n0 == static_cast<local_limb_type>(UINT8_C(1)))
      {
        return false;
      }

      // Exclude pure small primes from the small_primes table.
      // We are already restricted to np <= small_primes.back()
      // via the query above. So it is sufficient to test only
      // the lowest limb.
      bool is_small_prime { false };

      for(const auto& small_p : small_primes)
      {
        if(static_cast<local_limb_type>(n0 == small_p))
        {
          is_small_prime = true;

          break;
        }
      }

      if(is_small_prime)
      {
        return true;
      }
    }

    // Handle numbers divisible by small primes in the small_primes table.
    bool is_small_prime_divisible { false };

    for(const auto& small_p : small_primes)
    {
      // This test does not include the secondary query if (np == small_p).
      // Thisis OK here because exact small primes have already been
      // filtered out above.

      if((np % small_p) == static_cast<local_limb_type>(UINT8_C(0)))
      {
        is_small_prime_divisible = true;

        break;
      }
    }

    if(is_small_prime_divisible)
    {
      return false;
    }
  }

  for(int i = 0; i < iterations; ++i)
  {
    local_wide_integer_type a { distribution(generator) };

    local_wide_integer_type g = gcd(a, np);

    if((static_cast<std::uint_fast8_t>(g) > 1U) && (g > 1U))
    {
      return false;
    }

    const int jac = detail::jacobi(a, np);

    if(jac == 0)
    {
      return false;
    }

    const local_wide_integer_type exponent { (np - 1) / 2 };
    const local_wide_integer_type mod_exp { powm(a, exponent, np) };

    const local_wide_integer_type jacobian { (jac == -1) ? (np - 1) : jac };

    if(mod_exp != (jacobian % np))
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

  auto example008b_solovay_strassen_prime_edges() -> bool;

  auto example008b_solovay_strassen_prime_edges() -> bool
  {
    const std::array<std::pair<wide_integer_type, bool>, std::size_t { UINT8_C(8) }> edge_cases =
    {
      std::pair<wide_integer_type, bool> { wide_integer_type { 0 }, false },
      std::pair<wide_integer_type, bool> { wide_integer_type { 1 }, false },
      std::pair<wide_integer_type, bool> { wide_integer_type { 2 }, true },
      std::pair<wide_integer_type, bool> { wide_integer_type { 3 }, true },
      std::pair<wide_integer_type, bool> { wide_integer_type { 19 }, true },
      std::pair<wide_integer_type, bool> { wide_integer_type { 223 }, true },
      std::pair<wide_integer_type, bool> { wide_integer_type { 223 } * 227, false },
      std::pair<wide_integer_type, bool> { wide_integer_type { std::uint64_t { UINT64_C(6408001374760705163) } }, false },
    };

    // Use a pseudo-random seed for this test.

    random_engine2_type generator2(util::util_pseudorandom_time_point_seed::value<typename random_engine2_type::result_type>());

    distribution_type dist2 { wide_integer_type { 2U }, (std::numeric_limits<wide_integer_type>::max)() };

    constexpr int number_of_trials { 25 }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    bool result_edge_is_ok { true };

    for(auto& edge_case : edge_cases)
    {
      const bool result_solovay_strassen_edge_is_prime =
        local_solovay_strassen::solovay_strassen
        (
          edge_case.first,
          number_of_trials,
          dist2,
          generator2
        );

      const bool result_solovay_strassen_edge_is_prime_is_ok { (result_solovay_strassen_edge_is_prime == edge_case.second) };

      result_edge_is_ok = (result_solovay_strassen_edge_is_prime_is_ok && result_edge_is_ok);
    }

    return result_edge_is_ok;
  }

  auto example008b_solovay_strassen_prime_run() -> bool;

  auto example008b_solovay_strassen_prime_run() -> bool
  {
    // Use a pseudo-random seed for this test.

    random_engine1_type generator1(util::util_pseudorandom_time_point_seed::value<typename random_engine1_type::result_type>());
    random_engine2_type generator2(util::util_pseudorandom_time_point_seed::value<typename random_engine2_type::result_type>());

    // Select prime candidates from a range of 10^150 ... max(uint512_t) - 1.
    constexpr wide_integer_type
      dist_min
      (
        "1"
        "00000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000"
      );

    distribution_type
      dist1
      {
        dist_min,
        (std::numeric_limits<wide_integer_type>::max)() - 1
      };

    bool result_is_ok { false };

    // Set the maximum number of trials. But in the loop below,
    // we will certainly break prior to running so many trials.

    constexpr int max_trials { 8192 }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    int trials { 0 };

    for( ; trials < max_trials; ++trials)
    {
      // Perform a Solovay-Strassen versus Miller-Rabin primality comparison.
      // Each one should detect prime/non-prime with the same Boolean result
      // for a given prime candidate p0.

      #if defined(WIDE_INTEGER_NAMESPACE)
      using local_unsigned_fast_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::unsigned_fast_type;
      #else
      using local_unsigned_fast_type = ::math::wide_integer::unsigned_fast_type;
      #endif

      constexpr local_unsigned_fast_type number_of_trials { UINT8_C(56) };

      const wide_integer_type p0 { dist1(generator1) };

      distribution_type dist2 { wide_integer_type { 2U }, p0 - 1 };

      const bool result_solovay_strassen_is_prime =
        local_solovay_strassen::solovay_strassen
        (
          p0,
          number_of_trials,
          dist2,
          generator2
        );

      const bool result_miller_rabin_ctrl_is_prime =
        miller_rabin
        (
          p0,
          25,
          dist2,
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
             i < static_cast<unsigned>(UINT8_C(32));
  #else
             i < static_cast<unsigned>(UINT8_C(4));
  #endif
           ++i)
  {
    const auto result_prime_run_is_ok =
      local_example008b_solovay_strassen_prime::example008b_solovay_strassen_prime_run();

    result_is_ok = (result_prime_run_is_ok && result_is_ok);
  }

  {
    const auto result_prime_edges_is_ok =
      local_example008b_solovay_strassen_prime::example008b_solovay_strassen_prime_edges();

    result_is_ok = (result_prime_edges_is_ok && result_is_ok);
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

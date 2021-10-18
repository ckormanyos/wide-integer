///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// Build locally for test on MinGW or Strawberry via Git bash.
// cd C:/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/wide_integer

// When using -std=c++11
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++11 -I. -IC:/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example000a_builtin_convert.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe
// When using -std=c++2a
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++2a -I. -IC:/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example000a_builtin_convert.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe

// Compile as follows when using GCC's unsigned __int128
// When using -std=c++11
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++11 -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -DWIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL -I. -IC:/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp examples/example000a_builtin_convert.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe
// When using -std=c++2a
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++2a -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -DWIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL -I. -IC:/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp examples/example000a_builtin_convert.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe

// On Windows subsystem for LINUX
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/wide_integer

// When using -std=c++11 and g++
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++11 -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -DWIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL -I. -I/mnt/c/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp examples/example000a_builtin_convert.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe
// When using -std=c++20 and g++-10
// g++-10 -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++20 -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -DWIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL -I. -I/mnt/c/boost/boost_1_77_0 -pthread -lpthread test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_float_convert.cpp test/test_uintwide_t_int_convert.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp examples/example000a_builtin_convert.cpp test/test_uintwide_t_spot_values.cpp examples/example000_numeric_limits.cpp examples/example001_mul_div.cpp examples/example001a_div_mod.cpp examples/example002_shl_shr.cpp examples/example003_sqrt.cpp examples/example003a_cbrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example005a_pow_factors_of_p99.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp examples/example012_rsa_crypto.cpp -o wide_integer.exe

#include <chrono>
#include <iomanip>
#include <iostream>

#include <test/test_uintwide_t.h>
#include <test/test_uintwide_t_n_binary_ops_template.h>
#include <test/test_uintwide_t_n_binary_ops_template_signed.h>
#include <test/test_uintwide_t_n_binary_ops_mul_n_by_m_template.h>
#include <test/test_uintwide_t_n_binary_ops_mul_div_4_by_4_template.h>

#if defined(__clang__)
  #if defined __has_feature && __has_feature(thread_sanitizer)
  #define UINTWIDE_T_REDUCE_TEST_DEPTH
  #endif
#elif defined(__GNUC__)
  #if defined(__SANITIZE_THREAD__)
  #define UINTWIDE_T_REDUCE_TEST_DEPTH
  #endif
#endif

namespace local {

using clock_type = std::chrono::high_resolution_clock;

auto wide_decimal_time_start = clock_type::now();

#if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
constexpr std::size_t test_uintwide_t_n_binary_ops_rounds = 4U;
#else
constexpr std::size_t test_uintwide_t_n_binary_ops_rounds = 1U;
#endif

#if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
constexpr std::size_t test_uintwide_t_n_binary_ops_4_by_4_cases = std::uint32_t(1UL << 15U);
#else
constexpr std::size_t test_uintwide_t_n_binary_ops_4_by_4_cases = std::uint32_t(1UL << 9U);
#endif

bool test_uintwide_t_small_bits()
{
  std::cout << "running: test_uintwide_t_small_bits" << std::endl;

  bool result_is_ok = true;

  {
    using local_uint16_t = math::wide_integer::uintwide_t<16U, std::uint8_t>;

    local_uint16_t a = UINT16_C(0x5522);
    local_uint16_t b = UINT16_C(0xFFEE);

    local_uint16_t c = a * b;

    result_is_ok &= (c == UINT32_C(0x039C));
  }

  {
    using local_uint24_t = math::wide_integer::uintwide_t<24U, std::uint8_t>;

    local_uint24_t a = UINT32_C(0x11FF5522);
    local_uint24_t b = UINT32_C(0xABCDFFEE);

    local_uint24_t c = a * b;

    result_is_ok &= (c == UINT32_C(0xF368039C));
  }

  {
    using local_uint32_t = math::wide_integer::uintwide_t<32U, std::uint16_t>;

    local_uint32_t a = UINT32_C(0x11FF5522);
    local_uint32_t b = UINT32_C(0xABCDFFEE);

    local_uint32_t c = a * b;

    result_is_ok &= (c == UINT32_C(0xF368039C));
  }

  return result_is_ok;
}

bool test_uintwide_t_boost_backend()
{
  std::cout << "running: test_uintwide_t_boost_backend" << std::endl;
  const bool result_test_uintwide_t_boost_backend_is_ok = math::wide_integer::test_uintwide_t_boost_backend();
  return result_test_uintwide_t_boost_backend_is_ok;
}

bool test_uintwide_t_examples()
{
  std::cout << "running: test_uintwide_t_examples" << std::endl;
  const bool result_test_uintwide_t_examples_is_ok = math::wide_integer::test_uintwide_t_examples();
  return result_test_uintwide_t_examples_is_ok;
}

bool test_uintwide_t_edge_cases()
{
  std::cout << "running: test_uintwide_t_edge_cases" << std::endl;
  const bool result_test_uintwide_t_edge_cases_is_ok = math::wide_integer::test_uintwide_t_edge_cases();
  return result_test_uintwide_t_edge_cases_is_ok;
}

bool test_uintwide_t_float_convert()
{
  std::cout << "running: test_uintwide_t_float_convert" << std::endl;
  const bool result_test_uintwide_t_float_convert_is_ok = math::wide_integer::test_uintwide_t_float_convert();
  return result_test_uintwide_t_float_convert_is_ok;
}

bool test_uintwide_t_int_convert()
{
  std::cout << "running: test_uintwide_t_int_convert" << std::endl;
  const bool result_test_uintwide_t_int_convert_is_ok = math::wide_integer::test_uintwide_t_int_convert();
  return result_test_uintwide_t_int_convert_is_ok;
}

bool test_uintwide_t_spot_values()
{
  std::cout << "running: test_uintwide_t_spot_values" << std::endl;
  const bool result_test_uintwide_t_spot_values_is_ok = math::wide_integer::test_uintwide_t_spot_values();
  return result_test_uintwide_t_spot_values_is_ok;
}

bool test_uintwide_t_0000024()
{
  std::cout << "running: test_uintwide_t_0000024" << std::endl;
  test_uintwide_t_n_binary_ops_template<24U, std::uint8_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000048()
{
  std::cout << "running: test_uintwide_t_0000048" << std::endl;
  test_uintwide_t_n_binary_ops_template<48U, std::uint16_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000064()
{
  std::cout << "running: test_uintwide_t_0000064" << std::endl;
  test_uintwide_t_n_binary_ops_template<64U, std::uint32_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000064_signed()
{
  std::cout << "running: test_uintwide_t_0000064_signed" << std::endl;
  test_uintwide_t_n_binary_ops_template_signed<64U, std::uint16_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000096()
{
  std::cout << "running: test_uintwide_t_0000096" << std::endl;
  test_uintwide_t_n_binary_ops_template<96U, std::uint16_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000128()
{
  std::cout << "running: test_uintwide_t_0000128" << std::endl;
  test_uintwide_t_n_binary_ops_template<128U> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000256()
{
  std::cout << "running: test_uintwide_t_0000256" << std::endl;
  test_uintwide_t_n_binary_ops_template<256U> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

#if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
bool test_uintwide_t_0000256_limb_type_uint64_t()
{
  std::cout << "running: test_uintwide_t_0000256_limb_type_uint64_t" << std::endl;
  test_uintwide_t_n_binary_ops_template<256U, std::uint64_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}
#endif

bool test_uintwide_t_0000512()
{
  std::cout << "running: test_uintwide_t_0000512" << std::endl;
  test_uintwide_t_n_binary_ops_template<512U> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000512_signed()
{
  std::cout << "running: test_uintwide_t_0000512_signed" << std::endl;
  test_uintwide_t_n_binary_ops_template_signed<512U> test_uintwide_t_n_binary_ops_template_signed_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_signed_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0001024()
{
  std::cout << "running: test_uintwide_t_0001024" << std::endl;
  test_uintwide_t_n_binary_ops_template<1024U> test_uintwide_t_n_binary_ops_template_instance(1UL << 12U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0002048()
{
  std::cout << "running: test_uintwide_t_0002048" << std::endl;
  test_uintwide_t_n_binary_ops_template<2048U> test_uintwide_t_n_binary_ops_template_instance(1UL << 11U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0008192()
{
  std::cout << "running: test_uintwide_t_0008192" << std::endl;
  test_uintwide_t_n_binary_ops_template<8192U> test_uintwide_t_n_binary_ops_template_instance(1UL << 8U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

#if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
bool test_uintwide_t_0008192_limb_type_uint64_t()
{
  std::cout << "running: test_uintwide_t_0008192_limb_type_uint64_t" << std::endl;
  test_uintwide_t_n_binary_ops_template<8192U, std::uint64_t> test_uintwide_t_n_binary_ops_template_instance(1UL << 8U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}
#endif

bool test_uintwide_t_0012288()
{
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
  constexpr std::size_t count = std::size_t(1UL << 5U);
  #else
  constexpr std::size_t count = std::size_t(1UL << 7U);
  #endif

  std::cout << "running: test_uintwide_t_0012288" << std::endl;
  test_uintwide_t_n_binary_ops_template<12288U> test_uintwide_t_n_binary_ops_template_instance(count);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0032768()
{
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
  constexpr std::size_t count = std::size_t(1UL << 5U);
  #else
  constexpr std::size_t count = std::size_t(1UL << 7U);
  #endif

  std::cout << "running: test_uintwide_t_0032768" << std::endl;
  test_uintwide_t_n_binary_ops_template<32768U> test_uintwide_t_n_binary_ops_template_instance(count);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

#if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
bool test_uintwide_t_0065536_alloc()
{
  std::cout << "running: test_uintwide_t_0065536_alloc" << std::endl;
  test_uintwide_t_n_binary_ops_template<65536U, std::uint32_t, std::allocator<std::uint32_t>> test_uintwide_t_n_binary_ops_template_instance(1UL << 6U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}
#endif

bool test_uintwide_t_0008192_by_0012288()
{
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
  constexpr std::size_t count = std::size_t(1UL << 5U);
  #else
  constexpr std::size_t count = std::size_t(1UL << 7U);
  #endif

  std::cout << "running: test_uintwide_t_0008192_by_0012288" << std::endl;
  test_uintwide_t_n_binary_ops_mul_n_by_m_template<8192U, 12288U> test_uintwide_t_n_binary_ops_template_instance(count);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0012288_by_0008192()
{
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
  constexpr std::size_t count = std::size_t(1UL << 5U);
  #else
  constexpr std::size_t count = std::size_t(1UL << 7U);
  #endif

  std::cout << "running: test_uintwide_t_0012288_by_0008192" << std::endl;
  test_uintwide_t_n_binary_ops_mul_n_by_m_template<12288U, 8192U> test_uintwide_t_n_binary_ops_template_instance(count);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000032_by_0000032_4_by_4()
{
  std::cout << "running: test_uintwide_t_0000032_by_0000032_4_by_4" << std::endl;
  test_uintwide_t_n_binary_ops_mul_div_4_by_4_template<32U, std::uint8_t> test_uintwide_t_n_binary_ops_template_instance(test_uintwide_t_n_binary_ops_4_by_4_cases);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

bool test_uintwide_t_0000064_by_0000064_4_by_4()
{
  std::cout << "running: test_uintwide_t_0000064_by_0000064_4_by_4" << std::endl;
  test_uintwide_t_n_binary_ops_mul_div_4_by_4_template<64U, std::uint16_t> test_uintwide_t_n_binary_ops_template_instance(test_uintwide_t_n_binary_ops_4_by_4_cases);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  return result_is_ok;
}

} // namespace local

int main()
{
  using time_point_type = std::chrono::high_resolution_clock::time_point;

  const time_point_type start = local::clock_type::now();

  bool result_is_ok = true;

  result_is_ok &= local::test_uintwide_t_small_bits();                   std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_boost_backend();                std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_examples();                     std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_edge_cases();                   std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_float_convert();                std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_int_convert();                  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_spot_values();                  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000024();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000048();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000064();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000064_signed();               std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000096();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000128();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000256();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
  result_is_ok &= local::test_uintwide_t_0000256_limb_type_uint64_t();   std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #endif
  result_is_ok &= local::test_uintwide_t_0000512();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000512_signed();               std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0001024();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0002048();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0008192();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
  result_is_ok &= local::test_uintwide_t_0008192_limb_type_uint64_t();   std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #endif
  result_is_ok &= local::test_uintwide_t_0012288();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0032768();                      std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #if !defined(UINTWIDE_T_REDUCE_TEST_DEPTH)
  result_is_ok &= local::test_uintwide_t_0065536_alloc();                std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  #endif
  result_is_ok &= local::test_uintwide_t_0008192_by_0012288();           std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0012288_by_0008192();           std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000032_by_0000032_4_by_4();    std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
  result_is_ok &= local::test_uintwide_t_0000064_by_0000064_4_by_4();    std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  const time_point_type stop = local::clock_type::now();

  std::cout << "result_is_ok: "
            << std::boolalpha
            << result_is_ok
            << ", time: "
            << std::fixed
            << std::setprecision(1)
            << ((float) std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000.0F
            << "s"
            << std::endl;

  return (result_is_ok ? 0 : -1);
}

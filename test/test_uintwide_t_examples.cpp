///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <examples/example_uintwide_t.h>
#include <test/test_uintwide_t.h>

#include <iomanip>
#include <iostream>
#include <string>

namespace local
{
  auto print_bool_example_result(const std::string& str_test, const bool result_is_ok) -> void;

  auto print_bool_example_result(const std::string& str_test, const bool result_is_ok) -> void
  {
    std::stringstream strm { };

    strm << std::boolalpha << str_test << std::boolalpha << result_is_ok;

    std::cout << strm.str();
  }
} // namespace local

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::test_uintwide_t_examples() -> bool
#else
auto ::math::wide_integer::test_uintwide_t_examples() -> bool
#endif
{
  bool result_is_ok = true;

  result_is_ok = (math::wide_integer::example000_numeric_limits            () && result_is_ok); local::print_bool_example_result(  "result_is_ok after example000_numeric_limits          : ", result_is_ok);
  result_is_ok = (math::wide_integer::example000a_builtin_convert          () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example000a_builtin_convert        : ", result_is_ok);
  result_is_ok = (math::wide_integer::example001_mul_div                   () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example001_mul_div                 : ", result_is_ok);
  result_is_ok = (math::wide_integer::example001a_div_mod                  () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example001a_div_mod                : ", result_is_ok);
  result_is_ok = (math::wide_integer::example002_shl_shr                   () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example002_shl_shr                 : ", result_is_ok);
  result_is_ok = (math::wide_integer::example003_sqrt                      () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example003_sqrt                    : ", result_is_ok);
  result_is_ok = (math::wide_integer::example003a_cbrt                     () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example003a_cbrt                   : ", result_is_ok);
  result_is_ok = (math::wide_integer::example004_rootk_pow                 () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example004_rootk_pow               : ", result_is_ok);
  result_is_ok = (math::wide_integer::example005_powm                      () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example005_powm                    : ", result_is_ok);
  result_is_ok = (math::wide_integer::example005a_pow_factors_of_p99       () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example005a_pow_factors_of_p99     : ", result_is_ok);
  result_is_ok = (math::wide_integer::example006_gcd                       () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example006_gcd                     : ", result_is_ok);
  result_is_ok = (math::wide_integer::example007_random_generator          () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example007_random_generator        : ", result_is_ok);
  result_is_ok = (math::wide_integer::example008_miller_rabin_prime        () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example008_miller_rabin_prime      : ", result_is_ok);
  result_is_ok = (math::wide_integer::example008a_miller_rabin_prime       () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example008a_miller_rabin_prime     : ", result_is_ok);
  result_is_ok = (math::wide_integer::example008b_solovay_strassen_prime   () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example008b_solovay_strassen_prime : ", result_is_ok);
  result_is_ok = (math::wide_integer::example009_timed_mul                 () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example009_timed_mul               : ", result_is_ok);
  result_is_ok = (math::wide_integer::example009a_timed_mul_4_by_4         () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example009a_timed_mul_4_by_4       : ", result_is_ok);
  result_is_ok = (math::wide_integer::example009b_timed_mul_8_by_8         () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example009b_timed_mul_8_by_8       : ", result_is_ok);
  result_is_ok = (math::wide_integer::example010_uint48_t                  () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example010_uint48_t                : ", result_is_ok);
  result_is_ok = (math::wide_integer::example011_uint24_t                  () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example011_uint24_t                : ", result_is_ok);
  #if !(defined(_MSC_VER) && defined(_DEBUG))
  result_is_ok = (math::wide_integer::example012_rsa_crypto                () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example012_rsa_crypto              : ", result_is_ok);
  #endif
  result_is_ok = (math::wide_integer::example013_ecdsa_sign_verify         () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example013_ecdsa_sign_verify       : ", result_is_ok);
  result_is_ok = (math::wide_integer::example014_pi_spigot_wide            () && result_is_ok); local::print_bool_example_result("\nresult_is_ok after example014_pi_spigot_wide          : ", result_is_ok);

  std::cout << std::endl;

  return result_is_ok;
}

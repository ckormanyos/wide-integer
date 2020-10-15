///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <wide_integer/generic_template_uintwide_t.h>

bool test_uintwide_t_examples()
{
  bool result_is_ok = true;

  result_is_ok &= wide_integer::example001_mul_div               ();
  result_is_ok &= wide_integer::example001a_div_mod              ();
  result_is_ok &= wide_integer::example002_shl_shr               ();
  result_is_ok &= wide_integer::example003_sqrt                  ();
  result_is_ok &= wide_integer::example003a_cbrt                 ();
  result_is_ok &= wide_integer::example004_rootk_pow             ();
  result_is_ok &= wide_integer::example005_powm                  ();
  result_is_ok &= wide_integer::example006_gcd                   ();
  result_is_ok &= wide_integer::example007_random_generator      ();
  result_is_ok &= wide_integer::example008_miller_rabin_prime    ();
  result_is_ok &= wide_integer::example008a_miller_rabin_prime   ();
  result_is_ok &= wide_integer::example009_timed_mul             ();
  result_is_ok &= wide_integer::example010_uint48_t              ();
  result_is_ok &= wide_integer::example011_uint24_t              ();

  return result_is_ok;
}

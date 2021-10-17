///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef EXAMPLE_UINTWIDE_T_2021_04_29_H_
  #define EXAMPLE_UINTWIDE_T_2021_04_29_H_

  // This file contains function prototypes of the uintwide_t examples.

  namespace math { namespace wide_integer {

  bool example000_numeric_limits     ();
  bool example000a_builtin_convert   ();
  bool example001_mul_div            ();
  bool example001a_div_mod           ();
  bool example002_shl_shr            ();
  bool example003_sqrt               ();
  bool example003a_cbrt              ();
  bool example004_rootk_pow          ();
  bool example005_powm               ();
  bool example005a_pow_factors_of_p99();
  bool example006_gcd                ();
  bool example007_random_generator   ();
  bool example008_miller_rabin_prime ();
  bool example008a_miller_rabin_prime();
  bool example009_timed_mul          ();
  bool example009a_timed_mul_4_by_4  ();
  bool example009b_timed_mul_8_by_8  ();
  bool example010_uint48_t           ();
  bool example011_uint24_t           ();
  bool example012_rsa_crypto         ();

  } } // namespace math::wide_integer

#endif // EXAMPLE_UINTWIDE_T_2021_04_29_H_

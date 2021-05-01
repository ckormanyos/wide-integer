///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UINTWIDE_T_EXAMPLES_2021_04_29_H_
  #define UINTWIDE_T_EXAMPLES_2021_04_29_H_

  // This file contains function prototypes of the uintwide_t examples.

  #if __cplusplus > 201703L
    #define UINTWIDE_T_TEST_CONSTEXPR constexpr
  #else
    #define UINTWIDE_T_TEST_CONSTEXPR
  #endif

  namespace math { namespace wide_integer {

  bool example001_mul_div            ();
  bool example001a_div_mod           ();
  bool example002_shl_shr            ();
  bool example003_sqrt               ();
  bool example003a_cbrt              ();
  bool example004_rootk_pow          ();
  bool example005_powm               ();
  bool example006_gcd                ();
  bool example007_random_generator   ();
  bool example008_miller_rabin_prime ();
  bool example008a_miller_rabin_prime();
  bool example009_timed_mul          ();
  bool example009a_timed_mul_4_by_4  ();
  bool example010_uint48_t           ();
  bool example011_uint24_t           ();

  } } // namespace math::wide_integer

#endif // UINTWIDE_T_EXAMPLES_2021_04_29_H_

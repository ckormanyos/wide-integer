///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UINTWIDE_T_EXAMPLES_2021_04_29_H_
  #define UINTWIDE_T_EXAMPLES_2021_04_29_H_

  // This file contains function prototypes of the uintwide_t examples.

  #if defined(_MSC_VER)
    #if defined(_HAS_CXX20) && (_HAS_CXX20 != 0)
      #define UINTWIDE_T_EXAMPLES_CONSTEXPR constexpr
    #else
      #define UINTWIDE_T_EXAMPLES_CONSTEXPR
    #endif
  #else
    #if (defined(__cplusplus) && (__cplusplus >= 201402L))
      #if defined(__AVR__) && (!defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ > 6)))
      #define UINTWIDE_T_EXAMPLES_CONSTEXPR constexpr
      #elif (defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms>=201806))
        #if defined(__clang__)
          #if (__clang_major__ > 9)
          #define UINTWIDE_T_EXAMPLES_CONSTEXPR constexpr
          #else
          #define UINTWIDE_T_EXAMPLES_CONSTEXPR
          #endif
        #else
        #define UINTWIDE_T_EXAMPLES_CONSTEXPR constexpr
        #endif
      #else
      #define UINTWIDE_T_EXAMPLES_CONSTEXPR
      #endif
    #else
      #define UINTWIDE_T_EXAMPLES_CONSTEXPR
    #endif
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
  bool example009b_timed_mul_8_by_8  ();
  bool example010_uint48_t           ();
  bool example011_uint24_t           ();

  } } // namespace math::wide_integer

#endif // UINTWIDE_T_EXAMPLES_2021_04_29_H_

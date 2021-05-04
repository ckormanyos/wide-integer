///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef TEST_UINTWIDE_T_2019_12_15_H_
  #define TEST_UINTWIDE_T_2019_12_15_H_

  #if defined(_MSC_VER)
    #if defined(_HAS_CXX20) && (_HAS_CXX20 != 0)
      #define UINTWIDE_T_TESTS_CONSTEXPR constexpr
    #else
      #define UINTWIDE_T_TESTS_CONSTEXPR
    #endif
  #else
    #if (defined(__cplusplus) && (__cplusplus >= 201402L))
      #if defined(__AVR__) && (!defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ > 6)))
      #define UINTWIDE_T_TESTS_CONSTEXPR constexpr
      #elif (defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms>=201806))
        #if defined(__clang__)
          #if (__clang_major__ > 9)
          #define UINTWIDE_T_TESTS_CONSTEXPR constexpr
          #else
          #define UINTWIDE_T_TESTS_CONSTEXPR
          #endif
        #else
        #define UINTWIDE_T_TESTS_CONSTEXPR constexpr
        #endif
      #else
      #define UINTWIDE_T_TESTS_CONSTEXPR
      #endif
    #else
      #define UINTWIDE_T_TESTS_CONSTEXPR
    #endif
  #endif

  namespace math { namespace wide_integer {

  bool test_uintwide_t_boost_backend();
  bool test_uintwide_t_examples     ();
  bool test_uintwide_t_edge_cases   ();
  bool test_uintwide_t_spot_values  ();

  } } // namespace math::wide_integer

#endif // TEST_UINTWIDE_T_2019_12_15_H_

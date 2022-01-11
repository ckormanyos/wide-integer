///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef TEST_UINTWIDE_T_2019_12_15_H // NOLINT(llvm-header-guard)
  #define TEST_UINTWIDE_T_2019_12_15_H

  #include <math/wide_integer/uintwide_t.h>

  WIDE_INTEGER_NAMESPACE_BEGIN

  namespace math { namespace wide_integer {

  auto test_uintwide_t_boost_backend() -> bool;
  auto test_uintwide_t_examples     () -> bool;
  auto test_uintwide_t_edge_cases   () -> bool;
  auto test_uintwide_t_float_convert() -> bool;
  auto test_uintwide_t_int_convert  () -> bool;
  auto test_uintwide_t_spot_values  () -> bool;

  } // namespace wide_integer
  } // namespace math

  WIDE_INTEGER_NAMESPACE_END

  #if defined(WIDE_INTEGER_NAMESPACE)
  using namespace WIDE_INTEGER_NAMESPACE;
  #else
  #endif

#endif // TEST_UINTWIDE_T_2019_12_15_H

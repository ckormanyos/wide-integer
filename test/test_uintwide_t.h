///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef TEST_UINTWIDE_T_2019_12_15_H_
  #define TEST_UINTWIDE_T_2019_12_15_H_

  namespace math { namespace wide_integer {

  bool test_uintwide_t_boost_backend();
  bool test_uintwide_t_examples     ();
  bool test_uintwide_t_edge_cases   ();
  bool test_uintwide_t_float_convert();
  bool test_uintwide_t_int_convert  ();
  bool test_uintwide_t_spot_values  ();

  } } // namespace math::wide_integer

#endif // TEST_UINTWIDE_T_2019_12_15_H_

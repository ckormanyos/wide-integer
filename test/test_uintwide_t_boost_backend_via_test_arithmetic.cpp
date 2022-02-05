///////////////////////////////////////////////////////////////
//  Copyright 2022 Christopher Kormanyos.
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/uintwide_t_backend.hpp>

#include "test_arithmetic.hpp"

#include <test/test_uintwide_t.h>


// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/wide_integer
// g++-10 -finline-functions -march=native -mtune=native -O3 -Wall -std=gnu++20 -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -I. -I/mnt/c/boost/boost_1_78_0 test/test_uintwide_t_boost_backend_via_test_arithmetic.cpp -o test_uintwide_t_boost_backend_via_test_arithmetic.exe

int main()
{
  using local_big_uint_backend_type =
    boost::multiprecision::uintwide_t_backend<static_cast<math::wide_integer::size_t>(UINT32_C(1024)), std::uint8_t, std::allocator<void>>;

  using local_big_uint_type =
    boost::multiprecision::number<local_big_uint_backend_type,
                                  boost::multiprecision::et_off>;

  test<local_big_uint_type>();

  return (boost::report_errors() == 0);
}

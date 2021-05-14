///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_examples.h>

bool math::wide_integer::example000a_builtin_convert()
{
  bool result_is_ok = true;

  using int256_t = math::wide_integer::int256_t;

  {
    const int256_t n = -1234567.89;

    const bool result_n_is_ok = (n == -1234567);

    result_is_ok &= result_n_is_ok;
  }

  {
    const int256_t n = "-12345678900000000000000000000000";

    const float    f = (float) n;

    using std::fabs;

    const float closeness     = fabs(1.0F - fabs(f / -1.23456789E31F));
    const bool result_f_is_ok = (closeness < std::numeric_limits<float>::epsilon());

    result_is_ok &= result_f_is_ok;
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example000a_builtin_convert();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

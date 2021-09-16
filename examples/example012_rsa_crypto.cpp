///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_examples.h>

bool math::wide_integer::example012_rsa_crypto()
{
  const bool result_is_ok = true;

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example012_rsa_crypto();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <wide_integer/generic_template_uintwide_t.h>

namespace
{
  std::array<char, 3335U> str_a;
  std::array<char, 1113U> str_control;
}

bool wide_integer::example012_uint64_t_limb()
{
  using uint11264_t = wide_integer::generic_template::uintwide_t<11264U, std::uint64_t>;

  // Create the string '1' + 3,333 times '0', which is
  // equivalent to the decimal integral value 10^3333.

  std::fill(str_a.begin() + 1U,
            str_a.begin() + 1U + 3333U,
            '0');

  str_a.front() = '1';
  str_a.back()  = '\0';

  const uint11264_t a = str_a.data();

  const uint11264_t s = cbrt(a);

  // Create the string '1' + 1,111 times '0', which is
  // equivalent to the decimal integral value 10^1111.
  // (This is the cube root of 10^3333.)
  std::fill(str_control.begin() + 1U,
            str_control.begin() + 1U + 1111U,
            '0');

  str_control.front() = '1';
  str_control.back()  = '\0';

  const bool result_is_ok = (s == str_control.data());

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example012_uint64_t_limb();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

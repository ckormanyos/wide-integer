///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>

#include <wide_integer/generic_template_uintwide_t.h>

int main()
{
  using uint256_t = wide_integer::generic_template::uint256_t;

  bool result_is_ok_root;
  bool result_is_ok_pow;

  {
    const uint256_t x("0x95E0E51079E1D11737D3FD01429AA745582FEB4381D61FA56948C1A949E43C32");
    const uint256_t r = rootk(x, 7U);

    result_is_ok_root = (r == UINT64_C(0x16067D1894));
  }

  {
    const uint256_t r(UINT64_C(0x16067D1894));
    const uint256_t p = pow(r, 7U);

    result_is_ok_pow = (p == "0x95E0E5104B2F636571834936C982E40EFA25682E7370CD1C248051E1CDC34000");
  }

  std::cout << "result_is_ok_root: " << std::boolalpha << result_is_ok_root << std::endl;
  std::cout << "result_is_ok_pow : " << std::boolalpha << result_is_ok_pow  << std::endl;
}

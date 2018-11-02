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
    const uint256_t a("0x03DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
    const uint256_t s = rootk(a, 5U);

    result_is_ok_root = (s == "0x3F9680655F23C");
  }

  {
    const uint256_t s("0x3F9680655F23C");
    const uint256_t p = pow(s, 5U);

    result_is_ok_pow = (p == "0x03DF741DE58BC8B2A8C840BD0321CAB5CA92190FFCCCB886DEF30AFF3F933C00");
  }

  std::cout << "result_is_ok_root: " << std::boolalpha << result_is_ok_root << std::endl;
  std::cout << "result_is_ok_pow : " << std::boolalpha << result_is_ok_pow  << std::endl;
}

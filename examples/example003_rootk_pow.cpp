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
    const uint256_t s = rootk(a, 7U);

    result_is_ok_root = (s == UINT64_C(0xD10A003C0));
  }

  {
    const uint256_t s(UINT64_C(0xD10A003C0));
    const uint256_t p = pow(s, 7U);

    result_is_ok_pow = (p == "0x03DF741DE41E75AB653AB23DF2C2E1ED0FCB88B6410E63BFC26DBC0000000000");
  }

  std::cout << "result_is_ok_root: " << std::boolalpha << result_is_ok_root << std::endl;
  std::cout << "result_is_ok_pow : " << std::boolalpha << result_is_ok_pow  << std::endl;
}

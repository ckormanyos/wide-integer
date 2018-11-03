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

  const uint256_t a("0x4B89A8873F158D0C7200E4182789A5D011C6E47A56F982A6BC326770ECE7ED36");
  const uint256_t b("0x0797EF9AA44F66C632B2020F83C0DC30BC4E1C996782CFDC3931E36ED9DCB0B6");

  const uint256_t c = gcd(a, b);

  const bool result_is_ok = (c == 6U);

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

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

  const uint256_t a("95171305638294180544026029937381887996496533912928724156660670534452138401407");
  const uint256_t b("115088126363907011876813492439486921385995039675620908421742065814036688882888");

  const uint256_t c = gcd(a, b);

  const bool result_is_ok = (std::uint32_t(c) == UINT32_C(12170749));

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

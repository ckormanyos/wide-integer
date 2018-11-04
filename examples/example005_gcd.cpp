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

  const uint256_t a("65817543385799202331129824632578810170261660210697994406969361012031085400920");
  const uint256_t b("42832132932758279435945349456906220232760184148171721872947071577727211231630");

  const uint256_t c = gcd(a, b);

  const bool result_is_ok = (std::uint16_t(c) == 2010U);

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

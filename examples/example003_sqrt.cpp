///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iomanip>
#include <iostream>

#include <wide_integer/generic_template_uintwide_t.h>

namespace local
{
  template<typename UnsignedIntegerType>
  UnsignedIntegerType sqrt(const UnsignedIntegerType& m)
  {
    // Based on the pseudo-code of Algorithm 1.13 SqrtInt,
    // from R.P. Brent and P. Zimmermann, "Modern Computer
    // Arithmetic", Cambridge University Press, 2011.

    using local_unsigned_integral_type = UnsignedIntegerType;

    // TBD: Use a more advanced algorithm
    // to obtain a better initial value.
    local_unsigned_integral_type u(m >> 1);

    for (std::size_t i = 0U; i < 10000U; ++i)
    {
      const local_unsigned_integral_type s = u;

      const local_unsigned_integral_type t = s + (m / s);

      u = t >> 1;

      if (u >= s)
      {
        return s;
      }
    }

    return local_unsigned_integral_type(std::uint_fast8_t(0U));
  }

  using uint256_t = wide_integer::generic_template::uint256_t;
}

int main()
{
  const local::uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");

  const local::uint256_t s = local::sqrt(a);

  const bool result_is_ok =
    (s == "0xFA5FE7853F1D4AD92BDF244179CA178B");

  std::cout << "result_is_ok: "
            << std::boolalpha
            << result_is_ok
            << std::endl
            << "sqrt(" << std::hex << "0x" << std::uppercase << a << ") is:"
            << std::endl
            << std::hex << "0x" << std::uppercase << s
            << std::endl;
}

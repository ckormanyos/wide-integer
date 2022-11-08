///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <sstream>
#include <string>

#if !defined(WIDE_INTEGER_DISABLE_PRIVATE_CLASS_DATA_MEMBERS)
#define WIDE_INTEGER_DISABLE_PRIVATE_CLASS_DATA_MEMBERS
#endif

#include <math/wide_integer/uintwide_t.h>

namespace from_issue_335
{
  // See also: https://github.com/ckormanyos/wide-integer/issues/266

  template<typename UInt,
           uint32_t BitCount = 8 * sizeof(UInt),
           UInt MaxValue = -UInt(1)>
  auto f(uint32_t n) -> std::string
  {
    std::stringstream strm;

    strm << BitCount << "-bit ; MaxValue = " << MaxValue << ", n = " << UInt(n);

    return strm.str();
  }

  auto test_uintwide_t_xtra_from_issue_335() -> bool
  {
    // String result:
    //   "256-bit ; MaxValue = 115792089237316195423570985008687907853269984665640564039457584007913129639935, n = 42"
    const auto str_result = f<::math::wide_integer::uint256_t>(42);

    std::cout << str_result << std::endl;

    const auto result_is_ok =
    (
      str_result == "256-bit ; MaxValue = 115792089237316195423570985008687907853269984665640564039457584007913129639935, n = 42"
    );

    return result_is_ok;
  }
}

auto main() -> int
{
  const auto result_is_ok = from_issue_335::test_uintwide_t_xtra_from_issue_335();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

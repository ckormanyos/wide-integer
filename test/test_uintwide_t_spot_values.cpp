///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_test.h>

bool math::wide_integer::test_uintwide_t_spot_values()
{
  bool result_is_ok = true;

  {
    using uint512_t = math::wide_integer::uint512_t;

    const uint512_t a("698937339790347543053797400564366118744312537138445607919548628175822115805812983955794321304304417541511379093392776018867245622409026835324102460829431");
    const uint512_t b("100041341335406267530943777943625254875702684549707174207105689918734693139781");

    const uint512_t c = (a / b);
    const uint512_t d = (a % b);

    //   QuotientRemainder
    //     [698937339790347543053797400564366118744312537138445607919548628175822115805812983955794321304304417541511379093392776018867245622409026835324102460829431,
    //      100041341335406267530943777943625254875702684549707174207105689918734693139781]
    //
    //     {6986485091668619828842978360442127600954041171641881730123945989288792389271,
    //      100041341335406267530943777943625254875702684549707174207105689918734693139780}

    const bool c_is_ok = (c == "6986485091668619828842978360442127600954041171641881730123945989288792389271");
    const bool d_is_ok = (d == "100041341335406267530943777943625254875702684549707174207105689918734693139780");

    result_is_ok &= (c_is_ok && d_is_ok);
  }

  {
    using uint256_t =
      math::wide_integer::uintwide_t<256U, std::uint32_t>;

    static_assert(std::numeric_limits<uint256_t>::digits == 256,
                  "Error: Incorrect digit count for this example");

    // Note: Some of the comments in this file use the Wolfram Language(TM).
    //
    // Create two pseudo-random 256-bit unsigned integers.
    //   Table[IntegerString[RandomInteger[(2^256) - 1], 16], 2]
    //
    //   {F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
    //    166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75}
    //
    // Set the values of two random 256-bit unsigned integers.
    //   a = 0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE
    //   b = 0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
    //
    // Multiply:
    //   a * b = 0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076
    //
    // Divide:
    //   a / b = 10
    //
    // Modulus:
    //   a % b = 0x14998D5CA3DB6385F7DEDF4621DE48A9104AC13797C6567713D7ABC216D7AB4C

    WIDE_INTEGER_CONSTEXPR uint256_t a
    (
      {
        UINT32_C(0x410065DE),
        UINT32_C(0x3BDEED78),
        UINT32_C(0x80AF54D5),
        UINT32_C(0xCFC456CB),
        UINT32_C(0x026EF9CB),
        UINT32_C(0x37F18372),
        UINT32_C(0xE58BCB2F),
        UINT32_C(0xF4DF741D)
      }
    );

    WIDE_INTEGER_CONSTEXPR uint256_t b
    (
      {
        UINT32_C(0x9DD0DF75),
        UINT32_C(0x3733ECF8),
        UINT32_C(0x974A7FD6),
        UINT32_C(0x4658F55B),
        UINT32_C(0x6341AB50),
        UINT32_C(0xECCEAA04),
        UINT32_C(0x202B3D90),
        UINT32_C(0x166D63E0)
      }
    );

    WIDE_INTEGER_CONSTEXPR uint256_t c
    (
      {
        UINT32_C(0xF84AF076),
        UINT32_C(0x92D5AE70),
        UINT32_C(0xD2D71C55),
        UINT32_C(0xBE3676AA),
        UINT32_C(0x4F7F7D99),
        UINT32_C(0x6C61F9A0),
        UINT32_C(0xC57EB430),
        UINT32_C(0xE491A360)
      }
    );

    result_is_ok &= ((a * b) == c);

    WIDE_INTEGER_CONSTEXPR uint256_t q(10U);

    result_is_ok &= ((a / b) == q);

    WIDE_INTEGER_CONSTEXPR uint256_t m
    (
      {
        UINT32_C(0x16D7AB4C),
        UINT32_C(0x13D7ABC2),
        UINT32_C(0x97C65677),
        UINT32_C(0x104AC137),
        UINT32_C(0x21DE48A9),
        UINT32_C(0xF7DEDF46),
        UINT32_C(0xA3DB6385),
        UINT32_C(0x14998D5C)
      }
    );

    result_is_ok &= ((a % b) == m);
  }

  return result_is_ok;
}

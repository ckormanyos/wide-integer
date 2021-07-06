///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <sstream>

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_test.h>

bool math::wide_integer::test_uintwide_t_spot_values()
{
  bool result_is_ok = true;

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/108
    {
      using w_t  = math::wide_integer::uintwide_t<32U, std::uint32_t, void, true>;
      using ww_t = math::wide_integer::uintwide_t<64U, std::uint32_t, void, true>;

      w_t  neg     (-2);
      ww_t neg_wide(-2);
      ww_t neg_wide_cast = ww_t(neg);

      std::string str_neg;
      std::string str_neg_wide;
      std::string str_neg_wide_cast;

      { std::stringstream strm; strm << neg;           str_neg           = strm.str(); }
      { std::stringstream strm; strm << neg_wide;      str_neg_wide      = strm.str(); }
      { std::stringstream strm; strm << neg_wide_cast; str_neg_wide_cast = strm.str(); }

      const bool result_neg_is_ok           = (str_neg           == "-2");
      const bool result_neg_wide_is_ok      = (str_neg_wide      == "-2");
      const bool result_neg_wide_cast_is_ok = (str_neg_wide_cast == "-2");

      result_is_ok &= (   result_neg_is_ok
                       && result_neg_wide_is_ok
                       && result_neg_wide_cast_is_ok);
    }

    {
      using w_t  = math::wide_integer::uintwide_t<32U, std::uint8_t, void, true>;
      using ww_t = math::wide_integer::uintwide_t<64U, std::uint8_t, void, true>;

      w_t  neg     (-2);
      ww_t neg_wide(-2);
      ww_t neg_wide_cast = ww_t(neg);

      std::string str_neg;
      std::string str_neg_wide;
      std::string str_neg_wide_cast;

      { std::stringstream strm; strm << neg;           str_neg           = strm.str(); }
      { std::stringstream strm; strm << neg_wide;      str_neg_wide      = strm.str(); }
      { std::stringstream strm; strm << neg_wide_cast; str_neg_wide_cast = strm.str(); }

      const bool result_neg_is_ok           = (str_neg           == "-2");
      const bool result_neg_wide_is_ok      = (str_neg_wide      == "-2");
      const bool result_neg_wide_cast_is_ok = (str_neg_wide_cast == "-2");

      result_is_ok &= (   result_neg_is_ok
                       && result_neg_wide_is_ok
                       && result_neg_wide_cast_is_ok);
    }
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/63
    WIDE_INTEGER_CONSTEXPR auto
    input
    {
      math::wide_integer::uintwide_t<320U, std::uint32_t, void, true>
      {
        1729348762983LL
      }
    };

    WIDE_INTEGER_CONSTEXPR bool result_ll_is_ok = (static_cast<long long>(input) == 1729348762983LL);

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_ll_is_ok, "Error: test_uintwide_t_spot_values unsigned not OK!");
    #endif

    result_is_ok &= result_ll_is_ok;
  }

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

    WIDE_INTEGER_CONSTEXPR uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");

    WIDE_INTEGER_CONSTEXPR uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

    WIDE_INTEGER_CONSTEXPR uint256_t c("0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076");

    result_is_ok &= ((a * b) == c);

    WIDE_INTEGER_CONSTEXPR uint256_t q(10U);

    result_is_ok &= ((a / b) == q);

    WIDE_INTEGER_CONSTEXPR uint256_t m("0x14998D5CA3DB6385F7DEDF4621DE48A9104AC13797C6567713D7ABC216D7AB4C");

    result_is_ok &= ((a % b) == m);
  }

  return result_is_ok;
}

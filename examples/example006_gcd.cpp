///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example006_gcd() -> bool
#else
auto ::math::wide_integer::example006_gcd() -> bool
#endif
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  using WIDE_INTEGER_NAMESPACE::math::wide_integer::uint256_t;
  #else
  using ::math::wide_integer::uint256_t;
  #endif

  auto result_is_ok = true;

  {
    WIDE_INTEGER_CONSTEXPR auto a = uint256_t("7331125833173952065785419415459959607336636601196096595267521072574633406453");
    WIDE_INTEGER_CONSTEXPR auto b = uint256_t("81851102853488233888613042082614484613197092732034035303256305811964538942381");

    WIDE_INTEGER_CONSTEXPR auto c = gcd(a, b);

    WIDE_INTEGER_CONSTEXPR auto result_gcd_is_ok = (static_cast<std::uint32_t>(c) == static_cast<std::uint32_t>(UINT32_C(11759761)));

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_gcd_is_ok, "Error: example006_gcd not OK!");
    #endif

    result_is_ok = (result_gcd_is_ok && result_is_ok);
  }

  {
    WIDE_INTEGER_CONSTEXPR auto a = uint256_t("0xD2690CD26CD57A3C443993851A70D3B62F841573668DF7B229508371A0AEDE7F");
    WIDE_INTEGER_CONSTEXPR auto b = uint256_t("0xFE719235CD0B1A314D4CA6940AEDC38BDF8E9484E68CE814EDAA17D87B0B4CC8");

    WIDE_INTEGER_CONSTEXPR auto c = gcd(a, b);

    WIDE_INTEGER_CONSTEXPR auto result_gcd_is_ok = (static_cast<std::uint32_t>(c) == static_cast<std::uint32_t>(UINT32_C(12170749)));

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_gcd_is_ok, "Error: example006_gcd not OK!");
    #endif

    result_is_ok = (result_gcd_is_ok && result_is_ok);
  }

  {
    WIDE_INTEGER_CONSTEXPR auto a = uint256_t("3295797818601939030222216527897366111881692967620286262162602563410793404042");
    WIDE_INTEGER_CONSTEXPR auto b = uint256_t("55191470623654360751881872340477602850990868951383305891019018775544978982943");

    WIDE_INTEGER_CONSTEXPR auto c = gcd(a, b);

    WIDE_INTEGER_CONSTEXPR auto result_gcd_is_ok = (static_cast<std::uint32_t>(c) == static_cast<std::uint32_t>(UINT32_C(13520497)));

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_gcd_is_ok, "Error: example006_gcd not OK!");
    #endif

    result_is_ok = (result_gcd_is_ok && result_is_ok);
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE006_GCD)

#include <iomanip>
#include <iostream>

auto main() -> int
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const auto result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example006_gcd();
  #else
  const auto result_is_ok = ::math::wide_integer::example006_gcd();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

#endif

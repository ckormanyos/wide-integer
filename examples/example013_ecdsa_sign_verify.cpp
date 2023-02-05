///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local_example013_ecdsa
{
  template<const unsigned CurveBits,
           typename LimbType,
           const char* PointX,
           const char* PointY>
  struct ecc_point
  {
    #if defined(WIDE_INTEGER_NAMESPACE)
    using uint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<math::wide_integer::size_t>(CurveBits), LimbType>;
    #else
    using uint_type = ::math::wide_integer::uintwide_t<static_cast<math::wide_integer::size_t>(CurveBits), LimbType>;
    #endif

    using limb_type = typename uint_type::limb_type;

    using point_type =
      struct point_type
      {
        WIDE_INTEGER_CONSTEXPR point_type(uint_type x = uint_type(0),
                                          uint_type y = uint_type(0)) noexcept
          : my_x(x),
            my_y(y) { }

        const uint_type my_x;
        const uint_type my_y;
      };

    #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))
    static WIDE_INTEGER_CONSTEXPR auto value_g() noexcept -> point_type
    {
      return point_type { uint_type(PointX), uint_type(PointY) };
    }
    #else
    static auto value_g() noexcept -> const point_type&
    {
      static const point_type pt { uint_type(PointX), uint_type(PointY) };

      return pt;
    }
    #endif
  };

  template<const unsigned CurveBits,
           typename LimbType,
           const char* CurveName,
           const char* FieldCharacteristicP,
           const int   CurveCoefficientA,
           const int   CurveCoefficientB,
           const char* BasePointGx,
           const char* BasePointGy,
           const char* SubGroupOrder,
           const int   SubGroupCoFactor>
  struct elliptic_curve : public ecc_point<CurveBits, LimbType, BasePointGx, BasePointGy>
  {
    using base_class_type = ecc_point<CurveBits, LimbType, BasePointGx, BasePointGy>;

    using uint_type = typename base_class_type::uint_type;
    using limb_type = typename base_class_type::limb_type;

    #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))
    static WIDE_INTEGER_CONSTEXPR auto value_p () noexcept -> uint_type { return uint_type(FieldCharacteristicP); }
    static WIDE_INTEGER_CONSTEXPR auto value_o () noexcept -> uint_type { return uint_type(SubGroupOrder); }

    static WIDE_INTEGER_CONSTEXPR auto value_gx() noexcept -> uint_type { return base_class_type::value_g().my_x; }
    static WIDE_INTEGER_CONSTEXPR auto value_gy() noexcept -> uint_type { return base_class_type::value_g().my_y; }
    #else
    static auto value_p () noexcept -> const uint_type& { static const uint_type vp(FieldCharacteristicP); return vp; }
    static auto value_o () noexcept -> const uint_type& { static const uint_type vo(SubGroupOrder);        return vo; }

    static auto value_gx() noexcept -> const uint_type& { static const uint_type vgx(base_class_type::value_g().my_x); return vgx; }
    static auto value_gy() noexcept -> const uint_type& { static const uint_type vgy(base_class_type::value_g().my_y); return vgy; }
    #endif
  };

  constexpr char CurveName           [] = "secp256k1";
  constexpr char FieldCharacteristicP[] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F";
  constexpr char BasePointGx         [] = "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798";
  constexpr char BasePointGy         [] = "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8";
  constexpr char SubGroupOrder       [] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141";

} // namespace local_example013_ecdsa

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example013_ecdsa_sign_verify() -> bool
#else
auto ::math::wide_integer::example013_ecdsa_sign_verify() -> bool
#endif
{
  using namespace local_example013_ecdsa;

  using elliptic_curve_type =
    elliptic_curve<256U, std::uint32_t, CurveName, FieldCharacteristicP, 0, 7, BasePointGx, BasePointGy, SubGroupOrder, 1>;

  #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))

  static_assert(elliptic_curve_type::value_p () == elliptic_curve_type::uint_type("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"),
                "Error: Elliptic curve Field Characteristic p is seemingly incorrect");

  static_assert(elliptic_curve_type::value_o () == elliptic_curve_type::uint_type("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"),
                "Error: Elliptic curve Sub-Group Order is seemingly incorrect");

  static_assert(elliptic_curve_type::value_gx() == elliptic_curve_type::uint_type("0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"),
                "Error: Elliptic curve base-point Gx is seemingly incorrect");

  static_assert(elliptic_curve_type::value_gy() == elliptic_curve_type::uint_type("0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"),
                "Error: Elliptic curve base-point Gx is seemingly incorrect");

  #else
  static_cast<void>(elliptic_curve_type::value_p());
  #endif

  const auto result_is_ok = true;

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE013_ECDSA_SIGN_VERIFY)

#include <iomanip>
#include <iostream>

auto main() -> int
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const auto result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example013_ecdsa_sign_verify();
  #else
  const auto result_is_ok = ::math::wide_integer::example013_ecdsa_sign_verify();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

#endif

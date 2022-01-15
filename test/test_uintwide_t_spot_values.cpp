///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cassert>
#include <sstream>

#include <math/wide_integer/uintwide_t.h>
#include <test/test_uintwide_t.h>

namespace local
{
  template<typename UnknownIntegerType>
  auto test_uintwide_t_spot_values_from_issue_145(const UnknownIntegerType x) -> bool
  {
    // See also https://github.com/ckormanyos/wide-integer/issues/145#issuecomment-1006374713

    using local_unknown_integer_type = UnknownIntegerType;

    bool local_result_is_ok = true;

    const auto a0(x);

    #if defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    #endif

    {
      local_unknown_integer_type a = a0; a += a; // NOLINT(clang-diagnostic-self-assign-overloaded)

      local_result_is_ok &= (a == (2U * a0));
    }

    {
      local_unknown_integer_type a = a0; a -= a; // NOLINT(clang-diagnostic-self-assign-overloaded)

      local_result_is_ok &= (a == 0U);
    }

    {
      local_unknown_integer_type a = a0; a /= a; // NOLINT(clang-diagnostic-self-assign-overloaded)

      local_result_is_ok &= (a == 1U);
    }

    #if defined(__clang__)
    #pragma GCC diagnostic pop
    #endif

    return local_result_is_ok;
  }

  template<typename UnknownIntegerType>
  WIDE_INTEGER_CONSTEXPR auto test_uintwide_t_spot_values_from_pull_request_130() -> bool
  {
    // See also https://github.com/ckormanyos/wide-integer/pull/130

    using local_unknown_integer_type = UnknownIntegerType;

    using limits = std::numeric_limits<local_unknown_integer_type>;

    WIDE_INTEGER_CONSTEXPR auto expected
    {
      -1 - limits::max()
    };

    WIDE_INTEGER_CONSTEXPR auto actual
    {
      limits::lowest()
    };

    WIDE_INTEGER_CONSTEXPR bool b_ok = (expected == actual);

    return b_ok;
  }
} // namespace local

auto math::wide_integer::test_uintwide_t_spot_values() -> bool // NOLINT(readability-function-cognitive-complexity)
{
  bool result_is_ok = true;

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/181

    using local_uint128_type = math::wide_integer::uintwide_t<128U, std::uint32_t, void, false>;
    using local_int128_type  = math::wide_integer::uintwide_t<128U, std::uint32_t, void, true>;
    using local_uint160_type = math::wide_integer::uintwide_t<160U, std::uint32_t, void, false>;
    using local_int160_type  = math::wide_integer::uintwide_t<160U, std::uint32_t, void, true>;

    // Get randoms via:
    // RandomInteger[{100000000000000000000000000000000000, 10000000000000000000000000000000000000}]

    WIDE_INTEGER_CONSTEXPR local_uint128_type u128_0("3076659267683009403742876678609501102");
    WIDE_INTEGER_CONSTEXPR local_uint128_type u128_1("9784355713321885697254484081284759103");
    WIDE_INTEGER_CONSTEXPR local_uint128_type u128_2("1759644461251476961796845209840363274");

    WIDE_INTEGER_CONSTEXPR local_uint160_type u160_0 = local_uint160_type(u128_0);
    WIDE_INTEGER_CONSTEXPR local_uint160_type u160_1 = local_uint160_type(u128_1);
    WIDE_INTEGER_CONSTEXPR local_uint160_type u160_2 = local_uint160_type(u128_2);

    WIDE_INTEGER_CONSTEXPR local_uint128_type v128_0 = local_uint128_type(u160_0);
    WIDE_INTEGER_CONSTEXPR local_uint128_type v128_1 = local_uint128_type(u160_1);
    WIDE_INTEGER_CONSTEXPR local_uint128_type v128_2 = local_uint128_type(u160_2);

    result_is_ok &= (u128_0 == v128_0);
    result_is_ok &= (u128_1 == v128_1);
    result_is_ok &= (u128_2 == v128_2);

    #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
    static_assert(u128_0 == v128_0, "Error: Static check of inter-width casting (unsigned) is not OK");
    static_assert(u128_1 == v128_1, "Error: Static check of inter-width casting (unsigned) is not OK");
    static_assert(u128_2 == v128_2, "Error: Static check of inter-width casting (unsigned) is not OK");
    #endif

    WIDE_INTEGER_CONSTEXPR local_int128_type n128_0("-3076659267683009403742876678609501102");
    WIDE_INTEGER_CONSTEXPR local_int128_type n128_1("-9784355713321885697254484081284759103");
    WIDE_INTEGER_CONSTEXPR local_int128_type n128_2("-1759644461251476961796845209840363274");

    WIDE_INTEGER_CONSTEXPR local_int160_type n160_0 = local_int160_type(n128_0);
    WIDE_INTEGER_CONSTEXPR local_int160_type n160_1 = local_int160_type(n128_1);
    WIDE_INTEGER_CONSTEXPR local_int160_type n160_2 = local_int160_type(n128_2);

    WIDE_INTEGER_CONSTEXPR local_int128_type m128_0 = static_cast<local_int128_type>(n160_0);
    WIDE_INTEGER_CONSTEXPR local_int128_type m128_1 = static_cast<local_int128_type>(n160_1);
    WIDE_INTEGER_CONSTEXPR local_int128_type m128_2 = static_cast<local_int128_type>(n160_2);

    result_is_ok &= (n128_0 == m128_0);
    result_is_ok &= (n128_1 == m128_1);
    result_is_ok &= (n128_2 == m128_2);

    #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
    static_assert(u128_0 == v128_0, "Error: Static check of inter-width casting (signed) is not OK");
    static_assert(u128_1 == v128_1, "Error: Static check of inter-width casting (signed) is not OK");
    static_assert(u128_2 == v128_2, "Error: Static check of inter-width casting (signed) is not OK");
    #endif

    WIDE_INTEGER_CONSTEXPR local_uint160_type un160_0 = local_uint160_type(-n128_0);
    WIDE_INTEGER_CONSTEXPR local_uint160_type un160_1 = local_uint160_type(-n128_1);
    WIDE_INTEGER_CONSTEXPR local_uint160_type un160_2 = local_uint160_type(-n128_2);

    result_is_ok &= (un160_0 == u160_0);
    result_is_ok &= (un160_1 == u160_1);
    result_is_ok &= (un160_2 == u160_2);

    #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
    static_assert(un160_0 == u160_0, "Error: Static check of inter-width casting (mixed signes) is not OK");
    static_assert(un160_1 == u160_1, "Error: Static check of inter-width casting (mixed signes) is not OK");
    static_assert(un160_2 == u160_2, "Error: Static check of inter-width casting (mixed signes) is not OK");
    #endif

    WIDE_INTEGER_CONSTEXPR local_int128_type s128_0 = local_int128_type(un160_0);
    WIDE_INTEGER_CONSTEXPR local_int128_type s128_1 = local_int128_type(un160_1);
    WIDE_INTEGER_CONSTEXPR local_int128_type s128_2 = local_int128_type(un160_2);

    result_is_ok &= (local_uint128_type(s128_0) == u128_0);
    result_is_ok &= (local_uint128_type(s128_1) == u128_1);
    result_is_ok &= (local_uint128_type(s128_2) == u128_2);

    #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
    static_assert(static_cast<local_uint128_type>(s128_0) == u128_0, "Error: Static check of inter-width casting (mixed signes) is not OK");
    static_assert(static_cast<local_uint128_type>(s128_1) == u128_1, "Error: Static check of inter-width casting (mixed signes) is not OK");
    static_assert(static_cast<local_uint128_type>(s128_2) == u128_2, "Error: Static check of inter-width casting (mixed signes) is not OK");
    #endif
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/90

    using math::wide_integer::uint128_t;
    using math::wide_integer::int128_t;

    // Get randoms via:
    // RandomInteger[{100000000000000000000000000000000000, 10000000000000000000000000000000000000}]

    {
      WIDE_INTEGER_CONSTEXPR uint128_t u_sep("6'216'049'444'209'020'458'323'688'259'792'241'931");
      WIDE_INTEGER_CONSTEXPR uint128_t u    ("6216049444209020458323688259792241931");

      WIDE_INTEGER_CONSTEXPR uint128_t n_sep("-3000'424'814'887'742'920'043'278'044'817'737'744");
      WIDE_INTEGER_CONSTEXPR uint128_t n    ("-3000424814887742920043278044817737744");

      // BaseForm[6216049444209020458323688259792241931, 16]
      // 4ad2ae64368b98a810635e9cd49850b_16
      WIDE_INTEGER_CONSTEXPR uint128_t h_sep("0x4'AD'2A'E6'43'68'B9'8A'81'06'35'E9'CD'49'85'0B");

      result_is_ok &= (u_sep == u);
      result_is_ok &= (n_sep == n);
      result_is_ok &= (h_sep == u);

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(u_sep == u, "Error: Static check of construction via string with digit separators fails");
      static_assert(n_sep == n, "Error: Static check of construction via string with digit separators fails");
      static_assert(h_sep == u, "Error: Static check of construction via string with digit separators fails");
      #endif
    }
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/145#issuecomment-1006374713

    using math::wide_integer::uint128_t;
    using math::wide_integer::int128_t;

    // Get randoms via:
    // RandomInteger[{100000000000000000000000000000000000, 10000000000000000000000000000000000000}]

    WIDE_INTEGER_CONSTEXPR uint128_t u0("3076659267683009403742876678609501102");
    WIDE_INTEGER_CONSTEXPR uint128_t u1("9784355713321885697254484081284759103");
    WIDE_INTEGER_CONSTEXPR uint128_t u2("1759644461251476961796845209840363274");

    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(u0);
    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(u1);
    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(u2);

    WIDE_INTEGER_CONSTEXPR int128_t n0("-3076659267683009403742876678609501102");
    WIDE_INTEGER_CONSTEXPR int128_t n1("-9784355713321885697254484081284759103");
    WIDE_INTEGER_CONSTEXPR int128_t n2("-1759644461251476961796845209840363274");

    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(n0);
    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(n1);
    result_is_ok &= local::test_uintwide_t_spot_values_from_issue_145(n2);
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/154

    {
      using local_uint64_type    = math::wide_integer::uint64_t;
      using local_uint128_type   = math::wide_integer::uint128_t;
      using local_uint512_type   = math::wide_integer::uint512_t;
      using local_uint1024_type  = math::wide_integer::uint1024_t;
      using local_uint2048_type  = math::wide_integer::uint2048_t;
      using local_uint4096_type  = math::wide_integer::uint4096_t;
      using local_uint8192_type  = math::wide_integer::uint8192_t;
      using local_uint16384_type = math::wide_integer::uint16384_t;
      using local_uint32768_type = math::wide_integer::uint32768_t;
      using local_uint65536_type = math::wide_integer::uint65536_t;

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert((std::numeric_limits<local_uint64_type   >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint128_type  >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint512_type  >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint1024_type >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint2048_type >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint4096_type >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint8192_type >::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint16384_type>::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint32768_type>::max)() != 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint65536_type>::max)() != 0U, "Error: Static check of convenience type fails");

      static_assert((std::numeric_limits<local_uint64_type   >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint128_type  >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint512_type  >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint1024_type >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint2048_type >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint4096_type >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint8192_type >::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint16384_type>::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint32768_type>::min)() == 0U, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_uint65536_type>::min)() == 0U, "Error: Static check of convenience type fails");
      #else
      assert((std::numeric_limits<local_uint64_type   >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint128_type  >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint512_type  >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint1024_type >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint2048_type >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint4096_type >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint8192_type >::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint16384_type>::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint32768_type>::max)() != 0U); // NOLINT
      assert((std::numeric_limits<local_uint65536_type>::max)() != 0U); // NOLINT

      assert((std::numeric_limits<local_uint64_type   >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint128_type  >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint512_type  >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint1024_type >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint2048_type >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint4096_type >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint8192_type >::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint16384_type>::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint32768_type>::min)() == 0U); // NOLINT
      assert((std::numeric_limits<local_uint65536_type>::min)() == 0U); // NOLINT
      #endif
    }

    {
      using local_int64_type    = math::wide_integer::int64_t;
      using local_int128_type   = math::wide_integer::int128_t;
      using local_int512_type   = math::wide_integer::int512_t;
      using local_int1024_type  = math::wide_integer::int1024_t;
      using local_int2048_type  = math::wide_integer::int2048_t;
      using local_int4096_type  = math::wide_integer::int4096_t;
      using local_int8192_type  = math::wide_integer::int8192_t;
      using local_int16384_type = math::wide_integer::int16384_t;
      using local_int32768_type = math::wide_integer::int32768_t;
      using local_int65536_type = math::wide_integer::int65536_t;

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert((std::numeric_limits<local_int64_type   >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int128_type  >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int512_type  >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int1024_type >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int2048_type >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int4096_type >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int8192_type >::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int16384_type>::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int32768_type>::max)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int65536_type>::max)() != 0, "Error: Static check of convenience type fails");

      static_assert((std::numeric_limits<local_int64_type   >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int128_type  >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int512_type  >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int1024_type >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int2048_type >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int4096_type >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int8192_type >::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int16384_type>::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int32768_type>::min)() != 0, "Error: Static check of convenience type fails");
      static_assert((std::numeric_limits<local_int65536_type>::min)() != 0, "Error: Static check of convenience type fails");
      #else
      assert((std::numeric_limits<local_int64_type   >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int128_type  >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int512_type  >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int1024_type >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int2048_type >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int4096_type >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int8192_type >::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int16384_type>::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int32768_type>::max)() != 0); // NOLINT
      assert((std::numeric_limits<local_int65536_type>::max)() != 0); // NOLINT

      assert((std::numeric_limits<local_int64_type   >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int128_type  >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int512_type  >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int1024_type >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int2048_type >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int4096_type >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int8192_type >::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int16384_type>::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int32768_type>::min)() != 0); // NOLINT
      assert((std::numeric_limits<local_int65536_type>::min)() != 0); // NOLINT
      #endif
    }

    {
      using local_uint131072_type = math::wide_integer::uintwide_t<131072, std::uint32_t, std::allocator<void>, false>;

      local_uint131072_type u(123U);
      local_uint131072_type v( 56U);

      // Multiply 123^256.
      u *= u; u *= u; u *= u; u *= u;
      u *= u; u *= u; u *= u; u *= u;

      // Multiply 56^256.
      v *= v; v *= v; v *= v; v *= v;
      v *= v; v *= v; v *= v; v *= v;

      {
        std::stringstream strm;

        // Divide 123^256 / 56^256 and verify the integral result.
        local_uint131072_type w = u / v;

        strm << w;

        result_is_ok &=
          (strm.str() == "3016988223108505362607102560314821693738482648596342283928988093842474437457679828842200");
      }
    }
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/pull/134

    #if (defined(__clang__) && (__clang_major__ >= 10)) && (defined(__cplusplus) && (__cplusplus > 201703L))
      #if defined(__x86_64__)
      static_assert(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1, "Error: clang constexpr is not properly configured");
      #endif
    #endif
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/pull/130

    // The exact issue motivating this PR turned out to be
    // an incorect report. The tests, however, are useful
    // and these have been integrated into _spot_values().

    {
      using type = math::wide_integer::uintwide_t<64, std::uint32_t, void, true>;

      result_is_ok &= local::test_uintwide_t_spot_values_from_pull_request_130<type>();

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(local::test_uintwide_t_spot_values_from_pull_request_130<type>(), "Error: Check conditions surrounding issue 130");
      #endif
    }

    {
      using type = math::wide_integer::uintwide_t<64, std::uint8_t, void, true>;

      result_is_ok &= local::test_uintwide_t_spot_values_from_pull_request_130<type>();

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(local::test_uintwide_t_spot_values_from_pull_request_130<type>(), "Error: Check conditions surrounding issue 130");
      #endif
    }

    {
      using type = math::wide_integer::uintwide_t<256, std::uint32_t, void, true>;

      result_is_ok &= local::test_uintwide_t_spot_values_from_pull_request_130<type>();

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(local::test_uintwide_t_spot_values_from_pull_request_130<type>(), "Error: Check conditions surrounding issue 130");
      #endif
    }

    {
      using type = std::int32_t;

      result_is_ok &= local::test_uintwide_t_spot_values_from_pull_request_130<type>();

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(local::test_uintwide_t_spot_values_from_pull_request_130<type>(), "Error: Check conditions surrounding issue 130");
      #endif
    }

    {
      using type = std::int64_t;

      result_is_ok &= local::test_uintwide_t_spot_values_from_pull_request_130<type>();

      #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
      static_assert(local::test_uintwide_t_spot_values_from_pull_request_130<type>(), "Error: Check conditions surrounding issue 130");
      #endif
    }
  }

  {
    using math::wide_integer::uint256_t;

    // FromDigits["C9DD3EA24800F584CB28C25CC0E6FF1",16]
    // 16770224695321632575655872732632870897
    const uint256_t a("0xC9DD3EA24800F584CB28C25CC0E6FF1");

    // FromDigits["1E934A2EEA60A2AD14ECCAE7AD82C069",16]
    // 40641612127094559121321599356729737321
    const uint256_t b("0x1E934A2EEA60A2AD14ECCAE7AD82C069");

    const uint256_t lm = lcm(a - 1U, b - 1U);
    const uint256_t gd = gcd(a - 1U, b - 1U);

    // LCM[16770224695321632575655872732632870897 - 1, 40641612127094559121321599356729737321 - 1]
    result_is_ok &= (lm == uint256_t("28398706972978513348490390087175345493497748446743697820448222113648043280"));

    // GCD[16770224695321632575655872732632870897 - 1, 40641612127094559121321599356729737321 - 1]
    result_is_ok &= (gd == 24U);
  }

  {
    // See also https://github.com/ckormanyos/wide-integer/issues/111

    {
      using math::wide_integer::int256_t;

      int256_t a("-578960446186580977117854925043439539266349923328202820197287920"
                 "03956564819968");

      int256_t a_itself = (std::numeric_limits<int256_t>::min)();

      result_is_ok &= (a == (std::numeric_limits<int256_t>::min)());

      int256_t b("1");

      const int256_t a_div_b = a / b;

      result_is_ok &= (a_div_b == a);
      result_is_ok &= (a / a_itself == b);
    }

    {
      using my_int32_t = math::wide_integer::uintwide_t<32U, std::uint32_t, void, true>;

      my_int32_t c("-2147483648");

      my_int32_t c_itself = (std::numeric_limits<my_int32_t>::min)();

      result_is_ok &= (c == (std::numeric_limits<my_int32_t>::min)());

      my_int32_t d("1");

      const my_int32_t c_div_d = c / d;
      result_is_ok &= (c / c_itself == d);

      result_is_ok &= (c_div_d == c);
    }
  }

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

    WIDE_INTEGER_CONSTEXPR bool result_ll_is_ok = (static_cast<long long>(input) == 1729348762983LL); // NOLINT(google-runtime-int)

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_ll_is_ok, "Error: test_uintwide_t_spot_values unsigned not OK!");
    #endif

    result_is_ok &= result_ll_is_ok;
  }

  {
    using math::wide_integer::uint512_t;

    WIDE_INTEGER_CONSTEXPR uint512_t a("698937339790347543053797400564366118744312537138445607919548628175822115805812983955794321304304417541511379093392776018867245622409026835324102460829431");
    WIDE_INTEGER_CONSTEXPR uint512_t b("100041341335406267530943777943625254875702684549707174207105689918734693139781");

    WIDE_INTEGER_CONSTEXPR uint512_t c = (a / b);
    WIDE_INTEGER_CONSTEXPR uint512_t d = (a % b);

    //   QuotientRemainder
    //     [698937339790347543053797400564366118744312537138445607919548628175822115805812983955794321304304417541511379093392776018867245622409026835324102460829431,
    //      100041341335406267530943777943625254875702684549707174207105689918734693139781]
    //
    //     {6986485091668619828842978360442127600954041171641881730123945989288792389271,
    //      100041341335406267530943777943625254875702684549707174207105689918734693139780}

    WIDE_INTEGER_CONSTEXPR bool c_is_ok = (c == "6986485091668619828842978360442127600954041171641881730123945989288792389271");
    WIDE_INTEGER_CONSTEXPR bool d_is_ok = (d == "100041341335406267530943777943625254875702684549707174207105689918734693139780");

    result_is_ok &= (c_is_ok && d_is_ok);

    #if(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1)
    static_assert(c_is_ok, "Error: Static check of spot value division is not OK");
    static_assert(d_is_ok, "Error: Static check of spot value remainder is not OK");
    #endif
  }

  {
    using math::wide_integer::uint256_t;

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

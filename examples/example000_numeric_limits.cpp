///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local
{
  using uint64_t = math::wide_integer::uint64_t;
  using  int64_t = math::wide_integer::int64_t;
  using uint32_t = math::wide_integer::uintwide_t<32U, std::uint8_t, void, false>;
  using  int32_t = math::wide_integer::uintwide_t<32U, std::uint8_t, void, true>;
}

bool math::wide_integer::example000_numeric_limits()
{
  bool result_is_ok = true;

  {
    using uint256_t = math::wide_integer::uint256_t;

    WIDE_INTEGER_CONSTEXPR uint256_t my_max("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    WIDE_INTEGER_CONSTEXPR uint256_t my_min(0U);

    WIDE_INTEGER_CONSTEXPR bool result_uint256_t_is_ok =
         ((std::numeric_limits<uint256_t>::max)  () == my_max)
      && ((std::numeric_limits<uint256_t>::min)  () == my_min)
      && ( std::numeric_limits<uint256_t>::lowest() == uint256_t(std::numeric_limits<unsigned>::lowest()))
      && ( std::numeric_limits<uint256_t>::digits   == 256)
      && ( std::numeric_limits<uint256_t>::digits10 == 77)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_uint256_t_is_ok, "Error: example000_numeric_limits unsigned not OK!");
    #endif

    result_is_ok &= result_uint256_t_is_ok;
  }

  {
    using int256_t = math::wide_integer::int256_t;

    WIDE_INTEGER_CONSTEXPR int256_t my_max   ("0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    WIDE_INTEGER_CONSTEXPR int256_t my_min   ("-57896044618658097711785492504343953926634992332820282019728792003956564819968");
    WIDE_INTEGER_CONSTEXPR int256_t my_lowest("-57896044618658097711785492504343953926634992332820282019728792003956564819968");

    WIDE_INTEGER_CONSTEXPR bool result_int256_t_is_ok =
         ((std::numeric_limits<int256_t>::max)  () == my_max)
      && ((std::numeric_limits<int256_t>::min)  () == my_min)
      && ( std::numeric_limits<int256_t>::lowest() == my_lowest)
      && ( std::numeric_limits<int256_t>::digits   == 255)
      && ( std::numeric_limits<int256_t>::digits10 == 76)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_int256_t_is_ok, "Error: example000_numeric_limits signed not OK!");
    #endif

    result_is_ok &= result_int256_t_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR bool result_uint64_t_is_ok =
         ((std::numeric_limits<local::uint64_t>::max)  () ==       (std::numeric_limits<std::uint64_t>::max)  ())
      && ((std::numeric_limits<local::uint64_t>::min)  () ==       (std::numeric_limits<std::uint64_t>::min)  ())
      && ( std::numeric_limits<local::uint64_t>::lowest() ==        std::numeric_limits<std::uint64_t>::lowest())
      && ( std::numeric_limits<local::uint64_t>::lowest() ==  -1 - (std::numeric_limits<local::uint64_t>::max)())
      && ( std::numeric_limits<local::uint64_t>::digits   ==        std::numeric_limits<std::uint64_t>::digits  )
      && ( std::numeric_limits<local::uint64_t>::digits10 ==        std::numeric_limits<std::uint64_t>::digits10)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_uint64_t_is_ok, "Error: example000_numeric_limits unsigned not OK!");
    #endif

    result_is_ok &= result_uint64_t_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR bool result_int64_t_is_ok =
         ((std::numeric_limits<local::int64_t>::max)  () ==       (std::numeric_limits<std::int64_t>::max)  ())
      && ((std::numeric_limits<local::int64_t>::min)  () ==       (std::numeric_limits<std::int64_t>::min)  ())
      && ( std::numeric_limits<local::int64_t>::lowest() ==        std::numeric_limits<std::int64_t>::lowest())
      && ( std::numeric_limits<local::int64_t>::lowest() ==  -1 - (std::numeric_limits<local::int64_t>::max)())
      && ( std::numeric_limits<local::int64_t>::digits   ==        std::numeric_limits<std::int64_t>::digits  )
      && ( std::numeric_limits<local::int64_t>::digits10 ==        std::numeric_limits<std::int64_t>::digits10)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_int64_t_is_ok, "Error: example000_numeric_limits unsigned not OK!");
    #endif

    result_is_ok &= result_int64_t_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR bool result_uint32_t_is_ok =
         ((std::numeric_limits<local::uint32_t>::max)  () ==       (std::numeric_limits<std::uint32_t>::max)  ())
      && ((std::numeric_limits<local::uint32_t>::min)  () ==       (std::numeric_limits<std::uint32_t>::min)  ())
      && ( std::numeric_limits<local::uint32_t>::lowest() ==        std::numeric_limits<std::uint32_t>::lowest())
      && ( std::numeric_limits<local::uint32_t>::lowest() ==  -1 - (std::numeric_limits<local::uint32_t>::max)())
      && ( std::numeric_limits<local::uint32_t>::digits   ==        std::numeric_limits<std::uint32_t>::digits  )
      && ( std::numeric_limits<local::uint32_t>::digits10 ==        std::numeric_limits<std::uint32_t>::digits10)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_uint32_t_is_ok, "Error: example000_numeric_limits unsigned not OK!");
    #endif

    result_is_ok &= result_uint32_t_is_ok;
  }

  {
    WIDE_INTEGER_CONSTEXPR bool result_int32_t_is_ok =
         ((std::numeric_limits<local::int32_t>::max)  () ==       (std::numeric_limits<std::int32_t>::max)  ())
      && ((std::numeric_limits<local::int32_t>::min)  () ==       (std::numeric_limits<std::int32_t>::min)  ())
      && ( std::numeric_limits<local::int32_t>::lowest() ==        std::numeric_limits<std::int32_t>::lowest())
      && ( std::numeric_limits<local::int32_t>::lowest() ==  -1 - (std::numeric_limits<local::int32_t>::max)())
      && ( std::numeric_limits<local::int32_t>::digits   ==        std::numeric_limits<std::int32_t>::digits  )
      && ( std::numeric_limits<local::int32_t>::digits10 ==        std::numeric_limits<std::int32_t>::digits10)
      ;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_int32_t_is_ok, "Error: example000_numeric_limits unsigned not OK!");
    #endif

    result_is_ok &= result_int32_t_is_ok;
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example000_numeric_limits();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

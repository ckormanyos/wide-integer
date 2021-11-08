///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <ctime>
#include <random>
#include <sstream>
#include <string>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#endif

#include <boost/multiprecision/cpp_int.hpp>

#include <math/wide_integer/uintwide_t.h>
#include <test/test_uintwide_t.h>

namespace
{
  std::mt19937                                                         engine_val;
  std::ranlux24_base                                                   engine_sgn;
  std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> engine_len;

  template<const std::size_t MaxDigitsToGet,
           const std::size_t MinDigitsToGet = 2U>
  void get_random_digit_string(std::string& str)
  {
    static_assert(MinDigitsToGet >=  2U, "Error: The minimum number of digits to get must be  2 or more");

    static std::uniform_int_distribution<unsigned>
    dist_sgn
    (
      0,
      1
    );

    static std::uniform_int_distribution<unsigned>
    dist_len
    (
      MinDigitsToGet,
      MaxDigitsToGet
    );

    static std::uniform_int_distribution<unsigned>
    dist_first
    (
      1,
      9
    );

    static std::uniform_int_distribution<unsigned>
    dist_following
    (
      0,
      9
    );

    const bool is_neg = (dist_sgn(engine_sgn) != 0);

    const std::string::size_type len = static_cast<std::string::size_type>(dist_len(engine_len));

    std::string::size_type pos = 0U;

    if(is_neg)
    {
      str.resize(len + 1U);

      str.at(pos) = char('-');

      ++pos;
    }
    else
    {
      str.resize(len);
    }

    str.at(pos) = static_cast<char>(dist_first(engine_val) + 0x30U);

    ++pos;

    while(pos < str.length())
    {
      str.at(pos) = static_cast<char>(dist_following(engine_val) + 0x30U);

      ++pos;
    }
  }

  template<typename UnsignedIntegralType>
  static std::string hexlexical_cast(const UnsignedIntegralType& u)
  {
    std::stringstream ss;

    ss << std::hex << u;

    return ss.str();
  }
}

bool math::wide_integer::test_uintwide_t_int_convert()
{
  constexpr unsigned digits2 = 256U;

  using boost_sint_backend_type =
    boost::multiprecision::cpp_int_backend<digits2,
                                           digits2,
                                           boost::multiprecision::signed_magnitude>;

  using boost_sint_type = boost::multiprecision::number<boost_sint_backend_type, boost::multiprecision::et_on>;

  #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
  using local_limb_type = std::uint64_t;
  #else
  using local_limb_type = std::uint32_t;
  #endif

  using local_sint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, void, true>;

  engine_val.seed(static_cast<typename std::mt19937::result_type>                                                        (std::clock()));
  engine_sgn.seed(static_cast<typename std::ranlux24_base::result_type>                                                  (std::clock()));
  engine_len.seed(static_cast<typename std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647>::result_type>(std::clock()));

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < 0x100000U; ++i)
  {
    std::string str_digits;

    get_random_digit_string<18U, 2U>(str_digits);

    const boost_sint_type n_boost = boost_sint_type(str_digits.c_str());
    const local_sint_type n_local = local_sint_type(str_digits.c_str());

    const std::int64_t n_ctrl_boost = (std::int64_t) n_boost;
    const std::int64_t n_ctrl_local = (std::int64_t) n_local;

    const bool result_n_is_ok = (n_ctrl_boost == n_ctrl_local);

    result_is_ok &= result_n_is_ok;
  }

  return result_is_ok;
}

#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic pop
#endif

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif

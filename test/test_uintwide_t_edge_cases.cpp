///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

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

#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/uintwide_t_backend.hpp>

#include <math/wide_integer/uintwide_t.h>
#include <test/test_uintwide_t.h>

namespace
{
  constexpr std::size_t local_digits2 = 16384U;
}

using local_uint_type =
  boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<local_digits2>,
                                boost::multiprecision::et_off>;

using boost_uint_backend_type =
  boost::multiprecision::cpp_int_backend<local_digits2,
                                         local_digits2,
                                         boost::multiprecision::unsigned_magnitude>;

using boost_uint_type =
  boost::multiprecision::number<boost_uint_backend_type,
                                boost::multiprecision::et_off>;

bool math::wide_integer::test_uintwide_t_edge_cases()
{
  const local_uint_type u_max_local = (std::numeric_limits<local_uint_type>::max)();
  const boost_uint_type u_max_boost = (std::numeric_limits<boost_uint_type>::max)();

  local_uint_type result_local;
  boost_uint_type result_boost;

  result_local = u_max_local * u_max_local;
  result_boost = u_max_boost * u_max_boost;

  const bool result01_is_ok = ((result_local == 1U) && (result_boost == 1U));

  result_local = (u_max_local - 1U) * u_max_local;
  result_boost = (u_max_boost - 1U) * u_max_boost;

  const bool result02_is_ok = ((result_local == 2U) && (result_boost == 2U));

  const std::string str_seven_and_effs =
    "0x7" + std::string(std::string::size_type((local_digits2 / 4) - 1U), char('F'));

  const local_uint_type u_seven_and_effs_local(str_seven_and_effs.c_str());
  const boost_uint_type u_seven_and_effs_boost(str_seven_and_effs.c_str());

  result_local = u_seven_and_effs_local * u_seven_and_effs_local;
  result_boost = u_seven_and_effs_boost * u_seven_and_effs_boost;

  const bool result03_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const std::string str_three_quarter_effs_and_zeros =
      "0x"
    + std::string(std::string::size_type((local_digits2 / 4) * 3U), char('F'))
    + std::string(std::string::size_type((local_digits2 / 4) * 1U), char('0'))
    ;

  const local_uint_type u_three_quarter_effs_and_zeros_local(str_three_quarter_effs_and_zeros.c_str());
  const boost_uint_type u_three_quarter_effs_and_zeros_boost(str_three_quarter_effs_and_zeros.c_str());

  result_local = u_three_quarter_effs_and_zeros_local * u_three_quarter_effs_and_zeros_local;
  result_boost = u_three_quarter_effs_and_zeros_boost * u_three_quarter_effs_and_zeros_boost;

  const bool result04_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const std::string str_one_quarter_effs_and_zeros =
      "0x"
    + std::string(std::string::size_type((local_digits2 / 4) * 1U), char('F'))
    + std::string(std::string::size_type((local_digits2 / 4) * 3U), char('0'))
    ;

  const local_uint_type u_one_quarter_effs_and_zeros_local(str_one_quarter_effs_and_zeros.c_str());
  const boost_uint_type u_one_quarter_effs_and_zeros_boost(str_one_quarter_effs_and_zeros.c_str());

  result_local = u_one_quarter_effs_and_zeros_local * u_one_quarter_effs_and_zeros_local;
  result_boost = u_one_quarter_effs_and_zeros_boost * u_one_quarter_effs_and_zeros_boost;

  const bool result05_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const local_uint_type one_limb_effs_prior_to_half_and_zeros_local(local_uint_type(UINT32_C(0xFFFFFFFF)) << ((std::numeric_limits<local_uint_type>::digits / 2) - 32));
  const boost_uint_type one_limb_effs_prior_to_half_and_zeros_boost(boost_uint_type(UINT32_C(0xFFFFFFFF)) << ((std::numeric_limits<boost_uint_type>::digits / 2) - 32));

  result_local = one_limb_effs_prior_to_half_and_zeros_local * one_limb_effs_prior_to_half_and_zeros_local;
  result_boost = one_limb_effs_prior_to_half_and_zeros_boost * one_limb_effs_prior_to_half_and_zeros_boost;

  const bool result06_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const local_uint_type u_mid_local = u_three_quarter_effs_and_zeros_local / typename local_uint_type::backend_type::representation_type::limb_type(2U);
  const boost_uint_type u_mid_boost = u_three_quarter_effs_and_zeros_boost / typename std::iterator_traits<boost_uint_type::backend_type::limb_pointer>::value_type(2U);

  constexpr int signed_shift_amount =
    -(std::numeric_limits<typename local_uint_type::backend_type::representation_type::limb_type>::digits + 7);

  result_local = u_mid_local;
  result_local.backend().representation() >>= signed_shift_amount;
  result_boost = u_mid_boost * (boost_uint_type(1U) << (-signed_shift_amount));

  const bool result07_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  result_local = u_mid_local;
  result_local.backend().representation() <<= signed_shift_amount;
  result_boost = u_mid_boost / (boost_uint_type(1U) << (-signed_shift_amount));

  const bool result08_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const bool result_is_ok = (   result01_is_ok
                             && result02_is_ok
                             && result03_is_ok
                             && result04_is_ok
                             && result05_is_ok
                             && result06_is_ok
                             && result07_is_ok
                             && result08_is_ok);

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

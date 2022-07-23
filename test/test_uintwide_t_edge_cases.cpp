///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <random>
#include <string>

#include <boost/version.hpp>

#if !defined(BOOST_VERSION)
#error BOOST_VERSION is not defined. Ensure that <boost/version.hpp> is properly included.
#endif

#if ((BOOST_VERSION >= 107900) && !defined(BOOST_MP_STANDALONE))
#define BOOST_MP_STANDALONE
#endif

#if (BOOST_VERSION < 108000)
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#endif

#if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ >= 12))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wrestrict"
#endif

#if (BOOST_VERSION < 108000)
#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#endif
#endif

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/uintwide_t_backend.hpp>

#include <math/wide_integer/uintwide_t.h>
#include <test/test_uintwide_t.h>

namespace test_uintwide_t_edge {

namespace local_edge_cases {

  constexpr auto local_digits2       = static_cast<std::size_t>(UINT32_C(16384));
  constexpr auto local_digits2_small = static_cast<std::size_t>(UINT32_C(  256));

} // namespace local_edge_cases

using local_uintwide_t_small_unsigned_type =
  #if defined(WIDE_INTEGER_NAMESPACE)
  WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<local_edge_cases::local_digits2_small, std::uint16_t, void, false>;
  #else
  ::math::wide_integer::uintwide_t<local_edge_cases::local_digits2_small, std::uint16_t, void, false>;
  #endif

using local_uintwide_t_small_signed_type =
  #if defined(WIDE_INTEGER_NAMESPACE)
  WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<local_edge_cases::local_digits2_small, std::uint16_t, void, true>;
  #else
  ::math::wide_integer::uintwide_t<local_edge_cases::local_digits2_small, std::uint16_t, void, true>;
  #endif

std::uniform_int_distribution<std::uint32_t> dist_sgn    (UINT32_C(0), UINT32_C(1));  // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_dig_dec(UINT32_C(1), UINT32_C(9));  // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_dig_hex(UINT32_C(1), UINT32_C(15)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_dig_oct(UINT32_C(1), UINT32_C(7));  // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

using eng_sgn_type = std::ranlux24;
using eng_dig_type = std::minstd_rand0;

eng_sgn_type eng_sgn; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
eng_dig_type eng_dig; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

enum class local_base
{
  dec,
  hex,
  oct
};

template<typename IntegralTypeWithStringConstruction>
auto generate_wide_integer_value(bool       is_positive           = true,
                                 local_base base_to_get           = local_base::dec,
                                 int        digits_in_base_to_get = std::numeric_limits<IntegralTypeWithStringConstruction>::digits10) -> IntegralTypeWithStringConstruction
{
  using local_integral_type = IntegralTypeWithStringConstruction;

  static_assert(   (  std::numeric_limits<local_integral_type>::is_signed  && std::numeric_limits<local_integral_type>::digits > static_cast<int>(INT8_C(63)))
                || ((!std::numeric_limits<local_integral_type>::is_signed) && std::numeric_limits<local_integral_type>::digits > static_cast<int>(INT8_C(64))),
                "Error: Integral type destination does not have enough digits10");

  std::string str_x(static_cast<std::size_t>(digits_in_base_to_get), '0');

  std::generate(str_x.begin(),
                str_x.end(),
                [&base_to_get]() // NOLINT(modernize-use-trailing-return-type,-warnings-as-errors)
                {
                  char c { };

                  if(base_to_get == local_base::oct)
                  {
                    c = static_cast<char>(dist_dig_oct(eng_dig));
                    c = static_cast<char>(c + static_cast<char>(INT8_C(0x30)));
                  }
                  else if(base_to_get == local_base::hex)
                  {
                    c = static_cast<char>(dist_dig_hex(eng_dig));

                    if(c < static_cast<char>(INT8_C(0xA)))
                    {
                      c = static_cast<char>(c + static_cast<char>(INT8_C(0x30)));
                    }
                    else
                    {
                      c = static_cast<char>(c + static_cast<char>(INT8_C(0x41)));
                    }
                  }
                  else
                  {
                    c = static_cast<char>(dist_dig_dec(eng_dig));
                    c = static_cast<char>(c + static_cast<char>(INT8_C(0x30)));
                  }

                  return c;
                });

  if(base_to_get == local_base::oct)
  {
    str_x.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '0');
  }
  else if(base_to_get == local_base::hex)
  {
    str_x.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), 'x');
    str_x.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '0');
  }

  // Insert either a positive sign or a negative sign
  // (always one or the other) depending on the sign of x.
  const auto sign_char_to_insert =
    static_cast<char>
    (
      is_positive
        ? '+'
        : static_cast<char>((dist_sgn(eng_sgn) != static_cast<std::uint32_t>(UINT32_C(0))) ? '+' : '-')
    );

  str_x.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), sign_char_to_insert);

  return local_integral_type(str_x.c_str());
}

using local_uint_backend_type =
  boost::multiprecision::uintwide_t_backend<local_edge_cases::local_digits2,
                                            std::uint32_t,
                                            std::allocator<std::uint32_t>>;

using boost_uint_backend_allocator_type = void;

using boost_uint_backend_type =
  boost::multiprecision::cpp_int_backend<local_edge_cases::local_digits2,
                                         local_edge_cases::local_digits2,
                                         boost::multiprecision::unsigned_magnitude,
                                         boost::multiprecision::unchecked,
                                         boost_uint_backend_allocator_type>;

using local_uint_type =
  boost::multiprecision::number<local_uint_backend_type,
                                boost::multiprecision::et_off>;

using boost_uint_type =
  boost::multiprecision::number<boost_uint_backend_type,
                                boost::multiprecision::et_off>;

auto test_various_edge_operations() -> bool
{
  const auto u_max_local = (std::numeric_limits<local_uint_type>::max)();
  const auto u_max_boost = (std::numeric_limits<boost_uint_type>::max)();

  local_uint_type result_local;
  boost_uint_type result_boost;

  result_local = u_max_local * u_max_local;
  result_boost = u_max_boost * u_max_boost;

  const auto result01_is_ok = ((result_local == 1U) && (result_boost == 1U));

  result_local = (u_max_local - 1U) * u_max_local;
  result_boost = (u_max_boost - 1U) * u_max_boost;

  const auto result02_is_ok = ((result_local == 2U) && (result_boost == 2U));

  const std::string str_seven_and_effs =
    "0x7" + std::string(std::string::size_type((local_edge_cases::local_digits2 / 4) - 1U), 'F');

  const local_uint_type u_seven_and_effs_local(str_seven_and_effs.c_str());
  const boost_uint_type u_seven_and_effs_boost(str_seven_and_effs.c_str());

  result_local = u_seven_and_effs_local * u_seven_and_effs_local;
  result_boost = u_seven_and_effs_boost * u_seven_and_effs_boost;

  const auto result03_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const std::string str_three_quarter_effs_and_zeros =
      "0x"
    + std::string(std::string::size_type((local_edge_cases::local_digits2 / 4) * 3U), 'F')
    + std::string(std::string::size_type((local_edge_cases::local_digits2 / 4) * 1U), '0')
    ;

  const local_uint_type u_three_quarter_effs_and_zeros_local(str_three_quarter_effs_and_zeros.c_str());
  const boost_uint_type u_three_quarter_effs_and_zeros_boost(str_three_quarter_effs_and_zeros.c_str());

  result_local = u_three_quarter_effs_and_zeros_local * u_three_quarter_effs_and_zeros_local;
  result_boost = u_three_quarter_effs_and_zeros_boost * u_three_quarter_effs_and_zeros_boost;

  const auto result04_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const std::string str_one_quarter_effs_and_zeros =
      "0x"
    + std::string(std::string::size_type((local_edge_cases::local_digits2 / 4) * 1U), 'F')
    + std::string(std::string::size_type((local_edge_cases::local_digits2 / 4) * 3U), '0')
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

  const auto result06_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const local_uint_type u_mid_local = u_three_quarter_effs_and_zeros_local / typename local_uint_type::backend_type::representation_type::limb_type(2U);
  const boost_uint_type u_mid_boost = u_three_quarter_effs_and_zeros_boost / typename std::iterator_traits<boost_uint_type::backend_type::limb_pointer>::value_type(2U);

  constexpr auto signed_shift_amount =
    static_cast<int>
    (
      -(std::numeric_limits<typename local_uint_type::backend_type::representation_type::limb_type>::digits + 7)
    );

  result_local = u_mid_local;
  result_local.backend().representation() >>= signed_shift_amount;
  result_boost = u_mid_boost * (boost_uint_type(1U) << (-signed_shift_amount));

  const auto result07_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  result_local = u_mid_local;
  result_local.backend().representation() <<= signed_shift_amount;
  result_boost = u_mid_boost / (boost_uint_type(1U) << (-signed_shift_amount));

  const auto result08_is_ok = (result_local.convert_to<std::string>() == result_boost.convert_to<std::string>());

  const auto result_is_ok = (   result01_is_ok
                             && result02_is_ok
                             && result03_is_ok
                             && result04_is_ok
                             && result05_is_ok
                             && result06_is_ok
                             && result07_is_ok
                             && result08_is_ok);

  return result_is_ok;
}

auto test_various_ostream_ops() -> bool
{
  auto result_is_ok = true;

  eng_sgn.seed(static_cast<typename eng_sgn_type::result_type>(std::random_device{ }()));
  eng_dig.seed(static_cast<typename eng_dig_type::result_type>(std::random_device{ }()));

  {
    const auto u = local_uintwide_t_small_unsigned_type(static_cast<std::uint32_t>(UINT32_C(29363)));

    std::stringstream strm;

    strm << std::dec << std::showbase << std::setw(static_cast<std::streamsize>(INT8_C(100))) << std::setfill('#') << u;

    std::string str_ctrl(static_cast<std::size_t>(UINT8_C(100)), '#');

    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(4)))) = '2';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(3)))) = '9';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(2)))) = '3';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(1)))) = '6';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(0)))) = '3';

    const auto result_u_fill_is_ok = (strm.str() == str_ctrl);

    result_is_ok = (result_u_fill_is_ok && result_is_ok);
  }

  {
    const auto u = local_uintwide_t_small_unsigned_type(static_cast<std::uint32_t>(UINT32_C(41719)));

    std::stringstream strm;

    strm << std::hex << std::uppercase << std::showbase << std::setw(static_cast<std::streamsize>(INT8_C(100))) << std::setfill('#') << u;

    std::string str_ctrl(static_cast<std::size_t>(UINT8_C(100)), '#');

    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(5)))) = '0';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(4)))) = 'X';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(3)))) = 'A';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(2)))) = '2';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(1)))) = 'F';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(0)))) = '7';

    const auto result_u_fill_is_ok = (strm.str() == str_ctrl);

    result_is_ok = (result_u_fill_is_ok && result_is_ok);
  }

  {
    const auto u = local_uintwide_t_small_unsigned_type(static_cast<std::uint32_t>(UINT32_C(29363)));

    std::stringstream strm;

    strm << std::oct << std::uppercase << std::showbase << std::setw(static_cast<std::streamsize>(INT8_C(100))) << std::setfill('#') << u;

    std::string str_ctrl(static_cast<std::size_t>(UINT8_C(100)), '#');

    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(5)))) = '0';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(4)))) = '7';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(3)))) = '1';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(2)))) = '2';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(1)))) = '6';
    str_ctrl.at(static_cast<std::size_t>(static_cast<std::size_t>(str_ctrl.size() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::size_t>(UINT8_C(0)))) = '3';

    const auto result_u_fill_is_ok = (strm.str() == str_ctrl);

    result_is_ok = (result_u_fill_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    const auto u =
      generate_wide_integer_value<local_uintwide_t_small_unsigned_type>
      (
        true,
        local_base::dec,
        std::numeric_limits<local_uintwide_t_small_unsigned_type>::digits10
      );

    std::stringstream strm;

    strm << std::dec << u;

    const local_uintwide_t_small_unsigned_type u_strm(strm.str().c_str());

    const auto result_u_is_ok = (u == u_strm);

    result_is_ok = (result_u_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    const auto u =
      generate_wide_integer_value<local_uintwide_t_small_unsigned_type>
      (
        true,
        local_base::hex,
        std::numeric_limits<local_uintwide_t_small_unsigned_type>::digits / 4
      );

    std::stringstream strm;

    strm << std::hex << std::showbase << u;

    const local_uintwide_t_small_unsigned_type u_strm(strm.str().c_str());

    const auto result_u_is_ok = (u == u_strm);

    result_is_ok = (result_u_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    const auto u =
      generate_wide_integer_value<local_uintwide_t_small_unsigned_type>
      (
        true,
        local_base::oct,
        std::numeric_limits<local_uintwide_t_small_unsigned_type>::digits / 3
      );

    std::stringstream strm;

    strm << std::oct << std::showbase << u;

    const local_uintwide_t_small_unsigned_type u_strm(strm.str().c_str());

    const auto result_u_is_ok = (u == u_strm);

    result_is_ok = (result_u_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    const auto n =
      generate_wide_integer_value<local_uintwide_t_small_signed_type>
      (
        false,
        local_base::hex,
        (std::numeric_limits<local_uintwide_t_small_signed_type>::digits + 1) / 4
      );

    std::stringstream strm;

    strm << std::hex << std::showbase << n;

    const local_uintwide_t_small_signed_type n_strm(strm.str().c_str());

    const auto result_n_is_ok = (n == n_strm);

    result_is_ok = (result_n_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    const auto n =
      generate_wide_integer_value<local_uintwide_t_small_signed_type>
      (
        false,
        local_base::oct,
        (std::numeric_limits<local_uintwide_t_small_signed_type>::digits + 1) / 3
      );

    std::stringstream strm;

    strm << std::oct << std::showbase << n;

    const local_uintwide_t_small_signed_type n_strm(strm.str().c_str());

    const auto result_n_is_ok = (n == n_strm);

    result_is_ok = (result_n_is_ok && result_is_ok);
  }

  return result_is_ok;
}

auto test_various_roots() -> bool
{
  auto result_is_ok = true;

  {
    const auto u      = local_uintwide_t_small_unsigned_type("1000000000000000000000000000000");
    const auto u_root = rootk(u, static_cast<std::uint_fast8_t>(UINT8_C(1)));

    const bool result_u_root_is_ok = u_root == local_uintwide_t_small_unsigned_type("1000000000000000000000000000000");

    result_is_ok = (result_u_root_is_ok && result_is_ok);
  }

  {
    const auto u      = local_uintwide_t_small_unsigned_type("1000000000000000000000000000000");
    const auto u_root = rootk(u, static_cast<std::uint_fast8_t>(UINT8_C(2)));

    const bool result_u_root_is_ok = u_root == local_uintwide_t_small_unsigned_type("1000000000000000");

    result_is_ok = (result_u_root_is_ok && result_is_ok);
  }

  return result_is_ok;
}

} // namespace test_uintwide_t_edge

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::test_uintwide_t_edge_cases() -> bool
#else
auto math::wide_integer::test_uintwide_t_edge_cases() -> bool
#endif
{
  bool result_is_ok = true;

  result_is_ok = (test_uintwide_t_edge::test_various_edge_operations() && result_is_ok);
  result_is_ok = (test_uintwide_t_edge::test_various_ostream_ops    () && result_is_ok);
  result_is_ok = (test_uintwide_t_edge::test_various_roots          () && result_is_ok);

  return result_is_ok;

}

#if (BOOST_VERSION < 108000)
#if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
#pragma GCC diagnostic pop
#endif
#endif

#if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ >= 12))
#pragma GCC diagnostic pop
#endif

#if (BOOST_VERSION < 108000)
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif
#endif

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
#endif

#include <boost/multiprecision/cpp_int.hpp>

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_test.h>

namespace
{
  std::mt19937                                                         engine_man;
  std::ranlux24_base                                                   engine_sgn;
  std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> engine_e10;

  template<typename FloatingPointType,
           const std::int32_t LoExp10,
           const std::int32_t HiExp10>
  FloatingPointType get_random_float()
  {
    using local_builtin_float_type = FloatingPointType;

    static std::uniform_real_distribution<local_builtin_float_type>
    dist_man
    (
      local_builtin_float_type(0.0F),
      local_builtin_float_type(1.0F)
    );

    static std::uniform_int_distribution<unsigned>
    dist_sgn
    (
      0,
      1
    );

    static std::uniform_int_distribution<std::int32_t>
    dist_e10
    (
      LoExp10,
      HiExp10
    );

    using std::pow;

    const std::int32_t             p10 = dist_e10(engine_e10);
    const local_builtin_float_type e10 = pow(local_builtin_float_type(10.0F),
                                             local_builtin_float_type(p10));

    const local_builtin_float_type a = dist_man(engine_man) * e10;

    const bool is_neg = (dist_sgn(engine_sgn) != 0);

    const local_builtin_float_type f = ((is_neg == false) ? a : -a);

    return f;
  }

  template<typename UnsignedIntegralType>
  static std::string hexlexical_cast(const UnsignedIntegralType& u)
  {
    std::stringstream ss;

    ss << std::hex << u;

    return ss.str();
  }
}

bool math::wide_integer::test_uintwide_t_float_convert()
{
  constexpr unsigned digits2 = 256U;

  using boost_uint_backend_type =
    boost::multiprecision::cpp_int_backend<digits2,
                                           digits2,
                                           boost::multiprecision::unsigned_magnitude>;
  using boost_sint_backend_type =
    boost::multiprecision::cpp_int_backend<digits2,
                                           digits2,
                                           boost::multiprecision::signed_magnitude>;

  using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type, boost::multiprecision::et_on>;
  using boost_sint_type = boost::multiprecision::number<boost_sint_backend_type, boost::multiprecision::et_on>;

  using local_limb_type = std::uint32_t;

  using local_uint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, void>;
  using local_sint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, void, true>;

  engine_man.seed(static_cast<typename std::mt19937::result_type>                                                        (std::clock()));
  engine_sgn.seed(static_cast<typename std::ranlux24_base::result_type>                                                  (std::clock()));
  engine_e10.seed(static_cast<typename std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647>::result_type>(std::clock()));

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < 0x10000U; ++i)
  {
    const float f = get_random_float<float, -1, 27>();

    boost_sint_type n_boost = boost_sint_type(f);
    local_sint_type n_local = local_sint_type(f);

    const std::string str_boost_signed = hexlexical_cast((boost_uint_type) n_boost);
    const std::string str_local_signed = hexlexical_cast((local_uint_type) n_local);

    result_is_ok &= (str_boost_signed == str_local_signed);
  }

  for(std::size_t i = 0U; i < 0x10000U; ++i)
  {
    const double d = get_random_float<double, -1, 75>();

    boost_sint_type n_boost = boost_sint_type(d);
    local_sint_type n_local = local_sint_type(d);

    const std::string str_boost_signed = hexlexical_cast((boost_uint_type) n_boost);
    const std::string str_local_signed = hexlexical_cast((local_uint_type) n_local);

    result_is_ok &= (str_boost_signed == str_local_signed);
  }

  return result_is_ok;
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

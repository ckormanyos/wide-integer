///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/uintwide_t_backend.hpp>

typedef boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<1024U>,
                                      boost::multiprecision::et_off>
local_uint_type;

using boost_uint_backend_type =
  boost::multiprecision::cpp_int_backend<1024,
                                         1024,
                                         boost::multiprecision::unsigned_magnitude>;

using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type,
                                                      boost::multiprecision::et_off>;

bool test_uintwide_t_boost_backend()
{
  local_uint_type u = 1U;

  for(std::size_t i = 2U; i <= 100U; ++i)
  {
    u *= i;
  }

  const local_uint_type local_control("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
  const boost_uint_type boost_control("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");

  const bool local_control_is_ok = (u == local_control);
  const bool boost_control_is_ok = (boost::lexical_cast<std::string>(u) == boost::lexical_cast<std::string>(boost_control));

  const bool result_is_ok = (local_control_is_ok && boost_control_is_ok);

  return result_is_ok;
}

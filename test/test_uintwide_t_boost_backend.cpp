#include <iomanip>
#include <iostream>

#include <boost/multiprecision/uintwide_t_backend.hpp>

typedef boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<1024U>,
                                      boost::multiprecision::et_off>
big_uint_type;

bool test_uintwide_t_boost_backend()
{
  big_uint_type u = 1;

  for(unsigned i = 1; i <= 100; ++i)
  {
    u *= i;
  }

  const big_uint_type control("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");

  const bool result_is_ok = (u == control);

  return result_is_ok;
}

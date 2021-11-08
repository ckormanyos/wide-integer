///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

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
#include <boost/multiprecision/uintwide_t_backend.hpp>

#include <test/test_uintwide_t.h>

typedef boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<1024U>,
                                      boost::multiprecision::et_off>
local_uint_type;

using boost_uint_backend_type =
  boost::multiprecision::cpp_int_backend<1024,
                                         1024,
                                         boost::multiprecision::unsigned_magnitude>;

using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type,
                                                      boost::multiprecision::et_off>;

bool math::wide_integer::test_uintwide_t_boost_backend()
{
  bool result_is_ok = true;

  // Test a non-trivial calculation. A naive algorithm for calculating
  // a factorial (in this case 100!) has been selected.
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

    result_is_ok &= (local_control_is_ok && boost_control_is_ok);

    // Test divide-by-limb.
    u /= 10U;

    result_is_ok &= (u == local_uint_type("9332621544394415268169923885626670049071596826438162146859296389521759999322991560894146397615651828625369792082722375825118521091686400000000000000000000000"));

    // Test full multiplication.
    u *= u;

    result_is_ok &= (u == local_uint_type("87097824890894800794165901619444858655697206439408401342159325362433799963465833258779670963327549206446903807622196074763642894114359201905739606775078813946074899053317297580134329929871847646073758894343134833829668015151562808541626917661957374931734536035195944960000000000000000000000000000000000000000000000"));
  }

  // Test a very simple constexpr example.
  {
    WIDE_INTEGER_CONSTEXPR local_uint_type cu("123");

    WIDE_INTEGER_CONSTEXPR bool result_cu_is_ok = (cu == 123U);

    result_is_ok &= result_cu_is_ok;

    #if defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST != 0)
    static_assert(result_cu_is_ok == true, "Error: test_uintwide_t_boost_backend not OK!");
    #endif
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

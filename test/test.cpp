///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>

#define BOOST_TEST_MODULE test_uintwide_t
#include <boost/test/included/unit_test.hpp>

#include <test/test_uintwide_t.h>
#include <test/test_uintwide_t_n_binary_ops_template.h>

namespace
{
  constexpr std::size_t test_uintwide_t_n_binary_ops_rounds = 4U;
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_dummy_tag)
{
  std::cout << "running: test_uintwide_t_dummy" << std::endl;

  using uint_type = wide_integer::generic_template::uintwide_t<32U, std::uint8_t>;

  uint_type a = UINT32_C(0x11FF5522);
  uint_type b = UINT32_C(0xABCDFFEE);

  uint_type c = a * b;

  BOOST_CHECK(c == UINT32_C(0xF368039C));
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_boost_backend_tag)
{
  std::cout << "running: test_uintwide_t_boost_backend" << std::endl;
  const bool result_test_uintwide_t_boost_backend_is_ok = test_uintwide_t_boost_backend();
  BOOST_CHECK(result_test_uintwide_t_boost_backend_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_examples_tag)
{
  std::cout << "running: test_uintwide_t_examples" << std::endl;
  const bool result_test_uintwide_t_examples_is_ok = test_uintwide_t_examples();
  BOOST_CHECK(result_test_uintwide_t_examples_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0000128_tag)
{
  std::cout << "running: test_uintwide_t_0000128" << std::endl;
  test_uintwide_t_n_binary_ops_template<128U> test_uintwide_t_n_binary_ops_template_instance(1UL << 19U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  BOOST_CHECK(result_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0000512_tag)
{
  std::cout << "running: test_uintwide_t_0000512" << std::endl;
  test_uintwide_t_n_binary_ops_template<512U> test_uintwide_t_n_binary_ops_template_instance(1UL << 19U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  BOOST_CHECK(result_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0008192_tag)
{
  std::cout << "running: test_uintwide_t_0008192" << std::endl;
  test_uintwide_t_n_binary_ops_template<8192U> test_uintwide_t_n_binary_ops_template_instance(1UL << 13U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  BOOST_CHECK(result_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0065536_tag)
{
  std::cout << "running: test_uintwide_t_0065536" << std::endl;
  test_uintwide_t_n_binary_ops_template<65536U> test_uintwide_t_n_binary_ops_template_instance(1UL << 7U);
  const bool result_is_ok =
    test_uintwide_t_n_binary_ops_template_instance.do_test(test_uintwide_t_n_binary_ops_rounds);
  BOOST_CHECK(result_is_ok);
}

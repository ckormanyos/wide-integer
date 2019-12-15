#include <iomanip>
#include <iostream>

#define BOOST_TEST_MODULE test_uintwide_t
#include <boost/test/included/unit_test.hpp>

#include <test/test_uintwide_t.h>

BOOST_AUTO_TEST_CASE(test_uintwide_t_0000512)
{
  // 512
  std::cout << "running: test_uintwide_t_0000512_binary_add" << std::endl;
  const bool result_test_uintwide_t_0000512_binary_add_is_ok = test_uintwide_t_0000512_binary_add();
  BOOST_CHECK(result_test_uintwide_t_0000512_binary_add_is_ok);

  std::cout << "running: test_uintwide_t_0000512_binary_sub" << std::endl;
  const bool result_test_uintwide_t_0000512_binary_sub_is_ok = test_uintwide_t_0000512_binary_sub();
  BOOST_CHECK(result_test_uintwide_t_0000512_binary_sub_is_ok);

  std::cout << "running: test_uintwide_t_0000512_binary_mul" << std::endl;
  const bool result_test_uintwide_t_0000512_binary_mul_is_ok = test_uintwide_t_0000512_binary_mul();
  BOOST_CHECK(result_test_uintwide_t_0000512_binary_mul_is_ok);

  std::cout << "running: test_uintwide_t_0000512_binary_div" << std::endl;
  const bool result_test_uintwide_t_0000512_binary_div_is_ok = test_uintwide_t_0000512_binary_div();
  BOOST_CHECK(result_test_uintwide_t_0000512_binary_div_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0008192)
{
  // 8192
  std::cout << "running: test_uintwide_t_0008192_binary_add" << std::endl;
  const bool result_test_uintwide_t_0008192_binary_add_is_ok = test_uintwide_t_0008192_binary_add();
  BOOST_CHECK(result_test_uintwide_t_0008192_binary_add_is_ok);

  std::cout << "running: test_uintwide_t_0008192_binary_sub" << std::endl;
  const bool result_test_uintwide_t_0008192_binary_sub_is_ok = test_uintwide_t_0008192_binary_sub();
  BOOST_CHECK(result_test_uintwide_t_0008192_binary_sub_is_ok);

  std::cout << "running: test_uintwide_t_0008192_binary_mul" << std::endl;
  const bool result_test_uintwide_t_0008192_binary_mul_is_ok = test_uintwide_t_0008192_binary_mul();
  BOOST_CHECK(result_test_uintwide_t_0008192_binary_mul_is_ok);

  std::cout << "running: test_uintwide_t_0008192_binary_div" << std::endl;
  const bool result_test_uintwide_t_0008192_binary_div_is_ok = test_uintwide_t_0008192_binary_div();
  BOOST_CHECK(result_test_uintwide_t_0008192_binary_div_is_ok);
}

BOOST_AUTO_TEST_CASE(test_uintwide_t_0065536)
{
  // 65536
  std::cout << "running: test_uintwide_t_0065536_binary_add" << std::endl;
  const bool result_test_uintwide_t_0065536_binary_add_is_ok = test_uintwide_t_0065536_binary_add();
  BOOST_CHECK(result_test_uintwide_t_0065536_binary_add_is_ok);

  std::cout << "running: test_uintwide_t_0065536_binary_sub" << std::endl;
  const bool result_test_uintwide_t_0065536_binary_sub_is_ok = test_uintwide_t_0065536_binary_sub();
  BOOST_CHECK(result_test_uintwide_t_0065536_binary_sub_is_ok);

  std::cout << "running: test_uintwide_t_0065536_binary_mul" << std::endl;
  const bool result_test_uintwide_t_0065536_binary_mul_is_ok = test_uintwide_t_0065536_binary_mul();
  BOOST_CHECK(result_test_uintwide_t_0065536_binary_mul_is_ok);

  std::cout << "running: test_uintwide_t_0065536_binary_div" << std::endl;
  const bool result_test_uintwide_t_0065536_binary_div_is_ok = test_uintwide_t_0065536_binary_div();
  BOOST_CHECK(result_test_uintwide_t_0065536_binary_div_is_ok);
}

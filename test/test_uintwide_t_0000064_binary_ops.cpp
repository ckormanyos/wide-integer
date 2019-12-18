///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <cstddef>
#include <ctime>
#include <random>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <test/parallel_for.h>
#include <test/test_uintwide_t.h>
#include <wide_integer/generic_template_uintwide_t.h>

namespace
{
  constexpr std::size_t test_uintwide_t_digits2              = 64U;
  constexpr std::size_t test_uintwide_t_number_of_test_cases = 1UL << 25U;
}

using native_uint_type = std::uint64_t;

using local_uint_type = wide_integer::generic_template::uintwide_t<test_uintwide_t_digits2, std::uint16_t>;

void get_equal_random_test_values_native_and_local_n(native_uint_type* u_native, local_uint_type* u_local, const std::size_t count)
{
  using random_engine_type =
    wide_integer::generic_template::default_random_engine<local_uint_type::my_digits,
                                                          typename local_uint_type::value_type>;

  random_engine_type random_generator(std::clock());

  my_concurrency::parallel_for
  (
    std::size_t(0U),
    count,
    [&random_generator, &u_local, &u_native](std::size_t i)
    {
      const local_uint_type a = random_generator();

      u_local [i] = a;
      u_native[i] = static_cast<native_uint_type>(a);
    }
  );
}

namespace
{
  std::vector<local_uint_type> a_local;
  std::vector<local_uint_type> b_local;

  std::vector<native_uint_type> a_native;
  std::vector<native_uint_type> b_native;
}

bool test_uintwide_t_0000064_binary_add()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_native.resize(test_uintwide_t_number_of_test_cases);
    b_native.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_native_and_local_n(a_native.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_native_and_local_n(b_native.data(), b_local.data(), a_local.size());
  }

  bool result_is_ok = true;

  my_concurrency::parallel_for
  (
    std::size_t(0U),
    std::size_t(a_local.size()),
    [&result_is_ok](std::size_t i)
    {
      const native_uint_type c_native = a_native[i] + b_native[i];
      const local_uint_type  c_local  = a_local [i] + b_local [i];

      result_is_ok &= (c_native == static_cast<native_uint_type>(c_local));
    }
  );

  return result_is_ok;
}

bool test_uintwide_t_0000064_binary_sub()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_native.resize(test_uintwide_t_number_of_test_cases);
    b_native.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_native_and_local_n(a_native.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_native_and_local_n(b_native.data(), b_local.data(), a_local.size());
  }

  bool result_is_ok = true;

  my_concurrency::parallel_for
  (
    std::size_t(0U),
    std::size_t(a_local.size()),
    [&result_is_ok](std::size_t i)
    {
      const native_uint_type c_native = a_native[i] - b_native[i];
      const local_uint_type  c_local  = a_local [i] - b_local [i];

      result_is_ok &= (c_native == static_cast<native_uint_type>(c_local));
    }
  );

  return result_is_ok;
}

bool test_uintwide_t_0000064_binary_mul()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_native.resize(test_uintwide_t_number_of_test_cases);
    b_native.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_native_and_local_n(a_native.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_native_and_local_n(b_native.data(), b_local.data(), a_local.size());
  }

  bool result_is_ok = true;

  my_concurrency::parallel_for
  (
    std::size_t(0U),
    std::size_t(a_local.size()),
    [&result_is_ok](std::size_t i)
    {
      const native_uint_type c_native = a_native[i] * b_native[i];
      const local_uint_type  c_local  = a_local [i] * b_local [i];

      result_is_ok &= (c_native == static_cast<native_uint_type>(c_local));
    }
  );

  return result_is_ok;
}

bool test_uintwide_t_0000064_binary_div()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_native.resize(test_uintwide_t_number_of_test_cases);
    b_native.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_native_and_local_n(a_native.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_native_and_local_n(b_native.data(), b_local.data(), a_local.size());
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  gen.seed(std::clock());
  std::uniform_int_distribution<> dis(1, static_cast<int>(test_uintwide_t_digits2 - 1U));

  bool result_is_ok = true;

  const native_uint_type native_one(1U);
  const local_uint_type  local_one (1U);

  my_concurrency::parallel_for
  (
    std::size_t(0U),
    std::size_t(a_local.size()),
    [&result_is_ok, &native_one, &local_one, &dis, &gen](std::size_t i)
    {
      const std::size_t right_shift_amount = static_cast<std::size_t>(dis(gen));

      const native_uint_type c_native = a_native[i] / (std::max)(native_one, (b_native[i] >> right_shift_amount));
      const local_uint_type  c_local  = a_local [i] / (std::max)(local_one,  (b_local [i] >> right_shift_amount));

      result_is_ok &= (c_native == static_cast<native_uint_type>(c_local));
    }
  );

  return result_is_ok;
}

#include <cstddef>
#include <ctime>
#include <random>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <wide_integer/generic_template_uintwide_t.h>

#include <test/test_uintwide_t.h>

namespace
{
  constexpr std::size_t test_uintwide_t_digits2              = 128U;
  constexpr std::size_t test_uintwide_t_number_of_test_cases = 1UL << 21U;
}

using boost_uint_backend_type =
  boost::multiprecision::cpp_int_backend<test_uintwide_t_digits2,
                                         test_uintwide_t_digits2,
                                         boost::multiprecision::unsigned_magnitude>;

using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type>;

using local_uint_type = wide_integer::generic_template::uintwide_t<test_uintwide_t_digits2>;

void get_equal_random_test_values_boost_and_local_n(boost_uint_type* u_boost, local_uint_type* u_local, const std::size_t count)
{
  using random_engine_type =
    wide_integer::generic_template::default_random_engine<local_uint_type::my_digits,
                                                          typename local_uint_type::value_type>;

  random_engine_type random_generator(std::clock());

  for(std::size_t i = 0U; i < count; ++i)
  {
    const local_uint_type a = random_generator();

    u_local[i] = a;
    u_boost[i] = boost_uint_type(boost::lexical_cast<std::string>(a));
  }
}

namespace
{
  std::vector<local_uint_type> a_local;
  std::vector<local_uint_type> b_local;

  std::vector<boost_uint_type> a_boost;
  std::vector<boost_uint_type> b_boost;
}

bool test_uintwide_t_0000128_binary_add()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_boost.resize(test_uintwide_t_number_of_test_cases);
    b_boost.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());
  }

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < a_local.size(); ++i)
  {
    const boost_uint_type c_boost = a_boost[i] + b_boost[i];
    const local_uint_type c_local = a_local[i] + b_local[i];

    const std::string str_boost = boost::lexical_cast<std::string>(c_boost);
    const std::string str_local = boost::lexical_cast<std::string>(c_local);

    result_is_ok &= (str_boost == str_local);
  }

  return result_is_ok;
}

bool test_uintwide_t_0000128_binary_sub()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_boost.resize(test_uintwide_t_number_of_test_cases);
    b_boost.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());
  }

  get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
  get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < a_local.size(); ++i)
  {
    const boost_uint_type c_boost = a_boost[i] - b_boost[i];
    const local_uint_type c_local = a_local[i] - b_local[i];

    const std::string str_boost = boost::lexical_cast<std::string>(c_boost);
    const std::string str_local = boost::lexical_cast<std::string>(c_local);

    result_is_ok &= (str_boost == str_local);
  }

  return result_is_ok;
}

bool test_uintwide_t_0000128_binary_mul()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_boost.resize(test_uintwide_t_number_of_test_cases);
    b_boost.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());
  }

  get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
  get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < a_local.size(); ++i)
  {
    const boost_uint_type c_boost = a_boost[i] * b_boost[i];
    const local_uint_type c_local = a_local[i] * b_local[i];

    const std::string str_boost = boost::lexical_cast<std::string>(c_boost);
    const std::string str_local = boost::lexical_cast<std::string>(c_local);

    result_is_ok &= (str_boost == str_local);
  }

  return result_is_ok;
}

bool test_uintwide_t_0000128_binary_div()
{
  if(a_local.empty())
  {
    a_local.resize(test_uintwide_t_number_of_test_cases);
    b_local.resize(test_uintwide_t_number_of_test_cases);

    a_boost.resize(test_uintwide_t_number_of_test_cases);
    b_boost.resize(test_uintwide_t_number_of_test_cases);

    get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
    get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  gen.seed(std::clock());
  std::uniform_int_distribution<> dis(1, static_cast<int>(test_uintwide_t_digits2 - 1U));

  get_equal_random_test_values_boost_and_local_n(a_boost.data(), a_local.data(), a_local.size());
  get_equal_random_test_values_boost_and_local_n(b_boost.data(), b_local.data(), a_local.size());

  const boost_uint_type boost_one(1U);
  const local_uint_type local_one(1U);

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < a_local.size(); ++i)
  {
    const std::size_t right_shift_amount = static_cast<std::size_t>(dis(gen));

    const boost_uint_type c_boost = a_boost[i] / (std::max)(boost_one, (b_boost[i] >> right_shift_amount));
    const local_uint_type c_local = a_local[i] / (std::max)(local_one, (b_local[i] >> right_shift_amount));

    const std::string str_boost = boost::lexical_cast<std::string>(c_boost);
    const std::string str_local = boost::lexical_cast<std::string>(c_local);

    result_is_ok &= (str_boost == str_local);
  }

  return result_is_ok;
}

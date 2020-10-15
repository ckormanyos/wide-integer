///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 -2020.                  //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <iterator>
#include <random>
#include <vector>

constexpr unsigned wide_integer_test9_digits2 = 512U << 8U;

#include <wide_integer/generic_template_uintwide_t.h>

template<typename UnsignedIntegralIteratorType,
         typename RandomEngineType>
void get_random_big_uint(RandomEngineType& rng, UnsignedIntegralIteratorType it_out)
{
  using local_random_value_type = typename RandomEngineType::result_type;

  using local_uint_type = typename std::iterator_traits<UnsignedIntegralIteratorType>::value_type;

  constexpr std::size_t digits_of_uint___type = static_cast<std::size_t>(std::numeric_limits<local_uint_type>::digits);
  constexpr std::size_t digits_of_random_type = static_cast<std::size_t>(std::numeric_limits<local_random_value_type>::digits);

  local_random_value_type next_random = rng();

  *it_out = next_random;

  for(std::size_t i = digits_of_random_type; i < digits_of_uint___type; i += digits_of_random_type)
  {
    (*it_out) <<= digits_of_random_type;

    next_random = rng();

    (*it_out) |= next_random;
  }
}

using big_uint_type = wide_integer::generic_template::uintwide_t<wide_integer_test9_digits2>;

namespace local
{
  std::vector<big_uint_type> a(64U);
  std::vector<big_uint_type> b(a.size());
}

bool wide_integer::example009_timed_mul()
{
  using random_engine_type = std::minstd_rand;

  random_engine_type rng;

  rng.seed(std::clock());

  for(auto i = 0U; i < local::a.size(); ++i)
  {
    get_random_big_uint(rng, local::a.begin() + i);
    get_random_big_uint(rng, local::b.begin() + i);
  }

  std::size_t count = 0U;

  long long total_time;

  const std::clock_t start = std::clock();

  const std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

  for(;;)
  {
    const std::size_t index = count % local::a.size();

    local::a[index] * local::b[index];

    const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    ++count;

    if(total_time > 2999U)
    {
      break;
    }
  }

  const float kops_per_sec = float(count) / float((std::uint32_t) total_time);

  std::cout << "bits: "
            << std::numeric_limits<big_uint_type>::digits
            << ", kops_per_sec: "
            << kops_per_sec
            << count << std::endl;

  const bool result_is_ok = (kops_per_sec > (std::numeric_limits<float>::min)());

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

int main()
{
  const bool result_is_ok = wide_integer::example009_timed_mul();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

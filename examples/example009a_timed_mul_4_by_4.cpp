///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2020.                 //
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

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace
{
  template<typename UnsignedIntegralIteratorType,
           typename RandomEngineType>
  void get_random_big_uint(RandomEngineType& rng, UnsignedIntegralIteratorType it_out)
  {
    using local_uint_type = typename std::iterator_traits<UnsignedIntegralIteratorType>::value_type;

    using distribution_type =
      math::wide_integer::uniform_int_distribution<std::numeric_limits<local_uint_type>::digits, typename local_uint_type::limb_type>;

    distribution_type distribution;

    *it_out = distribution(rng);
  }

  using big_uint_type = math::wide_integer::uintwide_t<128U>;

  std::vector<big_uint_type> local_a(1024U);
  std::vector<big_uint_type> local_b(local_a.size());
}

bool math::wide_integer::example009a_timed_mul_4_by_4()
{
  using random_engine_type =
    std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

  random_engine_type rng;

  rng.seed(static_cast<typename random_engine_type::result_type>(std::clock()));

  for(typename std::vector<big_uint_type>::size_type
        i = static_cast<typename std::vector<big_uint_type>::size_type>(0U);
        i < local_a.size();
      ++i)
  {
    get_random_big_uint(rng, local_a.begin() + static_cast<typename std::vector<big_uint_type>::difference_type>(i));
    get_random_big_uint(rng, local_b.begin() + static_cast<typename std::vector<big_uint_type>::difference_type>(i));
  }

  std::uint64_t count = 0U;
  std::size_t   index = 0U;

  long long total_time;

  const std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

  for(;;)
  {
    local_a[index + 0U] * local_b[index + 0U];
    local_a[index + 1U] * local_b[index + 1U];
    local_a[index + 2U] * local_b[index + 2U];
    local_a[index + 3U] * local_b[index + 3U];

    const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    count += 4U;
    index += 4U;

    if(index >= local_a.size())
    {
      index = 0U;
    }

    if(total_time > 5999U)
    {
      break;
    }
  }

  const float kops_per_sec = float(count) / float((std::uint32_t) total_time);

  std::cout << "bits: "
            << std::numeric_limits<big_uint_type>::digits
            << ", kops_per_sec: "
            << std::fixed
            << std::setprecision(2)
            << kops_per_sec
            << ", count: "
            << count
            << std::endl;

  const bool result_is_ok = (kops_per_sec > (std::numeric_limits<float>::min)());

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

int main()
{
  const bool result_is_ok = wide_integer::example009a_timed_mul_4_by_4();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

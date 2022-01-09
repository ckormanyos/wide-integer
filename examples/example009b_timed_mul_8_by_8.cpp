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
#include <iterator>
#include <limits>
#include <random>
#include <vector>

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local_timed_mul_8_by_8
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

  using big_uint_type = math::wide_integer::uintwide_t<256U>;

  auto local_a() -> std::vector<big_uint_type>&
  {
    static std::vector<big_uint_type> my_local_a(1024U);

    return my_local_a;
  }

  auto local_b() -> std::vector<big_uint_type>&
  {
    static std::vector<big_uint_type> my_local_b(local_a().size());

    return my_local_b;
  }
} // namespace local_timed_mul_8_by_8

auto math::wide_integer::example009b_timed_mul_8_by_8() -> bool
{
  using random_engine_type =
    std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

  random_engine_type rng; // NOLINT(cert-msc32-c,cert-msc51-cpp)

  rng.seed(static_cast<typename random_engine_type::result_type>(std::clock()));

  for(auto i = static_cast<typename std::vector<local_timed_mul_8_by_8::big_uint_type>::size_type>(0U); i < local_timed_mul_8_by_8::local_a().size(); ++i)
  {
    local_timed_mul_8_by_8::get_random_big_uint(rng, local_timed_mul_8_by_8::local_a().begin() + static_cast<typename std::vector<local_timed_mul_8_by_8::big_uint_type>::difference_type>(i));
    local_timed_mul_8_by_8::get_random_big_uint(rng, local_timed_mul_8_by_8::local_b().begin() + static_cast<typename std::vector<local_timed_mul_8_by_8::big_uint_type>::difference_type>(i));
  }

  std::uint64_t count = 0U;
  std::size_t   index = 0U;

  long long total_time { }; // NOLINT(google-runtime-int)

  const std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

  for(;;)
  {
    local_timed_mul_8_by_8::local_a().at(index + 0U) * local_timed_mul_8_by_8::local_b().at(index + 0U);
    local_timed_mul_8_by_8::local_a().at(index + 1U) * local_timed_mul_8_by_8::local_b().at(index + 1U);
    local_timed_mul_8_by_8::local_a().at(index + 2U) * local_timed_mul_8_by_8::local_b().at(index + 2U);
    local_timed_mul_8_by_8::local_a().at(index + 3U) * local_timed_mul_8_by_8::local_b().at(index + 3U);

    const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    count += 4U;
    index += 4U;

    if(index >= local_timed_mul_8_by_8::local_a().size())
    {
      index = 0U;
    }

    if(total_time > 5999U)
    {
      break;
    }
  }

  const float kops_per_sec = float(count) / float(static_cast<std::uint32_t>(total_time));

  std::cout << "bits: "
            << std::numeric_limits<local_timed_mul_8_by_8::big_uint_type>::digits
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
  const bool result_is_ok = wide_integer::example009b_timed_mul_8_by_8();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

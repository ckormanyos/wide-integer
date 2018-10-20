///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This Miller-Rabin primality test is loosely based on
// an adaptation of some code from Boost.Multiprecision.
// The Boost.Multiprecision code can be found here:
// https://www.boost.org/doc/libs/1_68_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

#include <array>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

//#define TEST_UINTWIDE_T_USE_FIXED_RANDOM_SEEDS

#define TEST_UINTWIDE_T_USE_NUMBER_OF_DIGITS std::size_t(256U)

#include <generic_template_uintwide_t.h>

// Some examples:
// 256-Bit
// BaseForm[16^^391A52D30A8E2992C873DFCACCFD1C0A41223B270A89B68F5D80D1B79EB9F7FB, 10]
//   25828342025791210859166436130183142623644908596914722479104004883234718087163
//
// Obtain another primality check of this number.
// PrimeQ[25828342025791210859166436130183142623644908596914722479104004883234718087163]
//   True

// 512-Bit
// BaseForm[16^^66DCFC5C356041F18BDE1E24967F927792676430ECD2CA793B5470B22B25135DD8C5BF30B99ED6FE77323AD64D1A8E797A9F61B16D6A62916E1ABDAE172CD347, 10]
//   5387384271039304745508551812951241747064418070116709491801209017199450051016259069177713089714034058888601640767987406861497345836726393193223080052052807

// 1024-Bit
// BaseForm[16^^4C13F2300C50C0A568F013964C38E991837064DD762FCF647E22F325EA749126EA71B5CF412BD40BAFA90E73DF9832F5C74319FD5952FC9D72AE45B424EA2D168F718D2858A539E03CC6F15AF52101E4D6EFA03A2F446694AC64715653355C6607492B4A4B0B7B250AF964D878CA9F5B8ADA7CED003E2B146D73EFD048F6DB33, 10]
//   53423728181800137777827534817849948240183071720626548882339419582232495498871453045181774681728102488652942801395668402659115038117498862739489336673095967905611982718105156696703887027839599655773268311858451581630696642930238875596347814493959817488606142483475257336546018770999866807302647786275819936563

namespace
{
  #if !defined(TEST_UINTWIDE_T_USE_FIXED_RANDOM_SEEDS)

  template<typename UnsignedIntegralType,
           const UnsignedIntegralType Polynomial,
           const UnsignedIntegralType InitialValue,
           const UnsignedIntegralType FinalXorValue>
  UnsignedIntegralType crc_bitwise_template(const std::uint8_t* message, const std::size_t count)
  {
    using value_type = UnsignedIntegralType;

    value_type crc = InitialValue;

    // Perform modulo-2 division, one byte at a time.
    for(std::size_t byte = 0U; byte < count; ++byte)
    {
      // Bring the next byte into the result.
      crc ^= (value_type(message[byte]) << (std::numeric_limits<value_type>::digits - 8U));

      // Perform a modulo-2 division, one bit at a time.
      for(std::int_fast8_t bit = 8; bit > 0; --bit)
      {
        // Divide the current data bit.
        if((crc & (std::uintmax_t(1U) << (std::numeric_limits<value_type>::digits - 1U))) != 0U)
        {
          crc = value_type(crc << 1) ^ Polynomial;
        }
        else
        {
          crc <<= 1;
        }
      }
    }

    return value_type(crc ^ FinalXorValue);
  }

  inline std::uint64_t high_resolution_now_with_crc64()
  {
    using clock_type = std::chrono::high_resolution_clock;

    // Obtain an initial value of std::chrono::high_resolution_clock::now().
    const std::uintmax_t initial_now = 
      static_cast<std::uintmax_t>(std::chrono::duration_cast<std::chrono::nanoseconds>
                                    (clock_type::now().time_since_epoch()).count());

    std::uintmax_t current_now = initial_now;

    while(current_now == initial_now)
    {
      // Wait for std::chrono::high_resolution_clock::now()
      // to differ from the initial value previously obtained.

      current_now =
        static_cast<std::uintmax_t>(std::chrono::duration_cast<std::chrono::nanoseconds>
          (clock_type::now().time_since_epoch()).count());

      if(current_now != initial_now)
      {
        break;
      }
    }

    // Perform a logical xor of current_now with the maximum value of its type.
    current_now ^= (std::numeric_limits<std::uintmax_t>::max)();

    // Extract the data bytes of current now into an array...
    std::array<std::uint8_t, std::numeric_limits<std::uintmax_t>::digits / 8U> current_now_data;

    for(std::uint_fast8_t i = 0U; i < current_now_data.size(); ++ i)
    {
      current_now_data[i] = std::uint8_t(current_now >> (i * 8U));
    }

    // ... and... Finally, run a CRC64-WE checksum over the data bytes of current_now.
    const std::uint64_t current_now_crc64_we_result =
      crc_bitwise_template<std::uint64_t,
                           UINT64_C(0x42F0E1EBA9EA3693),
                           UINT64_C(0xFFFFFFFFFFFFFFFF),
                           UINT64_C(0xFFFFFFFFFFFFFFFF)>(current_now_data.data(),
                                                         current_now_data.size());

    // Return the 64-bit pseudo-random seed.
    return current_now_crc64_we_result;
  }

  #endif // not TEST_UINTWIDE_T_USE_FIXED_RANDOM_SEEDS

  class pcg_random_fast32 final
  {
  public:
    pcg_random_fast32(const std::uint64_t& initial_state,
                      const std::uint64_t& initial_seq) : my_state(0U),
                                                          my_inc  ((initial_seq << 1U) | 1U)
    {
      step();

      my_state += initial_state;

      step();
    }

    pcg_random_fast32(const pcg_random_fast32& other) : my_state(other.my_state),
                                                        my_inc  (other.my_inc) { }

    ~pcg_random_fast32() = default;

    pcg_random_fast32& operator=(const pcg_random_fast32& other)
    {
      if(this != &other)
      {
        my_state = other.my_state;
        my_inc   = other.my_inc;
      }

      return *this;
    }

    std::uint32_t operator()()
    {
      const std::uint64_t previous_state = my_state;

      step();

      return rotr(std::uint32_t(((previous_state >> 18U) ^ previous_state) >> 27U), std::int32_t(previous_state >> 59U));
    }

  private:
    std::uint64_t my_state;
    std::uint64_t my_inc;

    static const std::uint64_t default_multiplier = UINT64_C(6364136223846793005);

    pcg_random_fast32() = default;

    void step()
    {
      my_state = std::uint64_t(std::uint64_t(my_state * default_multiplier) + my_inc);
    }

    static std::uint32_t rotr(std::uint32_t value, std::int32_t rot)
    {
      return (value >> rot) | (value << std::int32_t(std::uint32_t(-rot) & 31U));
    }
  };

  template<typename UnsignedIntegralType>
  class random_unsigned_generator final
  {
  public:
    using value_type = UnsignedIntegralType;

    static_assert((std::numeric_limits<value_type>::digits % std::numeric_limits<std::uint32_t>::digits) == 0,
                  "Error: The width of UnsignedIntegralType must be a multiple of the digits in uint32_t.");

    random_unsigned_generator(const std::uint64_t seed0,
                              const std::uint64_t seed1 = UINT64_C(0)) : my_gen(seed0, seed1) { }

    random_unsigned_generator() : my_gen() { }

    value_type operator()(const value_type& lo_range = value_type(0U),
                          const value_type& hi_range = (std::numeric_limits<value_type>::max)())
    {
      value_type next_rand = my_gen();

      for(;;)
      {
        for(std::size_t i = 0U; i < std::numeric_limits<value_type>::digits / std::numeric_limits<std::uint32_t>::digits; ++i)
        {
          next_rand <<= 32U;

          next_rand |= std::uint32_t(my_gen());
        }

        if((next_rand >= lo_range) && (next_rand <= hi_range))
        {
          break;
        }
      }

      return next_rand;
    }

  private:
    pcg_random_fast32 my_gen;
  };

  bool is_small_prime(const std::uint_fast8_t n)
  {
    static const std::array<std::uint_fast8_t, 48U> small_primes = 
    {{
      UINT8_C(  3), UINT8_C(  5), UINT8_C(  7), UINT8_C( 11), UINT8_C( 13), UINT8_C( 17), UINT8_C( 19), UINT8_C( 23),
      UINT8_C( 29), UINT8_C( 31), UINT8_C( 37), UINT8_C( 41), UINT8_C( 43), UINT8_C( 47), UINT8_C( 53), UINT8_C( 59),
      UINT8_C( 61), UINT8_C( 67), UINT8_C( 71), UINT8_C( 73), UINT8_C( 79), UINT8_C( 83), UINT8_C( 89), UINT8_C( 97),
      UINT8_C(101), UINT8_C(103), UINT8_C(107), UINT8_C(109), UINT8_C(113), UINT8_C(127), UINT8_C(131), UINT8_C(137),
      UINT8_C(139), UINT8_C(149), UINT8_C(151), UINT8_C(157), UINT8_C(163), UINT8_C(167), UINT8_C(173), UINT8_C(179),
      UINT8_C(181), UINT8_C(191), UINT8_C(193), UINT8_C(197), UINT8_C(199), UINT8_C(211), UINT8_C(223), UINT8_C(227)
    }};

    return (std::find(small_primes.cbegin(),
                      small_primes.cend(), n) != small_primes.cend());
  }

  template<typename UnsignedIntegralType>
  bool check_small_factors(const UnsignedIntegralType& n)
  {
    // TBD: Can we eliminate some of the numerous
    // return statements in this subroutine?
    // Should we use lambda functions or other
    // small subroutines?

    {
      static const std::array<std::uint_fast8_t, 8U> small_factors0 =
      {{
        UINT8_C( 3), UINT8_C( 5), UINT8_C( 7), UINT8_C(11),
        UINT8_C(13), UINT8_C(17), UINT8_C(19), UINT8_C(23)
      }};

      static const std::uint32_t pp0 = UINT32_C(223092870);

      const std::uint32_t m = n % pp0;

      for(std::size_t i = 0U; i < small_factors0.size(); ++i)
      {
        if((m % std::uint32_t(small_factors0[i])) == 0U)
        {
          return false;
        }
      }
    }

    {
      static const std::array<std::uint_fast8_t, 6U> small_factors1 =
      {{
        UINT8_C(29), UINT8_C(31), UINT8_C(37), UINT8_C(41),
        UINT8_C(43), UINT8_C(47)
      }};

      static const std::uint32_t pp1 = UINT32_C(2756205443);

      const std::uint32_t m = n % pp1;

      for(std::size_t i = 0U; i < small_factors1.size(); ++i)
      {
        if((m % std::uint32_t(small_factors1[i])) == 0U)
        {
          return false;
        }
      }
    }

    {
      static const std::array<std::uint_fast8_t, 5U> small_factors2 =
      {{
        UINT8_C(53), UINT8_C(59), UINT8_C(61), UINT8_C(67),
        UINT8_C(71)
      }};

      static const std::uint32_t pp2 = UINT32_C(907383479);

      const std::uint32_t m = n % pp2;

      for(std::size_t i = 0U; i < small_factors2.size(); ++i)
      {
        if((m % std::uint32_t(small_factors2[i])) == 0U)
        {
          return false;
        }
      }
    }

    {
      static const std::array<std::uint_fast8_t, 5U> small_factors3 =
      {{
        UINT8_C(73), UINT8_C(79), UINT8_C(83), UINT8_C(89),
        UINT8_C(97)
      }};

      static const std::uint32_t pp3 = UINT32_C(4132280413);

      const std::uint32_t m = n % pp3;

      for(std::size_t i = 0U; i < small_factors3.size(); ++i)
      {
        if((m % std::uint32_t(small_factors3[i])) == 0U)
        {
          return false;
        }
      }
    }

    {
      static const std::array<std::array<std::uint_fast8_t, 4U>, 6U> small_factors4 =
      {{
        {{ UINT8_C(101), UINT8_C(103), UINT8_C(107), UINT8_C(109) }},
        {{ UINT8_C(113), UINT8_C(127), UINT8_C(131), UINT8_C(137) }},
        {{ UINT8_C(139), UINT8_C(149), UINT8_C(151), UINT8_C(157) }},
        {{ UINT8_C(163), UINT8_C(167), UINT8_C(173), UINT8_C(179) }},
        {{ UINT8_C(181), UINT8_C(191), UINT8_C(193), UINT8_C(197) }},
        {{ UINT8_C(199), UINT8_C(211), UINT8_C(223), UINT8_C(227) }}
      }};

      static const std::array<std::uint32_t, 6U> pp4 =
      {{
        UINT32_C(121330189),
        UINT32_C(113) * UINT32_C(127) * UINT32_C(131) * UINT32_C(137),
        UINT32_C(139) * UINT32_C(149) * UINT32_C(151) * UINT32_C(157),
        UINT32_C(163) * UINT32_C(167) * UINT32_C(173) * UINT32_C(179),
        UINT32_C(181) * UINT32_C(191) * UINT32_C(193) * UINT32_C(197),
        UINT32_C(199) * UINT32_C(211) * UINT32_C(223) * UINT32_C(227)
      }};

      for(std::size_t k = 0U; k < pp4.size(); ++k)
      {
        const std::uint32_t m = n % pp4[k];

        for(std::size_t i = 0U; i < small_factors4[0U].size(); ++i)
        {
          if((m % std::uint32_t(small_factors4[k][i])) == 0U)
          {
            return false;
          }
        }
      }
    }

    return true;
  }

  template<typename UnsignedIntegralType>
  std::size_t lsb(const UnsignedIntegralType& x)
  {
    std::size_t i;
    std::size_t j;
    std::size_t bpos = 0U;

    UnsignedIntegralType x_tmp(x);

    // This loop assumes that at least one bit is set in x.
    for(i = 0U; ((x_tmp != 0U) && (bpos == 0U)); ++i)
    {
      std::uint32_t a = std::uint32_t(x_tmp);

      for(j = 0U; j < std::size_t(std::numeric_limits<std::uint32_t>::digits); ++j)
      {
        if((a & 1U) != 0U)
        {
          bpos = std::size_t(std::size_t(i * std::size_t(std::numeric_limits<std::uint32_t>::digits)) + j);

          break;
        }

        a >>= 1;
      }

      if(bpos == 0U)
      {
        x_tmp >>= std::size_t(std::numeric_limits<std::uint32_t>::digits);
      }
    }

    return bpos;
  }

  template<typename UnsignedIntegralType1,
           typename UnsignedIntegralType2 = UnsignedIntegralType1>
  UnsignedIntegralType1 powm(const UnsignedIntegralType1& a,
                                   UnsignedIntegralType2  b,
                             const UnsignedIntegralType1& c)
  {
    // Calculate (b ^ p) % m.

    // TBD: Can deduction of the double-width type be made more generic?
    using local_double_width_type = typename UnsignedIntegralType1::double_width_type;
    using local_normal_width_type = UnsignedIntegralType1;

          local_double_width_type x(std::uint8_t(1U));
          local_double_width_type y(a);
          local_double_width_type result;
    const local_double_width_type c_local(c);

    const UnsignedIntegralType2 zero(std::uint8_t(0U));

    while(b > zero)
    {
      if(std::uint32_t(b) & 1U)
      {
        result = x * y;
        x = result % c_local;
      }

      result = y * y;
      y = result % c_local;
      b >>= 1;
    }

    return (local_normal_width_type(x) % c);
  }

  template<typename UnsignedIntegralType,
           typename RandomGenerator>
  bool my_miller_rabin_test(const UnsignedIntegralType& n,
                            const std::size_t           trials,
                                  RandomGenerator&      dist)
  {
    // TBD: Clean up the multiple return statements in this subroutine.

    using wide_integer_type = UnsignedIntegralType;

    if(n == 2U)
    {
      // Trivial special case.
      return true;
    }

    if((std::uint32_t(n) & 1U) == 0U)
    {
      // n is even.
      return false;
    }

    if(n <= 227U)
    {
      return is_small_prime(n);
    }

    if(check_small_factors(n) == false)
    {
      return false;
    }

    wide_integer_type nm1 = n - 1U;

    // Perform a single Fermat test which will
    // exclude many non-prime candidates.

    // We know n is greater than 227 because we have already
    // excluded all small factors up to and including 227.
    wide_integer_type q(std::uint_fast8_t(228U));

    wide_integer_type x;
    wide_integer_type y;

    x = powm(q, nm1, n);

    if(x != 1U)
    {
      return false;
    }

    q = n - 1U;
    const std::size_t k = lsb(q);
    q >>= k;

    // Execute the trials.
    for(std::size_t i = 0U; i < trials; ++i)
    {
      x = dist(2U, n - 2U);
      y = powm(x, q, n);

      std::size_t j = 0U;

      // TBD: The following code seems convoluded and it is difficult
      // to understand this code. Can this while-loop and all returns
      // and breaks be written in more intuitive and understandable form?
      while(true)
      {
        if(y == nm1)
        {
          break;
        }

        if(y == 1U)
        {
          if(j == 0U)
          {
            break;
          }

          return false; // test failed
        }

        if(++j == k)
        {
          return false; // failed
        }

        y = powm(y, 2U, n);
      }
    }

    return true;  // Yeheh! probably prime.
  }
}

bool miller_rabin_result()
{
  #if defined(TEST_UINTWIDE_T_USE_NUMBER_OF_DIGITS)
  using wide_integer_type = wide_integer::generic_template::uintwide_t<TEST_UINTWIDE_T_USE_NUMBER_OF_DIGITS>;
  #else
  using wide_integer_type = wide_integer::generic_template::uintwide_t<256U>;
  #endif

  #if defined(TEST_UINTWIDE_T_USE_FIXED_RANDOM_SEEDS)
  const std::uint64_t seed0 = UINT64_C(0xDAD6177428754C69);
  const std::uint64_t seed1 = UINT64_C(0x73DD1E70A590026C);
  const std::uint64_t seed2 = UINT64_C(0xD04437538D54D2F1);
  const std::uint64_t seed3 = UINT64_C(0xB81364AE3D6B7C96);
  #else
  const std::uint64_t seed0 = high_resolution_now_with_crc64();
  const std::uint64_t seed1 = high_resolution_now_with_crc64();
  const std::uint64_t seed2 = high_resolution_now_with_crc64();
  const std::uint64_t seed3 = high_resolution_now_with_crc64();
  #endif

  random_unsigned_generator<wide_integer_type> gen1(seed0, seed1);
  random_unsigned_generator<wide_integer_type> gen2(seed2, seed3);

  std::cout << std::hex << std::uppercase << "Random seed0: 0x" << seed0 << std::endl;
  std::cout << std::hex << std::uppercase << "Random seed1: 0x" << seed1 << std::endl;
  std::cout << std::hex << std::uppercase << "Random seed2: 0x" << seed2 << std::endl;
  std::cout << std::hex << std::uppercase << "Random seed3: 0x" << seed3 << std::endl;

        std::uint_fast32_t i;
  const std::uint_fast32_t number_of_trials = UINT32_C(10000000);

  bool miller_rabin_test_result = false;

  for(i = 0U; (i < number_of_trials) && (miller_rabin_test_result == false); ++i)
  {
    wide_integer_type n = gen1();

    miller_rabin_test_result = my_miller_rabin_test(n, 25U, gen2);

    if(miller_rabin_test_result)
    {
      // The value of n (at index i) is a probably prime.
      std::cout << "We have a probable prime at index: "
                << std::dec
                << i
                << std::endl;

      // We will now find out if [(n - 1) / 2] is also prime.
      miller_rabin_test_result = my_miller_rabin_test((n - 1U) / 2U, 25U, gen2);

      if(miller_rabin_test_result)
      {
        std::cout << std::endl
                  << "We have a safe prime with value: 0x"
                  << std::hex
                  << std::uppercase
                  << n
                  << std::endl;
      }
    }
  }

  const bool did_not_find_a_safe_prime = (i == number_of_trials);

  if(did_not_find_a_safe_prime)
  {
    std::cout << "Information: No safe primes were found" << std::endl;
  }

  return (did_not_find_a_safe_prime == false);
}

int main()
{
  const bool miller_rabin_test_is_ok = miller_rabin_result();

  static_cast<void>(miller_rabin_test_is_ok);
}

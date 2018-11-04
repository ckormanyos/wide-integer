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
#include <cstdint>
#include <iomanip>
#include <iostream>

#include <wide_integer/generic_template_uintwide_t.h>

namespace
{
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

      return rotate(std::uint32_t   (((previous_state >> 18U) ^ previous_state) >> 27U),
                    std::int_fast8_t  (previous_state >> 59U));
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

    static std::uint32_t rotate(std::uint32_t value, std::int_fast8_t rot)
    {
      return (value >> rot) | (value << std::int_fast8_t(std::uint_fast8_t(-rot) & 31U));
    }
  };

  template<typename UnsignedIntegralType>
  class random_unsigned_generator final
  {
  public:
    using value_type = UnsignedIntegralType;

    static_assert(((std::numeric_limits<value_type>::digits % std::numeric_limits<std::uint32_t>::digits) == 0),
                  "Error: The width of UnsignedIntegralType must be a multiple of the digits in uint32_t.");

    random_unsigned_generator() : my_gen() { }

    random_unsigned_generator(const std::uint64_t seed0,
                              const std::uint64_t seed1) : my_gen(seed0, seed1) { }

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

  template<typename UnsignedIntegralType,
           typename RandomGenerator>
  bool miller_rabin_test(const UnsignedIntegralType& n,
                         const std::size_t           number_of_trials,
                               RandomGenerator&      random_distribution)
  {
    // TBD: Clean up the multiple return statements in this subroutine.

    using local_wide_integer_type = UnsignedIntegralType;

    if(n == 2U)
    {
      // Trivial special case.
      return true;
    }

    const std::uint32_t n32(n);

    if((std::uint_fast8_t(n32) & 1U) == 0U)
    {
      // n is even.
      return false;
    }

    if(n <= 227U)
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
                        small_primes.cend(), std::uint_fast8_t(n32)) != small_primes.cend());
    }

    // Check small factors.
    {
      static const std::array<std::uint_fast8_t, 8U> small_factors0 =
      {{
        UINT8_C( 3), UINT8_C( 5), UINT8_C( 7), UINT8_C(11),
        UINT8_C(13), UINT8_C(17), UINT8_C(19), UINT8_C(23)
      }};

      static const std::uint32_t pp0 = UINT32_C(223092870);

      const std::uint32_t m(n % pp0);

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

      const std::uint32_t m(n % pp1);

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

      const std::uint32_t m(n % pp2);

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

      const std::uint32_t m(n % pp3);

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
        const std::uint32_t m(n % pp4[k]);

        for(std::size_t i = 0U; i < small_factors4[0U].size(); ++i)
        {
          if((m % std::uint32_t(small_factors4[k][i])) == 0U)
          {
            return false;
          }
        }
      }
    }

    const local_wide_integer_type nm1(n - 1U);

    // Perform a single Fermat test which will
    // exclude many non-prime candidates.

    // We know n is greater than 227 because we have already
    // excluded all small factors up to and including 227.
    local_wide_integer_type q(std::uint_fast8_t(228U));

    if(powm(q, nm1, n) != 1U)
    {
      return false;
    }

    q = nm1;
    const std::size_t k = lsb(q);
    q >>= k;

    // Execute the random trials.
    for(std::size_t i = 0U; i < number_of_trials; ++i)
    {
      const local_wide_integer_type x = random_distribution(2U, n - 2U);

      local_wide_integer_type y = powm(x, q, n);

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

          return false;
        }

        ++j;

        if(j == k)
        {
          return false;
        }

        y = powm(y, 2U, n);
      }
    }

    // Probably prime.
    return true;
  }
}

int main()
{
  using wide_integer_type = wide_integer::generic_template::uintwide_t<256U>;

  // Use fixed seeds in order to obtain deterministic
  // and reproducible results for this test.

  const std::uint64_t seed0 = UINT64_C(0xDAD6177428754C69);
  const std::uint64_t seed1 = UINT64_C(0x73DD1E70A590026C);
  const std::uint64_t seed2 = UINT64_C(0xD04437538D54D2F1);
  const std::uint64_t seed3 = UINT64_C(0xB81364AE3D6B7C96);

  random_unsigned_generator<wide_integer_type> gen1(seed0, seed1);
  random_unsigned_generator<wide_integer_type> gen2(seed2, seed3);

        std::uint_fast32_t i;
  const std::uint_fast32_t number_of_trials = UINT32_C(1000000);

  bool result_is_ok = false;

  for(i = 0U; i < number_of_trials; ++i)
  {
    wide_integer_type n = gen1();

    if(miller_rabin_test(n, 25U, gen2))
    {
      // We will now find out if [(n - 1) / 2] is also prime.

      result_is_ok = (   (miller_rabin_test((n - 1U) >> 1U, 25U, gen2) == true)
                      && (i == 18197U)
                      && (n == "0x807517654FB99B7EE275416CF4D9987E810B5E06753536531B0F1443A6145B87"));

      break;
    }
  }

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

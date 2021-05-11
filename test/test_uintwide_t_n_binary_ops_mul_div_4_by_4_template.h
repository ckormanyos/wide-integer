///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_MUL_DIV_4_BY_4_TEMPLATE_2021_03_04_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_MUL_DIV_4_BY_4_TEMPLATE_2021_03_04_H_

  #include <atomic>

  #include <math/wide_integer/uintwide_t.h>
  #include <test/test_uintwide_t_n_base.h>

  template<const math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename EnableType = void>
  class test_uintwide_t_n_binary_ops_mul_div_4_by_4_template;

  template<const math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  class test_uintwide_t_n_binary_ops_mul_div_4_by_4_template
    <MyWidth2,
     MyLimbType,
     typename std::enable_if<(   (std::numeric_limits<MyLimbType>::digits * 4 == MyWidth2)
                              && (std::is_fundamental<MyLimbType>::value == true)
                              && (std::is_integral   <MyLimbType>::value == true)
                              && (std::is_unsigned   <MyLimbType>::value == true))>::type>
    : public test_uintwide_t_n_binary_ops_base
  {
  private:
    static constexpr math::wide_integer::size_t digits2 = MyWidth2;

    virtual math::wide_integer::size_t get_digits2 () const { return digits2; }

    using native_uint_cntrl_type =
      typename math::wide_integer::detail::uint_type_helper<digits2>::exact_unsigned_type;

    using local_limb_type = MyLimbType;

    using local_uint_ab_type = math::wide_integer::uintwide_t<digits2, local_limb_type>;

  public:
    test_uintwide_t_n_binary_ops_mul_div_4_by_4_template(const std::size_t count)
      : test_uintwide_t_n_binary_ops_base(count),
        a_local(),
        b_local(),
        a_cntrl(),
        b_cntrl() { }

    virtual ~test_uintwide_t_n_binary_ops_mul_div_4_by_4_template() = default;

    virtual bool do_test(const std::size_t rounds)
    {
      bool result_is_ok = true;

      for(std::size_t i = 0U; i < rounds; ++i)
      {
        std::cout << "initialize()       native compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        this->initialize();

        std::cout << "test_binary_mul()  native compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_mul();

        std::cout << "test_binary_div()  native compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_div();
      }

      return result_is_ok;
    }

    virtual void initialize()
    {
      a_local.clear();
      b_local.clear();

      a_cntrl.clear();
      b_cntrl.clear();

      a_local.resize(size());
      b_local.resize(size());

      a_cntrl.resize(size());
      b_cntrl.resize(size());

      get_equal_random_test_values_cntrl_and_local_n(a_local.data(), a_cntrl.data(), size());
      get_equal_random_test_values_cntrl_and_local_n(b_local.data(), b_cntrl.data(), size());
    }

    virtual bool test_binary_mul() const
    {
      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      bool result_is_ok = true;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const native_uint_cntrl_type c_cntrl =   native_uint_cntrl_type(a_cntrl[i])
                                                 * b_cntrl[i];

          const local_uint_ab_type c_local =   static_cast<local_uint_ab_type>(a_local[i])
                                             * static_cast<local_uint_ab_type>(b_local[i]);

          const std::string str_boost = hexlexical_cast(c_cntrl);
          const std::string str_local = hexlexical_cast(c_local);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost == str_local);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

    virtual bool test_binary_div() const
    {
      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      test_uintwide_t_n_binary_ops_base::my_gen.seed(static_cast<typename random_generator_type::result_type>(std::clock()));
      std::uniform_int_distribution<> dis(1, static_cast<int>(digits2 - 1U));

      bool result_is_ok = true;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this, &dis](std::size_t i)
        {
          while(test_lock.test_and_set()) { ; }
          const std::size_t right_shift_amount = static_cast<std::size_t>(dis(my_gen));
          test_lock.clear();

          const native_uint_cntrl_type c_cntrl = a_cntrl[i] / (std::max)(native_uint_cntrl_type(1U), native_uint_cntrl_type(b_cntrl[i] >> right_shift_amount));
          const local_uint_ab_type     c_local = a_local[i] / (std::max)(local_uint_ab_type(1U),                           (b_local[i] >> right_shift_amount));

          const std::string str_boost = hexlexical_cast(c_cntrl);
          const std::string str_local = hexlexical_cast(c_local);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost == str_local);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

  private:
    std::vector<local_uint_ab_type> a_local;
    std::vector<local_uint_ab_type> b_local;

    std::vector<native_uint_cntrl_type> a_cntrl;
    std::vector<native_uint_cntrl_type> b_cntrl;

    template<typename OtherLocalUintType,
             typename OtherCntrlUintType>
    static void get_equal_random_test_values_cntrl_and_local_n(OtherLocalUintType* u_local,
                                                               OtherCntrlUintType* u_cntrl,
                                                               const std::size_t count)
    {
      using other_local_uint_type = OtherLocalUintType;
      using other_cntrl_uint_type = OtherCntrlUintType;

      test_uintwide_t_n_base::my_random_generator.seed(static_cast<typename std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647>::result_type>(std::clock()));

      using distribution_type =
        math::wide_integer::uniform_int_distribution<other_local_uint_type::my_width2, typename other_local_uint_type::limb_type>;

      distribution_type distribution;

      std::atomic_flag rnd_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        count,
        [&u_local, &u_cntrl, &distribution, &rnd_lock](std::size_t i)
        {
          while(rnd_lock.test_and_set()) { ; }
          const other_local_uint_type a = distribution(my_random_generator);
          rnd_lock.clear();

          u_local[i] = a;
          u_cntrl[i] = static_cast<other_cntrl_uint_type>(a);
        }
      );
    }
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_MUL_DIV_4_BY_4_TEMPLATE_2021_03_04_H_

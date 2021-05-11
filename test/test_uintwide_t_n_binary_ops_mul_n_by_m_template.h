///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_MUL_N_BY_M_TEMPLATE_2019_12_26_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_MUL_N_BY_M_TEMPLATE_2019_12_26_H_

  #include <atomic>

  #include <test/test_uintwide_t_n_base.h>

  template<const math::wide_integer::size_t MyDigits2A,
           const math::wide_integer::size_t MyDigits2B,
           typename MyLimbType = std::uint32_t>
  class test_uintwide_t_n_binary_ops_mul_n_by_m_template : public test_uintwide_t_n_binary_ops_base
  {
  private:
    static constexpr math::wide_integer::size_t digits2a = MyDigits2A;
    static constexpr math::wide_integer::size_t digits2b = MyDigits2B;

            math::wide_integer::size_t get_digits2a() const { return digits2a; }
            math::wide_integer::size_t get_digits2b() const { return digits2b; }
    virtual math::wide_integer::size_t get_digits2 () const { return digits2a + digits2b; }

    using boost_uint_backend_a_type =
      boost::multiprecision::cpp_int_backend<digits2a,
                                             digits2a,
                                             boost::multiprecision::unsigned_magnitude>;

    using boost_uint_backend_b_type =
      boost::multiprecision::cpp_int_backend<digits2b,
                                             digits2b,
                                             boost::multiprecision::unsigned_magnitude>;

    using boost_uint_backend_c_type =
      boost::multiprecision::cpp_int_backend<digits2a + digits2b,
                                             digits2a + digits2b,
                                             boost::multiprecision::unsigned_magnitude>;

    using boost_uint_a_type = boost::multiprecision::number<boost_uint_backend_a_type, boost::multiprecision::et_off>;
    using boost_uint_b_type = boost::multiprecision::number<boost_uint_backend_b_type, boost::multiprecision::et_off>;
    using boost_uint_c_type = boost::multiprecision::number<boost_uint_backend_c_type, boost::multiprecision::et_off>;

    using local_limb_type = MyLimbType;

    using local_uint_a_type = math::wide_integer::uintwide_t<digits2a, local_limb_type>;
    using local_uint_b_type = math::wide_integer::uintwide_t<digits2b, local_limb_type>;
    using local_uint_c_type = math::wide_integer::uintwide_t<digits2a + digits2b, local_limb_type>;

  public:
    test_uintwide_t_n_binary_ops_mul_n_by_m_template(const std::size_t count)
      : test_uintwide_t_n_binary_ops_base(count),
        a_local(),
        b_local(),
        a_boost(),
        b_boost() { }

    virtual ~test_uintwide_t_n_binary_ops_mul_n_by_m_template() = default;

    virtual bool do_test(const std::size_t rounds)
    {
      bool result_is_ok = true;

      for(std::size_t i = 0U; i < rounds; ++i)
      {
        std::cout << "initialize()       boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        this->initialize();

        std::cout << "test_binary_mul()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_mul();
      }

      return result_is_ok;
    }

    virtual void initialize()
    {
      a_local.clear();
      b_local.clear();

      a_boost.clear();
      b_boost.clear();

      a_local.resize(size());
      b_local.resize(size());

      a_boost.resize(size());
      b_boost.resize(size());

      get_equal_random_test_values_boost_and_local_n(a_local.data(), a_boost.data(), size());
      get_equal_random_test_values_boost_and_local_n(b_local.data(), b_boost.data(), size());
    }

    virtual bool test_binary_mul() const
    {
      bool result_is_ok = true;

      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const boost_uint_c_type c_boost =   boost_uint_c_type(a_boost[i])
                                            * b_boost[i];

          const local_uint_c_type c_local =   static_cast<local_uint_c_type>(a_local[i])
                                            * static_cast<local_uint_c_type>(b_local[i]);

          const std::string str_boost = hexlexical_cast(c_boost);
          const std::string str_local = hexlexical_cast(c_local);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost == str_local);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

  private:
    std::vector<local_uint_a_type> a_local;
    std::vector<local_uint_b_type> b_local;

    std::vector<boost_uint_a_type> a_boost;
    std::vector<boost_uint_b_type> b_boost;
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_MUL_N_BY_M_TEMPLATE_2019_12_26_H_

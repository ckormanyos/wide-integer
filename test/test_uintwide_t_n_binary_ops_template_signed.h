///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_TEMPLATE_SIGNED_2021_06_05_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_TEMPLATE_SIGNED_2021_06_05_H_

  #include <algorithm>
  #include <atomic>
  #include <cstddef>
  #include <random>
  #include <vector>

  #include <test/test_uintwide_t_n_binary_ops_base.h>

  template<const std::size_t MyDigits2,
           typename MyLimbType = std::uint32_t,
           typename AllocatorType = void>
  class test_uintwide_t_n_binary_ops_template_signed : public test_uintwide_t_n_binary_ops_base
  {
  private:
    static constexpr std::size_t digits2 = MyDigits2;

    using boost_uint_backend_type =
      boost::multiprecision::cpp_int_backend<digits2,
                                             digits2,
                                             boost::multiprecision::unsigned_magnitude>;
    using boost_sint_backend_type =
      boost::multiprecision::cpp_int_backend<digits2,
                                             digits2,
                                             boost::multiprecision::signed_magnitude>;

    using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type, boost::multiprecision::et_on>;
    using boost_sint_type = boost::multiprecision::number<boost_sint_backend_type, boost::multiprecision::et_on>;

    using local_limb_type = MyLimbType;

    using local_uint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, AllocatorType>;
    using local_sint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, AllocatorType, true>;

  public:
    test_uintwide_t_n_binary_ops_template_signed(const std::size_t count)
      : test_uintwide_t_n_binary_ops_base(count),
        a_local       (),
        b_local       (),
        a_local_signed(),
        b_local_signed(),
        a_boost       (),
        b_boost       (),
        a_boost_signed(),
        b_boost_signed() { }

    virtual ~test_uintwide_t_n_binary_ops_template_signed() = default;

    virtual std::size_t get_digits2() const { return digits2; }

    virtual void initialize()
    {
      a_local.clear();
      b_local.clear();
      a_local_signed.clear();
      b_local_signed.clear();

      a_boost.clear();
      b_boost.clear();
      a_boost_signed.clear();
      b_boost_signed.clear();

      a_local.resize(size());
      b_local.resize(size());
      a_local_signed.resize(size());
      b_local_signed.resize(size());

      a_boost.resize(size());
      b_boost.resize(size());
      a_boost_signed.resize(size());
      b_boost_signed.resize(size());

      get_equal_random_test_values_boost_and_local_n<local_uint_type, boost_uint_type, AllocatorType>(a_local.data(), a_boost.data(), size());
      get_equal_random_test_values_boost_and_local_n<local_uint_type, boost_uint_type, AllocatorType>(b_local.data(), b_boost.data(), size());

      std::copy(a_local.cbegin(), a_local.cend(), a_local_signed.begin());
      std::copy(b_local.cbegin(), b_local.cend(), b_local_signed.begin());

      std::copy(a_boost.cbegin(), a_boost.cend(), a_boost_signed.begin());
      std::copy(b_boost.cbegin(), b_boost.cend(), b_boost_signed.begin());
    }

    virtual bool test_binary_add() const
    {
      bool result_is_ok = true;

      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const boost_sint_type c_boost_signed = a_boost_signed[i] + b_boost_signed[i];
          const local_sint_type c_local_signed = a_local_signed[i] + b_local_signed[i];

          const std::string str_boost_signed = hexlexical_cast((boost_uint_type) c_boost_signed);
          const std::string str_local_signed = hexlexical_cast((local_uint_type) c_local_signed);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost_signed == str_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

    virtual bool test_binary_sub() const
    {
      bool result_is_ok = true;

      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const boost_sint_type c_boost_signed = a_boost_signed[i] - b_boost_signed[i];
          const local_sint_type c_local_signed = a_local_signed[i] - b_local_signed[i];

          const std::string str_boost_signed = hexlexical_cast((boost_uint_type) c_boost_signed);
          const std::string str_local_signed = hexlexical_cast((local_uint_type) c_local_signed);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost_signed == str_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
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
          const boost_sint_type c_boost_signed = a_boost_signed[i] * b_boost_signed[i];
          const local_sint_type c_local_signed = a_local_signed[i] * b_local_signed[i];

          const std::string str_boost_signed = hexlexical_cast((boost_uint_type) c_boost_signed);
          const std::string str_local_signed = hexlexical_cast((local_uint_type) c_local_signed);

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (str_boost_signed == str_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

    virtual bool test_binary_div() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

    virtual bool test_binary_mod() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

    virtual bool test_binary_sqrt() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

  private:
    std::vector<local_uint_type> a_local;
    std::vector<local_uint_type> b_local;
    std::vector<local_sint_type> a_local_signed;
    std::vector<local_sint_type> b_local_signed;

    std::vector<boost_uint_type> a_boost;
    std::vector<boost_uint_type> b_boost;
    std::vector<boost_sint_type> a_boost_signed;
    std::vector<boost_sint_type> b_boost_signed;
  };


  template<typename AllocatorType>
  class test_uintwide_t_n_binary_ops_template_signed<64U, std::uint16_t, AllocatorType>
    : public test_uintwide_t_n_binary_ops_base
  {
  private:
    static constexpr std::size_t digits2 = 64U;

    using native_uint_type = std::uint64_t;
    using native_sint_type = std::int64_t;

    using local_limb_type = std::uint16_t;

    using local_uint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, AllocatorType>;
    using local_sint_type = math::wide_integer::uintwide_t<digits2, local_limb_type, AllocatorType, true>;

  public:
    test_uintwide_t_n_binary_ops_template_signed(const std::size_t count)
      : test_uintwide_t_n_binary_ops_base(count),
        a_local_signed (),
        b_local_signed (),
        a_native_signed(),
        b_native_signed() { }

    virtual ~test_uintwide_t_n_binary_ops_template_signed() = default;

    virtual std::size_t get_digits2() const { return digits2; }

    virtual void initialize()
    {
      a_local_signed.clear();
      b_local_signed.clear();

      a_native_signed.clear();
      b_native_signed.clear();

      a_local_signed.resize(size());
      b_local_signed.resize(size());

      a_native_signed.resize(size());
      b_native_signed.resize(size());

      std::mt19937_64 eng64(std::clock());

      // Mantissa range from 10^15 ... 2^53-1
      std::uniform_int_distribution<std::uint64_t> dst_u64(UINT64_C(1), UINT64_C(0xFFFFFFFFFFFFFFFF));

      for(size_t i = 0U; i < size(); ++i)
      {
        a_native_signed[i] = (std::int64_t) dst_u64(eng64);
        b_native_signed[i] = (std::int64_t) dst_u64(eng64);

        a_local_signed[i] = local_sint_type(local_uint_type(a_native_signed[i]));
        b_local_signed[i] = local_sint_type(local_uint_type(b_native_signed[i]));
      }
    }

    virtual bool test_binary_add() const
    {
      bool result_is_ok = true;

      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const native_sint_type c_native_signed = a_native_signed[i] + b_native_signed[i];
          const local_sint_type  c_local_signed  = a_local_signed [i] + b_local_signed [i];

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (c_native_signed == (std::int64_t) c_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

    virtual bool test_binary_sub() const
    {
      bool result_is_ok = true;

      std::atomic_flag test_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        size(),
        [&test_lock, &result_is_ok, this](std::size_t i)
        {
          const native_sint_type c_native_signed = a_native_signed[i] - b_native_signed[i];
          const local_sint_type  c_local_signed  = a_local_signed [i] - b_local_signed [i];

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (c_native_signed == (std::int64_t) c_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
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
          const native_sint_type c_native_signed = a_native_signed[i] * b_native_signed[i];
          const local_sint_type  c_local_signed  = a_local_signed [i] * b_local_signed [i];

          while(test_lock.test_and_set()) { ; }
          result_is_ok &= (c_native_signed == (std::int64_t) c_local_signed);
          test_lock.clear();
        }
      );

      return result_is_ok;
    }

    virtual bool test_binary_div() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

    virtual bool test_binary_mod() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

    virtual bool test_binary_sqrt() const
    {
      bool result_is_ok = true;

      return result_is_ok;
    }

    virtual bool do_test(const std::size_t rounds)
    {
      bool result_is_ok = test_uintwide_t_n_binary_ops_base::do_test(rounds);

      return result_is_ok;
    }

  private:
    std::vector<local_sint_type> a_local_signed;
    std::vector<local_sint_type> b_local_signed;

    std::vector<native_sint_type> a_native_signed;
    std::vector<native_sint_type> b_native_signed;
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_TEMPLATE_SIGNED_2021_06_05_H_

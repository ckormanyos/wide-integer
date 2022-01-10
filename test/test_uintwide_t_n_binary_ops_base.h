///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H // NOLINT(llvm-header-guard)
  #define TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H

  #include <cstdint>
  #include <iomanip>
  #include <iostream>
  #include <random>

  #include <test/test_uintwide_t_n_base.h>

  class test_uintwide_t_n_binary_ops_base : public test_uintwide_t_n_base
  {
  public:
    explicit test_uintwide_t_n_binary_ops_base(const std::size_t count)
      : test_uintwide_t_n_base(count) { }

    test_uintwide_t_n_binary_ops_base() = delete;

    test_uintwide_t_n_binary_ops_base(const test_uintwide_t_n_binary_ops_base&)  = delete;
    test_uintwide_t_n_binary_ops_base(      test_uintwide_t_n_binary_ops_base&&) = delete;

    auto operator=(const test_uintwide_t_n_binary_ops_base&)  -> test_uintwide_t_n_binary_ops_base& = delete;
    auto operator=(      test_uintwide_t_n_binary_ops_base&&) -> test_uintwide_t_n_binary_ops_base& = delete;

    ~test_uintwide_t_n_binary_ops_base() override = default;

    virtual auto test_binary_add () const -> bool { return false; }
    virtual auto test_binary_sub () const -> bool { return false; }
    virtual auto test_binary_mul () const -> bool { return false; }
    virtual auto test_binary_div () const -> bool { return false; }
    virtual auto test_binary_mod () const -> bool { return false; }
    virtual auto test_binary_sqrt() const -> bool { return false; }

    virtual auto do_test(const std::size_t rounds) -> bool
    {
      bool result_is_ok = true;

      for(std::size_t i = 0U; i < rounds; ++i)
      {
        std::cout << "initialize()       boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        this->initialize();

        std::cout << "test_binary_add()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_add();

        std::cout << "test_binary_sub()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_sub();

        std::cout << "test_binary_mul()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_mul();

        std::cout << "test_binary_div()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_div();

        std::cout << "test_binary_mod()  boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_mod();

        std::cout << "test_binary_sqrt() boost compare with uintwide_t: round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_sqrt();
      }

      return result_is_ok;
    }

  protected:
    using random_generator_type = std::mersenne_twister_engine<std::uint32_t,
                                                               32,
                                                               624,
                                                               397,
                                                               31,
                                                               UINT32_C(0x9908B0DF),
                                                               11,
                                                               UINT32_C(0xFFFFFFFF),
                                                               7,
                                                               UINT32_C(0x9D2C5680),
                                                               15,
                                                               UINT32_C(0xEFC60000),
                                                               18,
                                                               UINT32_C(1812433253)>;

    static auto my_rnd() -> std::random_device&;
    static auto my_gen() -> random_generator_type&;
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H

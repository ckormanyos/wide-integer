///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

  #include <cstdint>
  #include <iomanip>
  #include <iostream>
  #include <random>

  #include <test/test_uintwide_t_n_base.h>

  class test_uintwide_t_n_binary_ops_base : public test_uintwide_t_n_base
  {
  public:
    test_uintwide_t_n_binary_ops_base(const std::size_t count)
      : test_uintwide_t_n_base(count) { }

    virtual ~test_uintwide_t_n_binary_ops_base() = default;

    virtual bool test_binary_add () const { return false; }
    virtual bool test_binary_sub () const { return false; }
    virtual bool test_binary_mul () const { return false; }
    virtual bool test_binary_div () const { return false; }
    virtual bool test_binary_mod () const { return false; }
    virtual bool test_binary_sqrt() const { return false; }

    virtual bool do_test(const std::size_t rounds)
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

    static std::random_device    my_rnd;
    static random_generator_type my_gen;
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

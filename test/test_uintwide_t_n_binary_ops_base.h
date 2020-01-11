#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

  #include <iomanip>
  #include <iostream>

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
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

  #include <iomanip>
  #include <sstream>
  #include <string>

  #include <boost/noncopyable.hpp>

  class test_uintwide_t_n_binary_ops_base : private boost::noncopyable
  {
  public:
    virtual ~test_uintwide_t_n_binary_ops_base() = default;

    virtual std::size_t get_digits2() const = 0;

    virtual void initialize      () = 0;
    virtual bool test_binary_add () const = 0;
    virtual bool test_binary_sub () const = 0;
    virtual bool test_binary_mul () const = 0;
    virtual bool test_binary_div () const = 0;
    virtual bool test_binary_sqrt() const = 0;

    bool do_test(const std::size_t rounds)
    {
      bool result_is_ok = true;

      for(std::size_t i = 0U; i < rounds; ++i)
      {
        std::cout << "initialize()      : round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        this->initialize();

        std::cout << "test_binary_add() : round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_add();

        std::cout << "test_binary_sub() : round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_sub();

        std::cout << "test_binary_mul() : round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_mul();

        std::cout << "test_binary_div() : round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_div();

        std::cout << "test_binary_sqrt(): round " << i << ",  digits2: " << this->get_digits2() << std::endl;
        result_is_ok &= this->test_binary_sqrt();
      }

      return result_is_ok;
    }

  protected:
    test_uintwide_t_n_binary_ops_base() = default;

    template<typename UnsignedIntegralType>
    static std::string hexlexical_cast(const UnsignedIntegralType& u)
    {
      std::stringstream ss;

      ss << std::hex << u;

      return ss.str();
    }
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

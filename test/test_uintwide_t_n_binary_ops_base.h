#ifndef TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_
  #define TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

  #include <ctime>
  #include <iomanip>
  #include <iostream>
  #include <sstream>

  #include <boost/multiprecision/cpp_int.hpp>
  #include <boost/noncopyable.hpp>

  #include <wide_integer/generic_template_uintwide_t.h>
  #include <test/parallel_for.h>

  class test_uintwide_t_n_binary_ops_base : private boost::noncopyable
  {
  public:
    virtual ~test_uintwide_t_n_binary_ops_base() = default;

    virtual std::size_t get_digits2() const = 0;

    virtual void initialize      () = 0;
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
    test_uintwide_t_n_binary_ops_base() = default;

    template<typename UnsignedIntegralType>
    static std::string hexlexical_cast(const UnsignedIntegralType& u)
    {
      std::stringstream ss;

      ss << std::hex << u;

      return ss.str();
    }

    template<typename OtherLocalUintType,
             typename OtherBoostUintType>
    static void get_equal_random_test_values_boost_and_local_n(OtherLocalUintType* u_local,
                                                               OtherBoostUintType* u_boost,
                                                               const std::size_t count)
    {
      using other_local_uint_type = OtherLocalUintType;
      using other_boost_uint_type = OtherBoostUintType;

      using random_engine_type =
        wide_integer::generic_template::default_random_engine<other_local_uint_type::my_digits,
                                                              typename other_local_uint_type::value_type>;

      random_engine_type random_generator(std::clock());

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        count,
        [&random_generator, &u_local, &u_boost](std::size_t i)
        {
          const other_local_uint_type a = random_generator();

          u_local[i] = a;
          u_boost[i] = other_boost_uint_type("0x" + hexlexical_cast(a));
        }
      );
    }
  };

#endif // TEST_UINTWIDE_T_N_BINARY_OPS_BASE_2019_12_19_H_

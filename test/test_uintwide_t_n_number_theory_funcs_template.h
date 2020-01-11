#ifndef TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_
  #define TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_

  #include <test/test_uintwide_t_n_base.h>

  template<const std::size_t MyDigits2,
           typename MyLimbType = std::uint32_t>
  class test_uintwide_t_n_number_theory_funcs_template : public test_uintwide_t_n_base
  {
  public:
    static constexpr std::size_t digits2 = MyDigits2;

    test_uintwide_t_n_number_theory_funcs_template(const std::size_t count)
      : test_uintwide_t_n_base(count) { }

    virtual ~test_uintwide_t_n_number_theory_funcs_template() = default;

    virtual std::size_t get_digits2() const { return digits2; }

    virtual void initialize() { }
  };

#endif // TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_  #include <test/test_uintwide_t_n_binary_ops_base.h>

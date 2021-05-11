///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_
  #define TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_

  #include <test/test_uintwide_t_n_base.h>

  template<const math::wide_integer::size_t MyWidth2,
           typename MyLimbType = std::uint32_t>
  class test_uintwide_t_n_number_theory_funcs_template : public test_uintwide_t_n_base
  {
  public:
    static constexpr math::wide_integer::size_t digits2 = MyWidth2;

    test_uintwide_t_n_number_theory_funcs_template(const std::size_t count)
      : test_uintwide_t_n_base(count) { }

    virtual ~test_uintwide_t_n_number_theory_funcs_template() = default;

    virtual math::wide_integer::size_t get_digits2() const { return digits2; }

    virtual void initialize() { }
  };

#endif // TEST_UINTWIDE_T_N_NUMBER_THEORY_FUNCS_TEMPLATE_2019_12_29_H_  #include <test/test_uintwide_t_n_binary_ops_base.h>

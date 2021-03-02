///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <test/test_uintwide_t_n_binary_ops_base.h>

std::random_device test_uintwide_t_n_binary_ops_base::my_rnd;

test_uintwide_t_n_binary_ops_base::random_generator_type test_uintwide_t_n_binary_ops_base::my_gen(my_rnd());

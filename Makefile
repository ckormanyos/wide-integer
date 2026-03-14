###############################################################################
#  Copyright Christopher Kormanyos 2026.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# local machine
# make MY_CC=g++ MY_BOOST_ROOT=/mnt/c/boost/boost_1_90_0 all

# MacOS with brew llvm
# make MY_CC=/opt/homebrew/opt/llvm/bin/clang++ MY_BOOST_ROOT=../boost-root MY_STD=c++23 MY_BREW=brew all

all : compile_and_link


BOOST_ROOT   := ../boost-root
CC           := clang++
STD          := c++20


ifneq ($(MY_BOOST_ROOT),)
BOOST_ROOT   := $(MY_BOOST_ROOT)
endif

ifneq ($(MY_CC),)
CC           := $(MY_CC)
endif

ifneq ($(MY_STD),)
STD          := $(MY_STD)
endif

ECHO         := echo


FILES_SRC    := test/test.cpp                                       \
                test/test_uintwide_t_boost_backend.cpp              \
                test/test_uintwide_t_edge_cases.cpp                 \
                test/test_uintwide_t_examples.cpp                   \
                test/test_uintwide_t_float_convert.cpp              \
                test/test_uintwide_t_int_convert.cpp                \
                test/test_uintwide_t_n_base.cpp                     \
                test/test_uintwide_t_n_binary_ops_base.cpp          \
                test/test_uintwide_t_spot_values.cpp                \
                examples/example000a_builtin_convert.cpp            \
                examples/example000_numeric_limits.cpp              \
                examples/example001_mul_div.cpp                     \
                examples/example001a_div_mod.cpp                    \
                examples/example002_shl_shr.cpp                     \
                examples/example003_sqrt.cpp                        \
                examples/example003a_cbrt.cpp                       \
                examples/example004_rootk_pow.cpp                   \
                examples/example005_powm.cpp                        \
                examples/example005a_pow_factors_of_p99.cpp         \
                examples/example006_gcd.cpp                         \
                examples/example007_random_generator.cpp            \
                examples/example008_miller_rabin_prime.cpp          \
                examples/example008a_miller_rabin_prime.cpp         \
                examples/example009_timed_mul.cpp                   \
                examples/example009a_timed_mul_4_by_4.cpp           \
                examples/example009b_timed_mul_8_by_8.cpp           \
                examples/example010_uint48_t.cpp                    \
                examples/example011_uint24_t.cpp                    \
                examples/example012_rsa_crypto.cpp                  \
                examples/example013_ecdsa_sign_verify.cpp           \
                examples/example014_pi_spigot_wide.cpp


CPPFLAGS     := -std=$(STD)                                         \
                -finline-functions                                  \
                -march=native                                       \
                -mtune=native                                       \
                -O3                                                 \
                -Werror                                             \
                -Wall                                               \
                -Wextra                                             \
                -Wpedantic                                          \
                -Wconversion                                        \
                -Wsign-conversion                                   \
                -Wshadow                                            \
                -Wundef                                             \
                -Wunused-parameter                                  \
                -Wuninitialized                                     \
                -Wunreachable-code                                  \
                -Winit-self                                         \
                -Wzero-as-null-pointer-constant


C_DEFINES    := -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64                 \
                -DWIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL


C_INCLUDES   := -I.                                                 \
                -I$(BOOST_ROOT)


ifeq ($(MY_BREW),brew)
C_INCLUDES   += -isystem /opt/homebrew/opt/llvm/include
C_INCLUDES   += -isystem $$(xcrun --show-sdk-path)
endif


LDFLAGS      := -pthread                                            \
                -lpthread


ifeq ($(MY_BREW),brew)
LDFLAGS      += -L/opt/homebrew/opt/llvm/lib
endif


compile_and_link :
	@-$(ECHO) +++ compiling and linking to wide_integer
	@-$(ECHO)
	@-$(CC) $(CPPFLAGS) $(C_INCLUDES) $(LDFLAGS) $(FILES_SRC) -o wide_integer
	@-$(ECHO)

find_package(Boost REQUIRED)
add_library(Examples
  example000_numeric_limits.cpp
  example000a_builtin_convert.cpp
  example001_mul_div.cpp
  example001a_div_mod.cpp
  example002_shl_shr.cpp
  example003_sqrt.cpp
  example003a_cbrt.cpp
  example004_rootk_pow.cpp
  example005_powm.cpp
  example006_gcd.cpp
  example007_random_generator.cpp
  example008_miller_rabin_prime.cpp
  example008a_miller_rabin_prime.cpp
  example009_timed_mul.cpp
  example009a_timed_mul_4_by_4.cpp
  example009b_timed_mul_8_by_8.cpp
  example010_uint48_t.cpp
  example011_uint24_t.cpp)
target_compile_features(Examples PRIVATE cxx_std_11)
target_include_directories(Examples PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(Examples SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

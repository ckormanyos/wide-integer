Wide-integer
[![Build Status](https://github.com/ckormanyos/wide-integer/actions/workflows/wide_integer.yml/badge.svg)](https://github.com/ckormanyos/wide-integer/actions)
==================

Wide-integer implements a generic C++ template for extended width unsigned integral types.

This C++ template header-only library implements drop-in big integer types
such as `uint128_t`, `uint256_t`, `uint384_t`, `uint512_t`, `uint1024_t`, `uint1536_t`, etc.
These can be used essentially like regular built-in integers.

Wide-integer supports unsigned integral types having bit counts
of <img src="https://render.githubusercontent.com/render/math?math=1{\ldots}63{\times}2^{N}">
while being 16, 24, 32 or larger.
In addition, small integer types such as software synthesized versions
of `uint24_t` or `uint48_t` can also be crafted with wide-integer.

Wide-integer also features basic realizations of several
elementary and number theoretical functions such as root finding,
random distribution, Miller-Rabin primality testing,
greatest common denominator (GCD) and more.

Inclusion of a single C++11 header file (plus one additional
utility header file) is all that is needed for using wide-integer,
as shown in the [examples](./examples).

## Implementation goals

  - Relatively wide precision range from 24, 32, 64 bits up to a few tens of thousands of bits
  - Moderately good efficiency over the entire wide precision range
  - Clean header-only C++11 design
  - Seamless portability to any modern C++11, 14, 17, 20 compiler
  - Scalability with small memory footprint and efficiency suitable for both PC/workstation systems as well as _bare-metal_ embedded systems
  - Support `constexpr`-ness for construction, binary arithmetic operations and some rudimentary functions provided C++14 or higher is being used to compile.

## Quick start
Easy application follows via a traditional C-style typedef or C++11 alias.
The defined type can be used very much like a built-in unsinged integral type.
In the following example, the static `uint512_t` variable `x` is initialized
with unsigned value `3U`.

In particular,

```
#include <math/wide_integer/uintwide_t.h>

using uint512_t = math::wide_integer::uintwide_t<512U, std::uint32_t>;

static uint512_t x = 3U;
```

The code sequence above defines the local data type `uint512_t` with
a C++11 alias. The first template parameter `512U` sets the binary digit
count while the second optional template parameter `std::uint32_t`
sets the internal _limb_ _type_. If the second template parameter is left blank,
the default limb type is 32 bits in width and unsigned.

`uintwide_t` also has a third optional template paramter that
can be used to set the allocator type for internal storage of the
big integer type. This optional parameter can help to reduce
stack consumption, especially when using higher digit counts.
If left blank, the default allocator type is `void`
and stack allocation is used with an `array`-like
internal representation.

## Examples

Various interesting and algorithmically challenging
[examples](./examples) have been implemented.
It is hoped that the examples provide inspiration and guidance on
how to use wide-integer.

  - ![`example001_mul_div.cpp`](./examples/example001_mul_div.cpp) performs multiplication and division.
  - ![`example001a_div_mod.cpp`](./examples/example001a_div_mod.cpp) exercises division and modulus calculations.
  - ![`example002_shl_shr.cpp`](./examples/example002_shl_shr.cpp) does a few left and right shift operations.
  - ![`example003_sqrt.cpp`](./examples/example003_sqrt.cpp) computes a square root.
  - ![`example003a_cbrt`](./examples/example003a_cbrt.cpp) computes a cube root.
  - ![`example004_rootk_pow.cpp`](./examples/example004_rootk_pow.cpp) computes an integral seventh root and its corresponding power.
  - ![`example005_powm.cpp`](./examples/example005_powm.cpp) tests the power-modulus function.
  - ![`example006_gcd.cpp`](./examples/example006_gcd.cpp) tests the computation of a greatest common divisor.
  - ![`example007_random_generator.cpp`](./examples/example007_random_generator.cpp) computes some large pseudo-random integers.
  - ![`example008_miller_rabin_prime.cpp`](./examples/example008_miller_rabin_prime.cpp) implements primality testing via Miller-Rabin.
  - ![`example008a_miller_rabin_prime.cpp`](./examples/example008a_miller_rabin_prime.cpp) tests Boost interaction with Miller-Rabin primality checks.
  - ![`example009_timed_mul.cpp`](./examples/example009_timed_mul.cpp) measures multiplication timings.
  - ![`example009a_timed_mul_4_by_4.cpp`](./examples/example009a_timed_mul_4_by_4.cpp) also measures multiplication timings for the special case of wide integers having 4 limbs.
  - ![`example009b_timed_mul_8_by_8.cpp`](./examples/example009b_timed_mul_8_by_8.cpp) yet again measures multiplication timings for the special case of wide integers having 8 limbs.
  - ![`example010_uint48_t.cpp`](./examples/example010_uint48_t.cpp) verifies 48-bit integer caluclations.
  - ![`example011_uint24_t.cpp`](./examples/example011_uint24_t.cpp) performs calculations with 24-bits, which is definitely on the small side of the range of wide-integer.

## Building, testing and CI

### Build Status
[![Build Status](https://github.com/ckormanyos/wide-integer/actions/workflows/wide_integer.yml/badge.svg)](https://github.com/ckormanyos/wide-integer/actions)

Building and running the tests can be accomplished using the provided Microsoft VisualStudio solution workspace.

You can also build and run tests from an empty directory using CMake:

```sh
cmake /path/to/wide-integer
cmake --build .
ctest --verbose
```

Alternatively building with native GCC (i.e., on *nix) can be executed with a simple command line.
Consider, for instance, building in Linux with GCC in the presence of `unsigned __int128`.
Boost is used for some examples and tests.
In this build example, Boost intended to be located in the made-up directory `../boost-root`,
which needs to be adapted according to the actual location of Boost.

```
cd wide_integer
g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wno-maybe-uninitialized -Wno-cast-function-type -std=gnu++11 -DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64 -I. -I../boost-root -pthread -lpthread  test/test.cpp test/test_uintwide_t_boost_backend.cpp test/test_uintwide_t_edge_cases.cpp test/test_uintwide_t_examples.cpp test/test_uintwide_t_n_base.cpp test/test_uintwide_t_n_binary_ops_base.cpp test/test_uintwide_t_spot_values.cpp examples/example001a_div_mod.cpp examples/example001_mul_div.cpp examples/example002_shl_shr.cpp examples/example003a_cbrt.cpp examples/example003_sqrt.cpp examples/example004_rootk_pow.cpp examples/example005_powm.cpp examples/example006_gcd.cpp examples/example007_random_generator.cpp examples/example008_miller_rabin_prime.cpp examples/example008a_miller_rabin_prime.cpp examples/example009_timed_mul.cpp examples/example009a_timed_mul_4_by_4.cpp examples/example009b_timed_mul_8_by_8.cpp examples/example010_uint48_t.cpp examples/example011_uint24_t.cpp -o wide_integer.exe
```


Testing is a big issue and a growing test suite is in continued progress
providing for tested, efficient functionality on the PC and workstation.
The GitHub code is delivered with an affiliated MSVC project that uses easy-to-understand
subroutines called from `main()` that exercise various test cases.

Continuous integration runs on push using GitHub Actions.
Various compilers, operating systems, and C++ standards
ranging from C++11, 14, 17, 20 are included in CI.

## Additional details

Wide-Integer has been tested with numerous compilers, for target systems ranging from 8 to 64 bits.
The library is specifically designed for efficiency with small to medium bit counts.
Supported bit counts include integers
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}63{\times}2^{N}">
while being 16, 24, 32 or larger such as 256, 384, 512, 768, 1024,
or other less common bit counts such as 11,264, etc.

Small, medium and large bit counts are supported.
Common applications might use the range of `uint128_t`, `uint256_t` or `uint512_t`.
It is also possible to make
software-synthesized (not very efficient) versions of `uint24_t`, `uint32_t` or `uint48_t`,
which might useful for hardware prototyping or other simulation and verification needs.
On the high-digit end, Karatsuba multiplication extends the high performance range
to many thousands of bits. Fast long division, however, relies on a classical algorithm
and sub-quadratic high-precision division is not yet implemented.

Portability of the code is another key point of focus. Special care
has been taken to test in certain high-performance embedded real-time
programming environments.

### Compiler switches

Various configuration features can optionally be
enabled or disabled with the compiler switches:

```
#define WIDE_INTEGER_DISABLE_IOSTREAM
#define WIDE_INTEGER_HAS_LIMB_TYPE_UINT64
#define WIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL
```

When working with even the most tiny microcontroller systems,
I/O streaming can optionally be disabled with the compiler switch:

```
#define WIDE_INTEGER_DISABLE_IOSTREAM
```

When working on high-performance systems having `unsigned __int128`
(an extended-width, yet non-standard data type),
a 64-bit limb of type `uint64_t` can be used.
Enable the 64-bit limb type on such systems
with the compiler switch:

```
#define WIDE_INTEGER_HAS_LIMB_TYPE_UINT64
```

or (when using GCC, clang or similar) on the compiler
command line with:

```
-DWIDE_INTEGER_HAS_LIMB_TYPE_UINT64
```

This macro is disabled by default.

The example below, for instance, uses a 64-bit limb type
on GCC or clang.

```
#define WIDE_INTEGER_HAS_LIMB_TYPE_UINT64

#include <math/wide_integer/uintwide_t.h>

using uint_fast256_t = math::wide_integer::uintwide_t<256U, std::uint64_t>;

static uint_fast256_t x = 42U;
```

Another potential optimization macro can be activated with

```
#define WIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL
```

This macro might improve performance on some target/compiler systems
by manually unrolling the multiplication loop(s) for
`uintwide_t` instances having 8 limbs. This macro is disabled
by default.

### C++14, 17, 20 `constexpr` support

When using C++20 `uintwide_t` supports compile-time
`constexpr` construction and evaluation of results
of binary arithmetic, comparison operators
and various elementary functions.
The following code, for instance, shows a compile-time instantiation
of `uintwide_t` and subsequent `constexpr` evaluations
of binary operations multiply, divide and comparison.
(See also the examples for additional use cases).

```
#include <math/wide_integer/uintwide_t.h>

// Use a C++20 compiler for this example.
using uint256_t = math::wide_integer::uintwide_t<256U>;

constexpr uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
constexpr uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

constexpr uint256_t c = (a * b);
constexpr uint256_t d = (a / b);

constexpr bool result_is_ok = (   (c == "0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076")
                               && (std::uint_fast8_t(d) == 10U));

static_assert(result_is_ok == true, "Error: example is not OK!");
```

`constexpr`-ness has been checked on GCC 10, clang 10
(with `-std=c++20`) and VC 14.2 (with `/std:c++latest`),
also for various embedded compilers such as `avr-gcc` 10,
`arm-non-eabi-gcc` 10, and more. Less modern compiler versions,
some with standards such as C++14, 17, 2a have also been checked
for `constexpr` usage of `uintwide_t`. If you have an older
compiler, you might have to check compiler
for availability of `constexpr` with wide_integer.

If a fully compliant C++20 compiler is not available,
the preprocessor symbols below can be useful.
These symbols are defined or set by the wide_integer library.

```
WIDE_INTEGER_CONSTEXPR
WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST
```

The preprocessor symbol `WIDE_INTEGER_CONSTEXPR` acts as either
a synonym for `constexpr` or expands to nothing depending on
whether the availability of `constexpr` support has been automatically
detected or not.
The preprocessor symbol `WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST`
has the value of 0 or 1, where 1 indicates that `uintwide_t`
values qualified with `WIDE_INTEGER_CONSTEXPR` are actually
compile-time constant (i.e., `constexpr`).

## Detailed Examples

We will now present various straightforward detailed examples.

The code below performs some elementary algebraic calculations
with a 256-bit unsigned integral type.

```
#include <iomanip>
#include <iostream>

#include <math/wide_integer/uintwide_t.h>

int main()
{
  using uint256_t = math::wide_integer::uint256_t;

  // Construction from string.
  // Other constructors are available from built-in types.

  const uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  const uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

  // Elementary arithmetic operations.
  const uint256_t c = (a * b);
  const uint256_t d = (a / b);

  // Logical comparison.
  const bool result_is_ok = (   (c == "0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076")
                             && (d == "0xA"));

  // Print the hexadecimal representation string output.

  std::cout << "0x" << std::hex << std::uppercase << c << std::endl;
  std::cout << "0x" << std::hex << std::uppercase << d << std::endl;

  // Visualize if the result is OK.

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

Wide-integer also supports a small selection of number-theoretical
functions such as least and most significant bit, square root,
_k_'th root, power, power-modulus, greatest common denominator
and random number generation. Most of these functions can be found via ADL.

The example below calculates an integer square root.

```C
#include <iomanip>
#include <iostream>

#include <math/wide_integer/uintwide_t.h>

int main()
{
  using uint256_t = math::wide_integer::uint256_t;

  const uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");

  const uint256_t s = sqrt(a);

  const bool result_is_ok =
    (s == "0xFA5FE7853F1D4AD92BDF244179CA178B");

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

The following sample performs add, subtract, multiply and divide of `uint48_t`.

```
#include <iomanip>
#include <iostream>

#include <math/wide_integer/uintwide_t.h>

int main()
{
  using uint48_t = math::wide_integer::uintwide_t<48U, std::uint8_t>;

  using distribution_type  = math::wide_integer::uniform_int_distribution<48U, std::uint8_t>;
  using random_engine_type = math::wide_integer::default_random_engine   <48U, std::uint8_t>;

  random_engine_type generator(0xF00DCAFEULL);

  distribution_type distribution;

  const std::uint64_t a64 = static_cast<std::uint64_t>(distribution(generator));
  const std::uint64_t b64 = static_cast<std::uint64_t>(distribution(generator));

  const uint48_t a(a64);
  const uint48_t b(b64);

  const uint48_t c_add = (a + b);
  const uint48_t c_sub = (a - b);
  const uint48_t c_mul = (a * b);
  const uint48_t c_div = (a / b);

  const bool result_is_ok = (   (c_add == ((a64 + b64) & 0x0000FFFFFFFFFFFFULL))
                             && (c_sub == ((a64 - b64) & 0x0000FFFFFFFFFFFFULL))
                             && (c_mul == ((a64 * b64) & 0x0000FFFFFFFFFFFFULL))
                             && (c_div == ((a64 / b64) & 0x0000FFFFFFFFFFFFULL)));

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

The next example computes the real-valued cube root of
<img src="https://render.githubusercontent.com/render/math?math=10^{3,333}">.
The real-valued cube root of this very large unsigned integer is
<img src="https://render.githubusercontent.com/render/math?math=10^{1,111}">.
We will use the (somewhat uncommon) integral data type `uint11264_t`.
Since `uint11264_t` has approximately 3,390 decimal digits of precision,
it is large enough to hold the value of
<img src="https://render.githubusercontent.com/render/math?math=10^{3,333}">
prior to (and following) the cube root operation.

```C
#include <iomanip>
#include <iostream>

#include <math/wide_integer/uintwide_t.h>

int main()
{
  using uint11264_t = math::wide_integer::uintwide_t<11264U, std::uint32_t>;

  // Create the string '1' + 3,333 times '0', which is
  // equivalent to the decimal integral value 10^3333.
  std::array<char, 3335U> str_a;

  std::fill(str_a.begin() + 1U,
            str_a.begin() + 1U + 3333U,
            '0');

  str_a.front() = '1';
  str_a.back()  = '\0';

  std::array<char, 1113U> str_control;

  const uint11264_t a = str_a.data();

  const uint11264_t s = cbrt(a);

  // Create the string '1' + 1,111 times '0', which is
  // equivalent to the decimal integral value 10^1111.
  // (This is the cube root of 10^3333.)
  std::fill(str_control.begin() + 1U,
            str_control.begin() + 1U + 1111U,
            '0');

  str_control.front() = '1';
  str_control.back()  = '\0';

  const bool result_is_ok = (s == str_control.data());

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

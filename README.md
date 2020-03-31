# Wide-integer
Wide-integer implements a generic C++ template for extended precision unsigned integral types.

This C++ template header-only library implements drop-in big integer types such as `uint128_t`, `uint256_t`, `uint384_t`, `uint512_t`, `uint1024_t`, `uint1536_t`, etc., that can be used essentially like regular built-in integers. Wide-integer supports unsigned integral types having bit counts of <img src="https://render.githubusercontent.com/render/math?math=1{\ldots}63{\times}2^{N}"> while being 16, 24, 32 or larger. In addition, small integer types such as software synthesized versoins of `uint24_t` or `uint48_t` can be realized with wide-integer.

Wide-integer also features elementary realizations of several number theoretical functions such as root finding, basic random distribution, Miller-Rabin primality testing and greatest common denominator (GCD).

Inclusion of a single C++11 header file is all that is needed.

# Details
Wide-Integer has been tested with numerous compilers, for target systems ranging from 8 to 64 bits.
The library is specifically designed for efficiency with small to medium bit counts.
Supported bit counts include integers
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}63{\times}2^{N}">
while being 16, 24, 32 or larger such as 256, 384, 512, 768, 1024,
or other less common bit counts such as 11,264, etc.
Also smaller and/or larger bit counts are supported. It is even possible to make
software-synthesized (not very efficient) versions of `uint24_t`, `uint32_t` or `uint48_t`,
which might useful for hardware prototyping or other simulation and verification needs.
On the high-digit end, Karatsuba multiplication extends the high performance range
to thousands of bits. Fast long division, however, relies on a classical algorithm
and sub-quadratic high-precision division is not yet implemented.

Portability of the code is another key point of focus. Special care
has been taken to test in certain high-performance embedded real-time
programming environments.

Testing is a big issue. Generating a full test suite is in continued progress
and tested efficient functionality on the PC and workstation is present.
The code is delivered with an affiliated MSVC project that uses Boost.Test
for various test cases.

When working with even the most tiny microcontroller systems, I/O streaming
can optionally be disabled with the `WIDE_INTEGER_DISABLE_IOSTREAM` compiler switch.
See the examples directory as more use cases are being created.

# Quick start
Easy application follows via a traditional C-style typedef or C++11 alias.
The defined type can be used very much like a built-in unsinged integral type.

For instance,

```C
#include "generic_template_uintwide_t.h"

using uint512_t = wide_integer::generic_template::uintwide_t<512U, std::uint32_t>;

static uint512_t x = 3U;
```

The code sequence above defines the local data type `uint512_t` with
a C++11 alias. The first template parameter `512U` sets the binary digit
count while the second optional template parameter `std::uint32_t`
sets the internal _limb_ _type_. If the second template parameter is left blank,
the default limb type is 32 bits in width and unsigned.
The static `uint512_t` variable `x` is set to 3.

# Detailed examples

```C
#include <iomanip>
#include <iostream>

#include "generic_template_uintwide_t.h"

int main()
{
  using uint256_t = wide_integer::generic_template::uint256_t;

  // Construction from string. Other constructors are available from built-in types.
  const uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  const uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

  // Elementary arithmetic operations.
  const uint256_t c = (a * b);
  const uint256_t d = (a / b);

  // Logical comparison.
  const bool result_is_ok = (   (c == "0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076")
                             && (d == "0xA"));

  // String output.
  std::cout << std::hex << std::uppercase << c << std::endl;
  std::cout << std::hex << std::uppercase << d << std::endl;

  // Visualize the result.
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

#include "generic_template_uintwide_t.h"

int main()
{
  using uint256_t = wide_integer::generic_template::uint256_t;

  const uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");

  const uint256_t s = sqrt(a);

  const bool result_is_ok =
    (s == "0xFA5FE7853F1D4AD92BDF244179CA178B");

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

The following code performs add, subtract, multiply and divide of `uint48_t`.

```C
#include <iomanip>
#include <iostream>

#include "generic_template_uintwide_t.h"

int main()
{
  using uint48_t = wide_integer::generic_template::uintwide_t<48U, std::uint8_t>;

  using distribution_type  = wide_integer::generic_template::uniform_int_distribution<48U, std::uint8_t>;
  using random_engine_type = wide_integer::generic_template::default_random_engine   <48U, std::uint8_t>;

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

The next sample computes the real-valued cube root of
<img src="https://render.githubusercontent.com/render/math?math=10^{3,333}">.
The real-valued cube root of this very large unsigned integer is
<img src="https://render.githubusercontent.com/render/math?math=10^{1,111}">.
We will use the (somewhat uncommon) integral data type `uint11264_t`.
Since `uint11520_t` has approximately 3,390 decimal digits of precision,
it is large enough to hold the value of
<img src="https://render.githubusercontent.com/render/math?math=10^{3,333}">
prior to (and following) the cube root operation.

```C
#include <iomanip>
#include <iostream>

#include "generic_template_uintwide_t.h"

int main()
{
  using uint11264_t = wide_integer::generic_template::uintwide_t<11264U, std::uint32_t>;

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

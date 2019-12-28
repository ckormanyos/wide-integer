# wide-integer
wide-integer implements a generic C++ template for extended precision unsigned integral types auch as `uint128_t`, `uint256_t`, `uint512_t`, `uint1024_t`, etc. At the moment, wide-integer supports unsigned integral types having bit counts of `2^n` times `1`, `2`, `3`, `5`, and `7`, and also greater than or equal to 16 or 24.

Inclusion of a single C++11 header file is all that is needed.

# Details
Wide-Integer has been tested on numerous compilers and is specifically designed for efficiency with small to medium bit counts. Supported bit counts include integers `2^n` times `1`, `2`, `3`, `5`, and `7` such as 256, 320, 384, 448, 512, 640, 768, 896, 1024, 1280, 1536, etc. Also smaller and larger bit counts are supported. It is even possible to make (not very efficient) version of `uint48_t` if this may be useful for hardware prototyping or other simulation verification needs. On the high-digit end, Karatsuba multiplication extends the high performance range to thousands of bits. Fast long division, however, relies on a classical algorithm and sub-quadratic high-precision division is not yet implemented.

Portability of the code is another key point of focus. Special care has been taken to test in certain high-performance embedded real-time programming environments. Tested efficient functionality on the PC and workstation is also present.

When working with even the most tiny microcontroller systems, I/O streaming can optionally be disabled with the `WIDE_INTEGER_DISABLE_IOSTREAM` compiler switch. See the examples directory as more use cases are being created.

Easy application follows via a typedef or alias. The defined type can be used very much like a built-in unsinged integral type.

# Examples

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

Wide-integer also supports a small selection of number-theoretical functions such as least and most significant bit, square root, k'th root, power, power-modulus, greatest common denominator and random number generation. Most of these functions can be found via ADL.

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

The next sample computes the cube root of <img src="https://render.githubusercontent.com/render/math?math=10^{3,333}">. The cube root of this very large unsigned integer is <img src="https://render.githubusercontent.com/render/math?math=10^{1,111}">. We will use the (somewhat uncommon) integral data type `uint11520_t`. Since `uint11520_t` has 3,467 decimal digits of precision, so it is large enough to hold the value of <img src="https://render.githubusercontent.com/render/math?math=10^{3,333}"> prior to the cube root operation.

```C
#include <iomanip>
#include <iostream>

#include "generic_template_uintwide_t.h"

int main()
{
  using uint11520_t = wide_integer::generic_template::uintwide_t<11520U, std::uint32_t>;

  // Create the string '1' + 3,333 times '0', which is
  // equivalent to the decimal integral value 10^3333.
  std::array<char, 3335U> str_a;

  std::fill(str_a.begin() + 1U,
            str_a.begin() + 1U + 3333U,
            '0');

  str_a.front() = '1';
  str_a.back()  = '\0';

  std::array<char, 1113U> str_control;

  const uint11520_t a = str_a.data();

  const uint11520_t s = cbrt(a);

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

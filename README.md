# wide-integer
wide-Integer implements a generic C++ template for uint128_t, uint256_t, uint512_t, uint1024_t, etc. At the moment, wide-integer is limited to unsigned integral types having bit counts that are powers of 2 greater than or equal to 128.

Inclusion of a single C++11 header file is all that is needed.

Wide-Integer has been tested on numerous compilers and is specifically designed for efficiency with small to medium bit counts such as 128, 256 or 512. Portability of the code is another key point of focus. Special care has been taken to test in certain high-performance embedded real-time programming environments. Tested efficient functionality on the PC and workstation is also present.

When working with even the most tiny microcontroller systems, I/O streaming can optionally be disabled with the WIDE_INTEGER_DISABLE_IOSTREAM compiler switch. See the examples directory as more use cases are being created.

Easy application follows via a typedef or alias. The defined type can be used very much like a built-in unsinged integral type.

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

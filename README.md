# wide-integer
Wide-Integer implements a generic C++ template for uint128_t, uint256_t, uint512_t, uint1024_t, etc. At the moment, wide-integer is limited to unsigned integral types having bit counts that are powers of 2 greater than or equal to 128.

Inclusion of a single C++11 header file is all that is needed.

Wide-Integer has been tested on numerous compilers and is specifically designed for use with all systems. Special care has been taken to achieve usage for high-performance embedded real-time programming environments.

Easy application follows via a typedef or alias. The type can be used very much like a built-in unsinged integral type:
```C


#include <wide_integer/generic_template_uintwide_t.h>

void test()
{
  using wide_integer_type = wide_integer::generic_template::uint256_t;


  const wide_integer_type a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  const wide_integer_type b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

  const wide_integer_type c = (a * b);
  const wide_integer_type d = (a / b);

  const bool result_is_ok = (   (c == "0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076")
                             && (d == "0xA"));

  std::cout << std::hex << std::uppercase << c << std::endl;
  std::cout << std::hex << std::uppercase << d << std::endl;

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

See the examples directory as more use cases are being created.

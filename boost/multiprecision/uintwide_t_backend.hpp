///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UINTWIDE_T_BACKEND_2019_12_15_HPP // NOLINT(llvm-header-guard)
  #define UINTWIDE_T_BACKEND_2019_12_15_HPP

  #include <cstdint>
  #include <limits>
  #include <string>
  #include <type_traits>

  #if defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wconversion"
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-parameter"
  #endif

  #if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wdeprecated-copy"
  #endif

  #include <boost/config.hpp>
  #include <boost/multiprecision/number.hpp>
  #include <boost/version.hpp>

  #include <math/wide_integer/uintwide_t.h>

  namespace boost::multiprecision {

  // Forward declaration of the uintwide_t_backend multiple precision class.
  // This class binds native (WIDE_INTEGER_NAMESPACE)::math::wide_integer::uintwide_t
  // to boost::multiprecsion::uintwide_t_backend.

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  class uintwide_t_backend;

  // Define the number category as an integer number kind
  // for the uintwide_t_backend. This is needed for properly
  // interacting as a backend with boost::muliprecision.
  #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107200))
  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  struct number_category<uintwide_t_backend<MyWidth2, MyLimbType>>
    : public boost::mpl::int_<number_kind_integer> { };
  #elif (defined(BOOST_VERSION) && (BOOST_VERSION <= 107500))
  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  struct number_category<uintwide_t_backend<MyWidth2, MyLimbType>>
    : public boost::integral_constant<int, number_kind_integer> { };
  #else
  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  struct number_category<uintwide_t_backend<MyWidth2, MyLimbType>>
    : public std::integral_constant<int, number_kind_integer> { };
  #endif

  // This is the uintwide_t_backend multiple precision class.
  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType = std::uint32_t>
  class uintwide_t_backend // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    using representation_type =
    #if defined(WIDE_INTEGER_NAMESPACE)
      WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>;
    #else
      ::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>;
    #endif

    #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107500))
    using signed_types   = mpl::list<std::int64_t>;
    using unsigned_types = mpl::list<std::uint64_t>;
    using float_types    = mpl::list<long double>;
    #else
    using   signed_types = std::tuple<  signed char,   signed short,   signed int,   signed long,   signed long long, std::intmax_t>;  // NOLINT(google-runtime-int)
    using unsigned_types = std::tuple<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, std::uintmax_t>; // NOLINT(google-runtime-int)
    using float_types    = std::tuple<float, double, long double>;
    #endif

    constexpr uintwide_t_backend() : m_value() { }

    explicit constexpr uintwide_t_backend(const representation_type& rep) : m_value(rep) { }

    constexpr uintwide_t_backend(const uintwide_t_backend& other) : m_value(other.m_value) { }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value)
                                      && (std::is_unsigned<UnsignedIntegralType>::value))>::type const* = nullptr>
    constexpr uintwide_t_backend(UnsignedIntegralType u) : m_value(representation_type(std::uint64_t(u))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value)
                                      && (std::is_signed  <SignedIntegralType>::value))>::type const* = nullptr>
    constexpr uintwide_t_backend(SignedIntegralType n) : m_value(representation_type(std::int64_t(n))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    template<typename FloatingPointType,
             typename std::enable_if<std::is_floating_point<FloatingPointType>::value>::type const* = nullptr>
    constexpr uintwide_t_backend(FloatingPointType f) : m_value(representation_type(static_cast<long double>(f))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    constexpr uintwide_t_backend(const char* c) : m_value(c) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    constexpr uintwide_t_backend(const std::string& str) : m_value(str) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    //~uintwide_t_backend() { }

    WIDE_INTEGER_CONSTEXPR auto operator=(const uintwide_t_backend& other) -> uintwide_t_backend&
    {
      if(this != &other)
      {
        m_value.representation() = other.m_value.crepresentation();
      }

      return *this;
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR auto operator=(const ArithmeticType& x) -> uintwide_t_backend&
    {
      m_value = representation_type(x);

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR auto operator=(const std::string& str_rep)  -> uintwide_t_backend& { m_value = representation_type(str_rep);  return *this; }
    WIDE_INTEGER_CONSTEXPR auto operator=(const char*        char_ptr) -> uintwide_t_backend& { m_value = representation_type(char_ptr); return *this; }

    WIDE_INTEGER_CONSTEXPR void swap(uintwide_t_backend& other_mp_cpp_backend)
    {
      m_value.representation().swap(other_mp_cpp_backend.m_value.representation());
    }

                  WIDE_INTEGER_CONSTEXPR auto  representation()       ->       representation_type& { return m_value; }
    WIDE_INTEGER_NODISCARD WIDE_INTEGER_CONSTEXPR auto  representation() const -> const representation_type& { return m_value; }
    WIDE_INTEGER_NODISCARD WIDE_INTEGER_CONSTEXPR auto crepresentation() const -> const representation_type& { return m_value; }

    WIDE_INTEGER_NODISCARD auto str(std::streamsize number_of_digits, const std::ios::fmtflags format_flags) const -> std::string
    {
      (void) number_of_digits;

      std::array<char, representation_type::wr_string_max_buffer_size_dec> pstr { };

      const std::uint_fast8_t base_rep     = (((format_flags & std::ios::hex)       != 0) ? 16U : 10U);
      const bool              show_base    = ( (format_flags & std::ios::showbase)  != 0);
      const bool              show_pos     = ( (format_flags & std::ios::showpos)   != 0);
      const bool              is_uppercase = ( (format_flags & std::ios::uppercase) != 0);

      const bool wr_string_is_ok = m_value.wr_string(pstr.data(), base_rep, show_base, show_pos, is_uppercase);

      std::string str_result = (wr_string_is_ok ? std::string(pstr.data()) : std::string());

      return str_result;
    }

    WIDE_INTEGER_CONSTEXPR void negate()
    {
      m_value.negate();
    }

    WIDE_INTEGER_NODISCARD constexpr auto compare(const uintwide_t_backend& other_mp_cpp_backend) const -> int
    {
      return static_cast<int>(m_value.compare(other_mp_cpp_backend.crepresentation()));
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value>::type const* = nullptr>
    WIDE_INTEGER_NODISCARD constexpr auto compare(ArithmeticType x) const -> int
    {
      return static_cast<int>(m_value.compare(representation_type(x)));
    }

    auto operator=(const representation_type&) -> uintwide_t_backend& = delete;

  private:
    representation_type m_value; // NOLINT(readability-identifier-naming)
  };

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_add(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() += x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_subtract(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() -= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_multiply(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() *= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(std::is_integral<IntegralType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_multiply(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() *= n;
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() /= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value)
                                    && (std::is_unsigned   <IntegralType>::value)
                                    && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<MyLimbType>::digits))>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    using local_wide_integer_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type;

    using local_limb_type = typename local_wide_integer_type::limb_type;

    result.representation().eval_divide_by_single_limb(static_cast<local_limb_type>(n), 0U, nullptr);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value)
                                    && (std::is_unsigned   <IntegralType>::value)
                                    && (std::numeric_limits<IntegralType>::digits) > std::numeric_limits<MyLimbType>::digits)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() /= n;
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() %= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value)
                                    && (std::is_unsigned   <IntegralType>::value)
                                    && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<MyLimbType>::digits))>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_integer_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& x, const IntegralType& n) -> IntegralType
  {
    using local_wide_integer_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type;

    typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type rem;

    local_wide_integer_type(x.crepresentation()).eval_divide_by_single_limb(n, 0U, &rem);

    return static_cast<IntegralType>(rem);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value)
                                    && (std::is_unsigned   <IntegralType>::value)
                                    && (std::numeric_limits<IntegralType>::digits) > std::numeric_limits<MyLimbType>::digits)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_integer_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& x, const IntegralType& n) -> IntegralType
  {
    const uintwide_t_backend<MyWidth2, MyLimbType> rem = x.crepresentation() % uintwide_t_backend<MyWidth2, MyLimbType>(n);

    return static_cast<IntegralType>(rem);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_bitwise_and(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() &= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_bitwise_or(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() |= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_bitwise_xor(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() ^= x.crepresentation();
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_complement(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    for(auto i = 0U; i < std::tuple_size<typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type>::value; ++i)
    {
      using local_limb_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::limb_type;

      result.representation().representation()[i] = static_cast<local_limb_type>(~x.crepresentation().crepresentation()[i]);
    }
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& p,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p.crepresentation(),
                                   m.crepresentation());
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename OtherIntegralTypeM,
           typename std::enable_if<(std::is_integral<OtherIntegralTypeM>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& p,
                                        const OtherIntegralTypeM                         m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p.crepresentation(),
                                   m);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename OtherIntegralTypeP,
           typename std::enable_if<(std::is_integral<OtherIntegralTypeP>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                                        const OtherIntegralTypeP                         p,
                                        const uintwide_t_backend<MyWidth2, MyLimbType>& m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p,
                                   m.crepresentation());
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(std::is_integral<IntegralType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_left_shift(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() <<= n;
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(std::is_integral<IntegralType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR void eval_right_shift(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() >>= n;
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_lsb(const uintwide_t_backend<MyWidth2, MyLimbType>& a) -> unsigned
  {
    return static_cast<unsigned>(lsb(a.crepresentation()));
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_msb(const uintwide_t_backend<MyWidth2, MyLimbType>& a) -> unsigned
  {
    return static_cast<unsigned>(msb(a.crepresentation()));
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_eq(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (a.compare(b) == 0);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_eq(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b) -> bool
  {
    return (a.compare(b) == 0);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_eq(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == 0);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_gt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (a.compare(b) == 1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_gt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b) -> bool
  {
    return (a.compare(b) == 1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_gt(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == 1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_lt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (a.compare(b) == -1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_lt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b) -> bool
  {
    return (a.compare(b) == -1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(std::is_arithmetic <ArithmeticType>::value)>::type const* = nullptr>
  WIDE_INTEGER_CONSTEXPR auto eval_lt(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b) -> bool
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == -1);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_is_zero(const uintwide_t_backend<MyWidth2, MyLimbType>& x) -> bool
  {
    return (x.crepresentation() == 0U);
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR auto eval_get_sign(const uintwide_t_backend<MyWidth2, MyLimbType>& x) -> int
  {
    int n_result { };

    if  (x.crepresentation() == 0U) { n_result = 0; }
    else                            { n_result = 1; }

    return n_result;
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_convert_to(unsigned long long* result, // NOLINT(google-runtime-int)
                                              const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<unsigned long long>(val.crepresentation()); // NOLINT(google-runtime-int)
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_convert_to(signed long long* result, // NOLINT(google-runtime-int)
                                              const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<signed long long>(val.crepresentation()); // NOLINT(google-runtime-int)
  }

  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType>
  WIDE_INTEGER_CONSTEXPR void eval_convert_to(long double* result,
                                              const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<long double>(val.crepresentation());
  }

  } // namespace boost::multiprecision

  namespace boost::math::policies {

  // Specialization of the precision structure.
  template<
  #if defined(WIDE_INTEGER_NAMESPACE)
           const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
  #else
           const ::math::wide_integer::size_t MyWidth2,
  #endif
           typename MyLimbType,
           typename ThisPolicy,
           const boost::multiprecision::expression_template_option ExpressionTemplatesOptions>
  struct precision<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>,
                                                 ExpressionTemplatesOptions>,
                   ThisPolicy>
  {
    using precision_type = typename ThisPolicy::precision_type;

    using local_digits_2 = digits2<MyWidth2>;

    #if (BOOST_VERSION <= 107500)
    using type = typename mpl::if_c       <((local_digits_2::value <= precision_type::value) || (precision_type::value <= 0)),
                                             local_digits_2,
                                             precision_type>::type;
    #else
    using type = typename std::conditional<((local_digits_2::value <= precision_type::value) || (precision_type::value <= 0)),
                                             local_digits_2,
                                             precision_type>::type;
    #endif
  };

  } // namespace boost::math::policies

  namespace std // NOLINT(cert-dcl58-cpp)
  {
    template<
    #if defined(WIDE_INTEGER_NAMESPACE)
             const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2,
    #else
             const ::math::wide_integer::size_t MyWidth2,
    #endif
             typename MyLimbType,
             const boost::multiprecision::expression_template_option ExpressionTemplatesOptions>
    class numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>,
                                                       ExpressionTemplatesOptions>>
    {
    public:
      static constexpr bool is_specialized = true;
      static constexpr bool is_signed      = false;
      static constexpr bool is_integer     = true;
      static constexpr bool is_exact       = true;
      static constexpr bool is_bounded     = true;
      static constexpr bool is_modulo      = false;
      static constexpr bool is_iec559      = false;
      static constexpr int  digits         = MyWidth2;
      static constexpr int  digits10       = static_cast<int>((MyWidth2 * 301LL) / 1000LL);
      static constexpr int  max_digits10   = static_cast<int>((MyWidth2 * 301LL) / 1000LL);

      #if defined(WIDE_INTEGER_NAMESPACE)
      static constexpr int max_exponent   = std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent;
      static constexpr int max_exponent10 = std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent10;
      static constexpr int min_exponent   = std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent;
      static constexpr int min_exponent10 = std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent10;
      #else
      static constexpr int max_exponent   = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent;
      static constexpr int max_exponent10 = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent10;
      static constexpr int min_exponent   = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent;
      static constexpr int min_exponent10 = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent10;
      #endif

      static constexpr int                     radix             = 2;
      static constexpr std::float_round_style  round_style       = std::round_to_nearest;
      static constexpr bool                    has_infinity      = false;
      static constexpr bool                    has_quiet_NaN     = false;
      static constexpr bool                    has_signaling_NaN = false;
      static constexpr std::float_denorm_style has_denorm        = std::denorm_absent;
      static constexpr bool                    has_denorm_loss   = false;
      static constexpr bool                    traps             = false;
      static constexpr bool                    tinyness_before   = false;

      #if defined(WIDE_INTEGER_NAMESPACE)
      static WIDE_INTEGER_CONSTEXPR auto (min)        () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min)()       ); }
      static WIDE_INTEGER_CONSTEXPR auto (max)        () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max)()       ); }
      static WIDE_INTEGER_CONSTEXPR auto lowest       () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::lowest       ); }
      static WIDE_INTEGER_CONSTEXPR auto epsilon      () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::epsilon      ); }
      static WIDE_INTEGER_CONSTEXPR auto round_error  () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::round_error  ); }
      static WIDE_INTEGER_CONSTEXPR auto infinity     () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::infinity     ); }
      static WIDE_INTEGER_CONSTEXPR auto quiet_NaN    () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::quiet_NaN    ); } // NOLINT(readability-identifier-naming)
      static WIDE_INTEGER_CONSTEXPR auto signaling_NaN() -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::signaling_NaN); } // NOLINT(readability-identifier-naming)
      static WIDE_INTEGER_CONSTEXPR auto denorm_min   () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::denorm_min   ); }
      #else
      static WIDE_INTEGER_CONSTEXPR auto (min)        () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min)()       ); }
      static WIDE_INTEGER_CONSTEXPR auto (max)        () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max)()       ); }
      static WIDE_INTEGER_CONSTEXPR auto lowest       () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::lowest       ); }
      static WIDE_INTEGER_CONSTEXPR auto epsilon      () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::epsilon      ); }
      static WIDE_INTEGER_CONSTEXPR auto round_error  () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::round_error  ); }
      static WIDE_INTEGER_CONSTEXPR auto infinity     () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::infinity     ); }
      static WIDE_INTEGER_CONSTEXPR auto quiet_NaN    () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::quiet_NaN    ); } // NOLINT(readability-identifier-naming)
      static WIDE_INTEGER_CONSTEXPR auto signaling_NaN() -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::signaling_NaN); } // NOLINT(readability-identifier-naming)
      static WIDE_INTEGER_CONSTEXPR auto denorm_min   () -> boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::denorm_min   ); }
      #endif
    };

    #ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

    #if defined(WIDE_INTEGER_NAMESPACE)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_specialized; // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_signed;      // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_integer;     // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_exact;       // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_bounded;     // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_modulo;      // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_iec559;      // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits;         // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits10;       // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_digits10;   // NOLINT(readability-redundant-declaration)

    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent;   // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent10; // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent;   // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent10; // NOLINT(readability-redundant-declaration)

    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int                     std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::radix;             // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr std::float_round_style  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::round_style;       // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_infinity;      // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_quiet_NaN;     // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_signaling_NaN; // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr std::float_denorm_style std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm;        // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm_loss;   // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::traps;             // NOLINT(readability-redundant-declaration)
    template<const WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::tinyness_before;   // NOLINT(readability-redundant-declaration)
    #else
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_specialized; // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_signed;      // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_integer;     // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_exact;       // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_bounded;     // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_modulo;      // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_iec559;      // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits;         // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits10;       // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_digits10;   // NOLINT(readability-redundant-declaration)

    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent;    // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent10;  // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent;    // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent10;  // NOLINT(readability-redundant-declaration)

    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr int                     std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::radix;             // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr std::float_round_style  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::round_style;       // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_infinity;      // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_quiet_NaN;     // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_signaling_NaN; // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr std::float_denorm_style std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm;        // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm_loss;   // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::traps;             // NOLINT(readability-redundant-declaration)
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> constexpr bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::tinyness_before;   // NOLINT(readability-redundant-declaration)
    #endif

    #endif // !BOOST_NO_INCLASS_MEMBER_INITIALIZATION

  } // namespace std

  #if (defined(__clang__) && (__clang_major__ > 9)) && !defined(__APPLE__)
  #pragma GCC diagnostic pop
  #endif

  #if defined(__GNUC__)
  #pragma GCC diagnostic pop
  #pragma GCC diagnostic pop
  #pragma GCC diagnostic pop
  #endif

#endif // UINTWIDE_T_BACKEND_2019_12_15_HPP

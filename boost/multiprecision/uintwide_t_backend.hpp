///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UINTWIDE_T_BACKEND_2019_12_15_HPP_
  #define UINTWIDE_T_BACKEND_2019_12_15_HPP_

  #include <cstdint>
  #include <limits>
  #include <string>
  #include <type_traits>

  #if defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wconversion"
  #endif

  #include <boost/config.hpp>
  #include <boost/multiprecision/number.hpp>

  #include <math/wide_integer/uintwide_t.h>

  namespace boost { namespace multiprecision {

  // Forward declaration of the uintwide_t_backend multiple precision class.
  // This class binds native ::mp_cpp to boost::multiprecsion::uintwide_t_backend.
  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  class uintwide_t_backend;
  } }


  // Define the number category as a floating-point kind
  // for the uintwide_t_backend. This is needed for properly
  // interacting as a backend with boost::muliprecision.
  #if (BOOST_VERSION <= 107200)
  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  struct boost::multiprecision::number_category<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>>
    : public boost::mpl::int_<boost::multiprecision::number_kind_integer> { };
  #elif (BOOST_VERSION <= 107500)
  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  struct boost::multiprecision::number_category<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>>
    : public boost::integral_constant<int, boost::multiprecision::number_kind_integer> { };
  #else
  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  struct boost::multiprecision::number_category<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>>
    : public std::integral_constant<int, boost::multiprecision::number_kind_integer> { };
  #endif

  namespace boost { namespace multiprecision {

  // This is the uintwide_t_backend multiple precision class.
  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType = std::uint32_t>
  class uintwide_t_backend
  {
  public:
    using representation_type = ::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>;

    #if (BOOST_VERSION <= 107500)
    using signed_types   = mpl::list<std::int64_t>;
    using unsigned_types = mpl::list<std::uint64_t>;
    using float_types    = mpl::list<long double>;
    #else
    using   signed_types = std::tuple<  signed char,   signed short,   signed int,   signed long,   signed long long, std::intmax_t>;
    using unsigned_types = std::tuple<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, std::uintmax_t>;
    using float_types    = std::tuple<float, double, long double>;
    #endif

    uintwide_t_backend() : m_value() { }

    explicit uintwide_t_backend(const representation_type& rep) : m_value(rep) { }

    uintwide_t_backend(const uintwide_t_backend& other) : m_value(other.m_value) { }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
    uintwide_t_backend(UnsignedIntegralType u) : m_value(representation_type(std::uint64_t(u))) { }

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
    uintwide_t_backend(SignedIntegralType n) : m_value(representation_type(std::int64_t(n))) { }

    template<typename FloatingPointType,
             typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    uintwide_t_backend(FloatingPointType f) : m_value(representation_type(static_cast<long double>(f))) { }

    uintwide_t_backend(const char* c) : m_value(c) { }

    uintwide_t_backend(const std::string& str) : m_value(str) { }

    virtual ~uintwide_t_backend() = default;

    uintwide_t_backend& operator=(const uintwide_t_backend& other)
    {
      if(this != &other)
      {
        m_value.representation() = other.m_value.crepresentation();
      }

      return *this;
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
    uintwide_t_backend& operator=(const ArithmeticType& x)
    {
      m_value = representation_type(x);

      return *this;
    }

    uintwide_t_backend& operator=(const std::string& str_rep)  { m_value = representation_type(str_rep);  return *this; }
    uintwide_t_backend& operator=(const char*        char_ptr) { m_value = representation_type(char_ptr); return *this; }

    void swap(uintwide_t_backend& other_mp_cpp_backend)
    {
      m_value.representation().swap(other_mp_cpp_backend.m_value.representation());
    }

          representation_type&  representation()       { return m_value; }
    const representation_type&  representation() const { return m_value; }
    const representation_type& crepresentation() const { return m_value; }

    std::string str(std::streamsize number_of_digits, const std::ios::fmtflags format_flags) const
    {
      (void) number_of_digits;

      char pstr[representation_type::wr_string_max_buffer_size_dec];

      const std::uint_fast8_t base_rep     = (((format_flags & std::ios::hex)       != 0) ? 16U : 10U);
      const bool              show_base    = ( (format_flags & std::ios::showbase)  != 0);
      const bool              show_pos     = ( (format_flags & std::ios::showpos)   != 0);
      const bool              is_uppercase = ( (format_flags & std::ios::uppercase) != 0);

      const bool wr_string_is_ok = m_value.wr_string(pstr, base_rep, show_base, show_pos, is_uppercase);

      const std::string str_result = (wr_string_is_ok ? std::string(pstr) : std::string());

      return str_result;
    }

    void negate()
    {
      m_value.negate();
    }

    int compare(const uintwide_t_backend& other_mp_cpp_backend) const
    {
      return static_cast<int>(m_value.compare(other_mp_cpp_backend.crepresentation()));
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
    int compare(ArithmeticType x)
    {
      return static_cast<int>(m_value.compare(representation_type(x)));
    }

  private:
    representation_type m_value;

    uintwide_t_backend& operator=(const representation_type&) = delete;
  };

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_add(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() += x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_subtract(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() -= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_multiply(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() *= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(std::is_integral<IntegralType>::value == true)>::type const* = nullptr>
  void eval_multiply(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() *= n;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() /= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                    && (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_unsigned   <IntegralType>::value == true)
                                    && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<MyLimbType>::digits))>::type const* = nullptr>
  void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    using local_wide_integer_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type;

    using local_limb_type = typename local_wide_integer_type::limb_type;

    result.representation().eval_divide_by_single_limb((local_limb_type) n, 0U, nullptr);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                    && (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_unsigned   <IntegralType>::value == true)
                                    && (std::numeric_limits<IntegralType>::digits) > std::numeric_limits<MyLimbType>::digits)>::type const* = nullptr>
  void eval_divide(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() /= n;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() %= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                    && (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_unsigned   <IntegralType>::value == true)
                                    && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<MyLimbType>::digits))>::type const* = nullptr>
  IntegralType eval_integer_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& x, const IntegralType& n)
  {
    using local_wide_integer_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type;

    typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type rem;

    local_wide_integer_type(x.crepresentation()).eval_divide_by_single_limb(n, 0U, &rem);

    return (IntegralType) rem;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                    && (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_unsigned   <IntegralType>::value == true)
                                    && (std::numeric_limits<IntegralType>::digits) > std::numeric_limits<MyLimbType>::digits)>::type const* = nullptr>
  IntegralType eval_integer_modulus(uintwide_t_backend<MyWidth2, MyLimbType>& x, const IntegralType& n)
  {
    const uintwide_t_backend<MyWidth2, MyLimbType> rem = x.crepresentation() % uintwide_t_backend<MyWidth2, MyLimbType>(n);

    return (IntegralType) rem;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_bitwise_and(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() &= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_bitwise_or(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() |= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_bitwise_xor(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    result.representation() ^= x.crepresentation();
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_complement(uintwide_t_backend<MyWidth2, MyLimbType>& result, const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    for(auto i = 0U; i < std::tuple_size<typename uintwide_t_backend<MyWidth2, MyLimbType>::representation_type>::value; ++i)
    {
      using local_limb_type = typename uintwide_t_backend<MyWidth2, MyLimbType>::limb_type;

      result.representation().representation()[i] = (local_limb_type) ~x.crepresentation().crepresentation()[i];
    }
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& p,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p.crepresentation(),
                                   m.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename OtherIntegralTypeM,
           typename std::enable_if<(   (std::is_integral   <OtherIntegralTypeM>::value == true)
                                    && (std::is_fundamental<OtherIntegralTypeM>::value == true))>::type const* = nullptr>
  void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& p,
                 const OtherIntegralTypeM                         m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p.crepresentation(),
                                   m);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename OtherIntegralTypeP,
           typename std::enable_if<(   (std::is_integral   <OtherIntegralTypeP>::value == true)
                                    && (std::is_fundamental<OtherIntegralTypeP>::value == true))>::type const* = nullptr>
  void eval_powm(      uintwide_t_backend<MyWidth2, MyLimbType>& result,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& b,
                 const OtherIntegralTypeP                         p,
                 const uintwide_t_backend<MyWidth2, MyLimbType>& m)
  {
    result.representation() = powm(b.crepresentation(),
                                   p,
                                   m.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_fundamental<IntegralType>::value == true))>::type const* = nullptr>
  void eval_left_shift(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() <<= n;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename IntegralType,
           typename std::enable_if<(   (std::is_integral   <IntegralType>::value == true)
                                    && (std::is_fundamental<IntegralType>::value == true))>::type const* = nullptr>
  void eval_right_shift(uintwide_t_backend<MyWidth2, MyLimbType>& result, const IntegralType& n)
  {
    result.representation() >>= n;
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  unsigned eval_lsb(const uintwide_t_backend<MyWidth2, MyLimbType>& a)
  {
    return (unsigned) lsb(a.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  unsigned eval_msb(const uintwide_t_backend<MyWidth2, MyLimbType>& a)
  {
    return (unsigned) msb(a.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  bool eval_eq(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (a.compare(b) == 0);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_eq(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == 0);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_eq(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == 0);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  bool eval_gt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (a.compare(b) == 1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_gt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == 1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_gt(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == 1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  bool eval_lt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (a.compare(b) == -1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_lt(const uintwide_t_backend<MyWidth2, MyLimbType>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == -1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType,
           typename ArithmeticType,
           typename std::enable_if<(   (std::is_arithmetic <ArithmeticType>::value == true)
                                    && (std::is_fundamental<ArithmeticType>::value == true))>::type const* = nullptr>
  bool eval_lt(const ArithmeticType& a, const uintwide_t_backend<MyWidth2, MyLimbType>& b)
  {
    return (uintwide_t_backend<MyWidth2, MyLimbType>(a).compare(b) == -1);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  bool eval_is_zero(const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    return (x.crepresentation() == 0U);
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  int eval_get_sign(const uintwide_t_backend<MyWidth2, MyLimbType>& x)
  {
    if  (x.crepresentation() == 0U) { return  0; }
    else                            { return  1; }
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_convert_to(unsigned long long* result,
                       const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<unsigned long long>(val.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_convert_to(signed long long* result,
                       const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<signed long long>(val.crepresentation());
  }

  template<const ::math::wide_integer::size_t MyWidth2,
           typename MyLimbType>
  void eval_convert_to(long double* result,
                       const uintwide_t_backend<MyWidth2, MyLimbType>& val)
  {
    *result = static_cast<long double>(val.crepresentation());
  }

  } } // namespace boost::multiprecision

  namespace boost { namespace math { namespace policies {

  // Specialization of the precision structure.
  template<const ::math::wide_integer::size_t MyWidth2,
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

  } } } // namespaces boost::math::policies

  namespace std
  {
    template<const ::math::wide_integer::size_t MyWidth2,
             typename MyLimbType,
             const boost::multiprecision::expression_template_option ExpressionTemplatesOptions>
    class numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>,
                                                       ExpressionTemplatesOptions>>
    {
    public:
      BOOST_STATIC_CONSTEXPR bool is_specialized = true;
      BOOST_STATIC_CONSTEXPR bool is_signed      = false;
      BOOST_STATIC_CONSTEXPR bool is_integer     = true;
      BOOST_STATIC_CONSTEXPR bool is_exact       = true;
      BOOST_STATIC_CONSTEXPR bool is_bounded     = true;
      BOOST_STATIC_CONSTEXPR bool is_modulo      = false;
      BOOST_STATIC_CONSTEXPR bool is_iec559      = false;
      BOOST_STATIC_CONSTEXPR int  digits         = MyWidth2;
      BOOST_STATIC_CONSTEXPR int  digits10       = static_cast<int>((MyWidth2 * 301LL) / 1000LL);
      BOOST_STATIC_CONSTEXPR int  max_digits10   = static_cast<int>((MyWidth2 * 301LL) / 1000LL);

      BOOST_STATIC_CONSTEXPR int max_exponent   = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent;
      BOOST_STATIC_CONSTEXPR int max_exponent10 = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max_exponent10;
      BOOST_STATIC_CONSTEXPR int min_exponent   = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent;
      BOOST_STATIC_CONSTEXPR int min_exponent10 = std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min_exponent10;

      BOOST_STATIC_CONSTEXPR int                     radix             = 2;
      BOOST_STATIC_CONSTEXPR std::float_round_style  round_style       = std::round_to_nearest;
      BOOST_STATIC_CONSTEXPR bool                    has_infinity      = false;
      BOOST_STATIC_CONSTEXPR bool                    has_quiet_NaN     = false;
      BOOST_STATIC_CONSTEXPR bool                    has_signaling_NaN = false;
      BOOST_STATIC_CONSTEXPR std::float_denorm_style has_denorm        = std::denorm_absent;
      BOOST_STATIC_CONSTEXPR bool                    has_denorm_loss   = false;
      BOOST_STATIC_CONSTEXPR bool                    traps             = false;
      BOOST_STATIC_CONSTEXPR bool                    tinyness_before   = false;

      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> (min)        () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::min)()       ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> (max)        () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>((std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::max)()       ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> lowest       () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::lowest       ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> epsilon      () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::epsilon      ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> round_error  () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::round_error  ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> infinity     () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::infinity     ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> quiet_NaN    () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::quiet_NaN    ); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> signaling_NaN() { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::signaling_NaN); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions> denorm_min   () { return boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType> (std::numeric_limits<::math::wide_integer::uintwide_t<MyWidth2, MyLimbType>>::denorm_min   ); }
    };

    #ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_specialized;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_signed;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_integer;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_exact;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_bounded;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_modulo;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::is_iec559;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::digits10;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_digits10;

    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::max_exponent10;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::min_exponent10;

    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST int                     std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::radix;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST std::float_round_style  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::round_style;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_infinity;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_quiet_NaN;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_signaling_NaN;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST std::float_denorm_style std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::has_denorm_loss;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::traps;
    template<const ::math::wide_integer::size_t MyWidth2, typename MyLimbType, const boost::multiprecision::expression_template_option ExpressionTemplatesOptions> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::uintwide_t_backend<MyWidth2, MyLimbType>, ExpressionTemplatesOptions>>::tinyness_before;

    #endif // !BOOST_NO_INCLASS_MEMBER_INITIALIZATION

  } // namespace std

  #if defined(__GNUC__)
  #pragma GCC diagnostic pop
  #endif

#endif // UINTWIDE_T_BACKEND_2019_12_15_HPP_

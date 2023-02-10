///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace example013_ecdsa
{
  class hash_sha256
  {
  public:
    using result_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(32))>;

    // LCOV_EXCL_START
    constexpr hash_sha256()                       = default;
    constexpr hash_sha256(const hash_sha256&)     = default;
    constexpr hash_sha256(hash_sha256&&) noexcept = default;
    ~hash_sha256() = default;

    constexpr auto operator=(hash_sha256&&) noexcept -> hash_sha256& = default;
    constexpr auto operator=(const hash_sha256&) ->     hash_sha256& = default;
    // LCOV_EXCL_STOP

    WIDE_INTEGER_CONSTEXPR auto hash(const std::uint8_t* msg, const size_t length) -> result_type
    {
      init();
      update(msg, length);
      return finalize();
    }

    WIDE_INTEGER_CONSTEXPR void init()
    {
      my_datalen = static_cast<std::uint32_t>(UINT8_C(0));
      my_bitlen  = static_cast<std::uint64_t>(UINT8_C(0));

      transform_context[static_cast<std::size_t>(UINT8_C(0))] = static_cast<std::uint32_t>(UINT32_C(0x6A09E667));
      transform_context[static_cast<std::size_t>(UINT8_C(1))] = static_cast<std::uint32_t>(UINT32_C(0xBB67AE85));
      transform_context[static_cast<std::size_t>(UINT8_C(2))] = static_cast<std::uint32_t>(UINT32_C(0x3C6EF372));
      transform_context[static_cast<std::size_t>(UINT8_C(3))] = static_cast<std::uint32_t>(UINT32_C(0xA54FF53A));
      transform_context[static_cast<std::size_t>(UINT8_C(4))] = static_cast<std::uint32_t>(UINT32_C(0x510E527F));
      transform_context[static_cast<std::size_t>(UINT8_C(5))] = static_cast<std::uint32_t>(UINT32_C(0x9B05688C));
      transform_context[static_cast<std::size_t>(UINT8_C(6))] = static_cast<std::uint32_t>(UINT32_C(0x1F83D9AB));
      transform_context[static_cast<std::size_t>(UINT8_C(7))] = static_cast<std::uint32_t>(UINT32_C(0x5BE0CD19));
    }

    WIDE_INTEGER_CONSTEXPR void update(const std::uint8_t* msg, const size_t length)
    {
      for (auto i = static_cast<std::size_t>(UINT8_C(0)); i < length; ++i)
      {
        my_data[my_datalen] = msg[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
        my_datalen++;

        if(my_datalen == static_cast<std::uint32_t>(UINT8_C(64)))
        {
          // LCOV_EXCL_START
          sha256_transform();

          my_datalen = static_cast<std::uint32_t>(UINT8_C(0));

          my_bitlen = static_cast<std::uint64_t>(my_bitlen + static_cast<std::uint_fast16_t>(UINT16_C(512)));
          // LCOV_EXCL_STOP
        }
      }
    }

    WIDE_INTEGER_CONSTEXPR auto finalize() -> result_type
    {
      result_type hash_result { };

      auto hash_index = static_cast<std::size_t>(my_datalen);

      my_data[hash_index] = static_cast<std::uint8_t>(UINT8_C(0x80)); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)

      ++hash_index;

      // Pad whatever data is left in the buffer.
      if(my_datalen < static_cast<std::uint32_t>(UINT8_C(56U)))
      {
        std::fill((my_data.begin() + hash_index), (my_data.begin() + static_cast<std::size_t>(UINT8_C(56))), static_cast<std::uint8_t>(UINT8_C(0)));
      }
      else
      {
        // LCOV_EXCL_START
        std::fill((my_data.begin() + hash_index), my_data.end(), static_cast<std::uint8_t>(UINT8_C(0)));

        sha256_transform();

        std::fill_n(my_data.begin(), static_cast<std::size_t>(UINT8_C(56)), static_cast<std::uint8_t>(UINT8_C(0)));
        // LCOV_EXCL_STOP
      }

      // Append to the padding the total message length (in bits) and subsequently transform.
      my_bitlen =
        static_cast<std::uint64_t>
        (
            my_bitlen
          + static_cast<std::uint64_t>
            (
              static_cast<std::uint64_t>(my_datalen) * static_cast<std::uint8_t>(UINT8_C(8))
            )
        );

      my_data[static_cast<std::size_t>(UINT8_C(63))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C( 0)));
      my_data[static_cast<std::size_t>(UINT8_C(62))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C( 8)));
      my_data[static_cast<std::size_t>(UINT8_C(61))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(16)));
      my_data[static_cast<std::size_t>(UINT8_C(60))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(24)));
      my_data[static_cast<std::size_t>(UINT8_C(59))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(32)));
      my_data[static_cast<std::size_t>(UINT8_C(58))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(40)));
      my_data[static_cast<std::size_t>(UINT8_C(57))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(48)));
      my_data[static_cast<std::size_t>(UINT8_C(56))] = static_cast<std::uint8_t>(my_bitlen >> static_cast<unsigned>(UINT8_C(56)));

      sha256_transform();

      // Since this implementation uses little endian byte ordering and SHA uses big endian,
      // reverse all the bytes when copying the final transform_context to the output hash.
      constexpr auto conversion_scale =
        static_cast<std::size_t>
        (
            std::numeric_limits<typename transform_context_type::value_type>::digits
          / std::numeric_limits<std::uint8_t>::digits
        );

      for(auto   output_index = static_cast<std::size_t>(UINT8_C(0));
                 output_index < std::tuple_size<result_type>::value;
               ++output_index)
      {
        const auto right_shift_amount =
          static_cast<std::size_t>
          (
            static_cast<std::size_t>
            (
                static_cast<std::size_t>
                (
                    static_cast<std::size_t>(conversion_scale - 1U)
                  - static_cast<std::size_t>(output_index % conversion_scale)
                )
              * static_cast<std::size_t>(UINT8_C(8))
            )
          );

        hash_result[output_index] =
          static_cast<std::uint8_t>
          (
            transform_context[(output_index / conversion_scale)] >> right_shift_amount
          );
      }

      return hash_result;
    }

  private:
    using transform_context_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(8))>;

    std::uint32_t my_datalen { }; // NOLINT(readability-identifier-naming)
    std::uint64_t my_bitlen  { }; // NOLINT(readability-identifier-naming)

    std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))> my_data { }; // NOLINT(readability-identifier-naming)

    transform_context_type transform_context { }; // NOLINT(readability-identifier-naming)

    WIDE_INTEGER_CONSTEXPR auto sha256_transform() -> void
    {
      std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(64))> m { };

      for(auto   i = static_cast<std::size_t>(UINT8_C(0)),
                 j = static_cast<std::size_t>(UINT8_C(0));
                 i < static_cast<std::size_t>(UINT8_C(16));
               ++i,
                 j += 4U)
      {
        m[i] = // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_data[j + static_cast<std::size_t>(UINT8_C(0))]) << static_cast<unsigned>(UINT8_C(24))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
            | static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_data[j + static_cast<std::size_t>(UINT8_C(1))]) << static_cast<unsigned>(UINT8_C(16))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
            | static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_data[j + static_cast<std::size_t>(UINT8_C(2))]) << static_cast<unsigned>(UINT8_C( 8))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
            | static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_data[j + static_cast<std::size_t>(UINT8_C(3))]) << static_cast<unsigned>(UINT8_C( 0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
          );
      }

      for(auto i = static_cast<std::size_t>(UINT8_C(16)) ; i < static_cast<std::size_t>(UINT8_C(64)); ++i)
      {
        m[i] = ssig1(m[i - static_cast<std::size_t>(UINT8_C(2))]) + m[i - static_cast<std::size_t>(UINT8_C(7))] + ssig0(m[i - static_cast<std::size_t>(UINT8_C(15))]) + m[i - static_cast<std::size_t>(UINT8_C(16))]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-bounds-constant-array-index)
      }

      transform_context_type state = transform_context;

      constexpr std::array<std::uint32_t, 64U> transform_constants =
      {
        static_cast<std::uint32_t>(UINT32_C(0x428A2F98)), static_cast<std::uint32_t>(UINT32_C(0x71374491)), static_cast<std::uint32_t>(UINT32_C(0xB5C0FBCF)), static_cast<std::uint32_t>(UINT32_C(0xE9B5DBA5)),
        static_cast<std::uint32_t>(UINT32_C(0x3956C25B)), static_cast<std::uint32_t>(UINT32_C(0x59F111F1)), static_cast<std::uint32_t>(UINT32_C(0x923F82A4)), static_cast<std::uint32_t>(UINT32_C(0xAB1C5ED5)),
        static_cast<std::uint32_t>(UINT32_C(0xD807AA98)), static_cast<std::uint32_t>(UINT32_C(0x12835B01)), static_cast<std::uint32_t>(UINT32_C(0x243185BE)), static_cast<std::uint32_t>(UINT32_C(0x550C7DC3)),
        static_cast<std::uint32_t>(UINT32_C(0x72BE5D74)), static_cast<std::uint32_t>(UINT32_C(0x80DEB1FE)), static_cast<std::uint32_t>(UINT32_C(0x9BDC06A7)), static_cast<std::uint32_t>(UINT32_C(0xC19BF174)),
        static_cast<std::uint32_t>(UINT32_C(0xE49B69C1)), static_cast<std::uint32_t>(UINT32_C(0xEFBE4786)), static_cast<std::uint32_t>(UINT32_C(0x0FC19DC6)), static_cast<std::uint32_t>(UINT32_C(0x240CA1CC)),
        static_cast<std::uint32_t>(UINT32_C(0x2DE92C6F)), static_cast<std::uint32_t>(UINT32_C(0x4A7484AA)), static_cast<std::uint32_t>(UINT32_C(0x5CB0A9DC)), static_cast<std::uint32_t>(UINT32_C(0x76F988DA)),
        static_cast<std::uint32_t>(UINT32_C(0x983E5152)), static_cast<std::uint32_t>(UINT32_C(0xA831C66D)), static_cast<std::uint32_t>(UINT32_C(0xB00327C8)), static_cast<std::uint32_t>(UINT32_C(0xBF597FC7)),
        static_cast<std::uint32_t>(UINT32_C(0xC6E00BF3)), static_cast<std::uint32_t>(UINT32_C(0xD5A79147)), static_cast<std::uint32_t>(UINT32_C(0x06CA6351)), static_cast<std::uint32_t>(UINT32_C(0x14292967)),
        static_cast<std::uint32_t>(UINT32_C(0x27B70A85)), static_cast<std::uint32_t>(UINT32_C(0x2E1B2138)), static_cast<std::uint32_t>(UINT32_C(0x4D2C6DFC)), static_cast<std::uint32_t>(UINT32_C(0x53380D13)),
        static_cast<std::uint32_t>(UINT32_C(0x650A7354)), static_cast<std::uint32_t>(UINT32_C(0x766A0ABB)), static_cast<std::uint32_t>(UINT32_C(0x81C2C92E)), static_cast<std::uint32_t>(UINT32_C(0x92722C85)),
        static_cast<std::uint32_t>(UINT32_C(0xA2BFE8A1)), static_cast<std::uint32_t>(UINT32_C(0xA81A664B)), static_cast<std::uint32_t>(UINT32_C(0xC24B8B70)), static_cast<std::uint32_t>(UINT32_C(0xC76C51A3)),
        static_cast<std::uint32_t>(UINT32_C(0xD192E819)), static_cast<std::uint32_t>(UINT32_C(0xD6990624)), static_cast<std::uint32_t>(UINT32_C(0xF40E3585)), static_cast<std::uint32_t>(UINT32_C(0x106AA070)),
        static_cast<std::uint32_t>(UINT32_C(0x19A4C116)), static_cast<std::uint32_t>(UINT32_C(0x1E376C08)), static_cast<std::uint32_t>(UINT32_C(0x2748774C)), static_cast<std::uint32_t>(UINT32_C(0x34B0BCB5)),
        static_cast<std::uint32_t>(UINT32_C(0x391C0CB3)), static_cast<std::uint32_t>(UINT32_C(0x4ED8AA4A)), static_cast<std::uint32_t>(UINT32_C(0x5B9CCA4F)), static_cast<std::uint32_t>(UINT32_C(0x682E6FF3)),
        static_cast<std::uint32_t>(UINT32_C(0x748F82EE)), static_cast<std::uint32_t>(UINT32_C(0x78A5636F)), static_cast<std::uint32_t>(UINT32_C(0x84C87814)), static_cast<std::uint32_t>(UINT32_C(0x8CC70208)),
        static_cast<std::uint32_t>(UINT32_C(0x90BEFFFA)), static_cast<std::uint32_t>(UINT32_C(0xA4506CEB)), static_cast<std::uint32_t>(UINT32_C(0xBEF9A3F7)), static_cast<std::uint32_t>(UINT32_C(0xC67178F2))
      };

      for(auto i = static_cast<std::size_t>(UINT8_C(0)); i < static_cast<std::size_t>(UINT8_C(64)); ++i)
      {
        const auto tmp1 =
          static_cast<std::uint32_t>
          (
              state[static_cast<std::size_t>(UINT8_C(7))]
            + bsig1(state[static_cast<std::size_t>(UINT8_C(4))])
            + ch(state[static_cast<std::size_t>(UINT8_C(4))], state[static_cast<std::size_t>(UINT8_C(5))], state[static_cast<std::size_t>(UINT8_C(6))])
            + transform_constants[i] // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
            + m[i]                   // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
          );

        const auto tmp2 =
          static_cast<std::uint32_t>
          (
              bsig0(state[static_cast<std::size_t>(UINT8_C(0))])
            + maj(state[static_cast<std::size_t>(UINT8_C(0))], state[static_cast<std::size_t>(UINT8_C(1))], state[static_cast<std::size_t>(UINT8_C(2))])
          );

        state[static_cast<std::size_t>(UINT8_C(7))] = state[static_cast<std::size_t>(UINT8_C(6))];
        state[static_cast<std::size_t>(UINT8_C(6))] = state[static_cast<std::size_t>(UINT8_C(5))];
        state[static_cast<std::size_t>(UINT8_C(5))] = state[static_cast<std::size_t>(UINT8_C(4))];
        state[static_cast<std::size_t>(UINT8_C(4))] = state[static_cast<std::size_t>(UINT8_C(3))] + tmp1;
        state[static_cast<std::size_t>(UINT8_C(3))] = state[static_cast<std::size_t>(UINT8_C(2))];
        state[static_cast<std::size_t>(UINT8_C(2))] = state[static_cast<std::size_t>(UINT8_C(1))];
        state[static_cast<std::size_t>(UINT8_C(1))] = state[static_cast<std::size_t>(UINT8_C(0))];
        state[static_cast<std::size_t>(UINT8_C(0))] = tmp1 + tmp2;
      }

      transform_context[static_cast<std::size_t>(UINT8_C(0))] += state[static_cast<std::size_t>(UINT8_C(0))];
      transform_context[static_cast<std::size_t>(UINT8_C(1))] += state[static_cast<std::size_t>(UINT8_C(1))];
      transform_context[static_cast<std::size_t>(UINT8_C(2))] += state[static_cast<std::size_t>(UINT8_C(2))];
      transform_context[static_cast<std::size_t>(UINT8_C(3))] += state[static_cast<std::size_t>(UINT8_C(3))];
      transform_context[static_cast<std::size_t>(UINT8_C(4))] += state[static_cast<std::size_t>(UINT8_C(4))];
      transform_context[static_cast<std::size_t>(UINT8_C(5))] += state[static_cast<std::size_t>(UINT8_C(5))];
      transform_context[static_cast<std::size_t>(UINT8_C(6))] += state[static_cast<std::size_t>(UINT8_C(6))];
      transform_context[static_cast<std::size_t>(UINT8_C(7))] += state[static_cast<std::size_t>(UINT8_C(7))];
    }

    static constexpr auto rotl(std::uint32_t a, unsigned b) -> std::uint32_t
    {
      // Circular left shift ROTR^n(x).
      return (static_cast<std::uint32_t>(a << b) | static_cast<std::uint32_t>(a >> (static_cast<unsigned>(UINT8_C(32)) - b)));
    }

    static constexpr auto rotr(std::uint32_t a, unsigned b) -> std::uint32_t
    {
      // Circular right shift ROTR^n(x).
      return (static_cast<std::uint32_t>(a >> b) | static_cast<std::uint32_t>(a << (static_cast<unsigned>(UINT8_C(32)) - b)));
    }

    static constexpr auto ch(std::uint32_t x, std::uint32_t y, std::uint32_t z) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(x & y) ^ static_cast<std::uint32_t>(~x & z));
    }

    static constexpr auto maj(std::uint32_t x, std::uint32_t y, std::uint32_t z) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(x & y) ^ static_cast<std::uint32_t>(x & z) ^ static_cast<std::uint32_t>(y & z));
    }

    static constexpr auto bsig0(std::uint32_t x) -> std::uint32_t
    {
      return (rotr(x, static_cast<unsigned>(UINT8_C(2))) ^ rotr(x, static_cast<unsigned>(UINT8_C(13))) ^ rotr(x, static_cast<unsigned>(UINT8_C(22))));
    }

    static constexpr auto bsig1(std::uint32_t x) -> std::uint32_t
    {
      return (rotr(x, static_cast<unsigned>(UINT8_C(6))) ^ rotr(x, static_cast<unsigned>(UINT8_C(11))) ^ rotr(x, static_cast<unsigned>(UINT8_C(25))));
    }

    static constexpr auto ssig0(std::uint32_t x) -> std::uint32_t
    {
      return (rotr(x, static_cast<unsigned>(UINT8_C(7))) ^ rotr(x, static_cast<unsigned>(UINT8_C(18))) ^ (x >> static_cast<unsigned>(UINT8_C(3))));
    }

    static constexpr auto ssig1(std::uint32_t x) -> std::uint32_t
    {
      return (rotr(x, static_cast<unsigned>(UINT8_C(17))) ^ rotr(x, static_cast<unsigned>(UINT8_C(19))) ^ (x >> static_cast<unsigned>(UINT8_C(10))));
    }
  };

  template<const std::size_t N>
  WIDE_INTEGER_CONSTEXPR auto hash(std::array<std::uint8_t, N> v) -> typename hash_sha256::result_type
  {
    return example013_ecdsa::hash_sha256().hash(v.data(), v.size());
  }

  template<const unsigned CurveBits,
           typename LimbType,
           const char* PointX,
           const char* PointY>
  struct ecc_point
  {
    #if defined(WIDE_INTEGER_NAMESPACE)
    using uint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(CurveBits), LimbType, void, false>;
    #else
    using uint_type = ::math::wide_integer::uintwide_t<static_cast<::math::wide_integer::size_t>(CurveBits), LimbType, void, false>;
    #endif

    #if defined(WIDE_INTEGER_NAMESPACE)
    using double_sint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(2))), LimbType, void, true>;
    #else
    using double_sint_type = ::math::wide_integer::uintwide_t<static_cast<::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(2))), LimbType, void, true>;
    #endif

    using limb_type = typename uint_type::limb_type;

    using point_type =
      struct point_type
      {
        constexpr point_type(double_sint_type x = static_cast<double_sint_type>(static_cast<unsigned>(UINT8_C(0))), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,bugprone-easily-swappable-parameters)
                             double_sint_type y = static_cast<double_sint_type>(static_cast<unsigned>(UINT8_C(0)))) noexcept
          : my_x(x),
            my_y(y) { }

        double_sint_type my_x; // NOLINT(misc-non-private-member-variables-in-classes)
        double_sint_type my_y; // NOLINT(misc-non-private-member-variables-in-classes)
      };

    #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))
    static WIDE_INTEGER_CONSTEXPR auto value_g() noexcept -> point_type
    {
      return point_type { double_sint_type(PointX), double_sint_type(PointY) }; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    }
    #else
    static auto value_g() noexcept -> const point_type&
    {
      static const point_type pt { double_sint_type(PointX), double_sint_type(PointY) }; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

      return pt;
    }
    #endif
  };

  template<const unsigned CurveBits,
           typename LimbType,
           const char* CurveName,
           const char* FieldCharacteristicP,
           const int   CurveCoefficientA,
           const int   CurveCoefficientB,
           const char* BasePointGx,
           const char* BasePointGy,
           const char* SubGroupOrder,
           const int   SubGroupCoFactor>
  struct elliptic_curve : public ecc_point<CurveBits, LimbType, BasePointGx, BasePointGy>
  {
    using base_class_type = ecc_point<CurveBits, LimbType, BasePointGx, BasePointGy>; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    using point_type       = typename base_class_type::point_type;
    using uint_type        = typename base_class_type::uint_type;
    using double_sint_type = typename base_class_type::double_sint_type;
    using limb_type        = typename base_class_type::limb_type;

    using keypair_type = std::pair<uint_type, std::pair<uint_type, uint_type>>;

    #if defined(WIDE_INTEGER_NAMESPACE)
    using sexatuple_sint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(6))), limb_type, void, true>;
    #else
    using sexatuple_sint_type = ::math::wide_integer::uintwide_t<static_cast<::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(6))), limb_type, void, true>;
    #endif

    #if defined(WIDE_INTEGER_NAMESPACE)
    using duodectuple_sint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(12))), limb_type, void, true>;
    #else
    using duodectuple_sint_type = ::math::wide_integer::uintwide_t<static_cast<::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(12))), limb_type, void, true>;
    #endif

    #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))
    static WIDE_INTEGER_CONSTEXPR auto value_p () noexcept -> double_sint_type { return double_sint_type(FieldCharacteristicP); } // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    static WIDE_INTEGER_CONSTEXPR auto value_n () noexcept -> double_sint_type { return double_sint_type(SubGroupOrder); }        // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    static WIDE_INTEGER_CONSTEXPR auto value_gx() noexcept -> double_sint_type { return base_class_type::value_g().my_x; }
    static WIDE_INTEGER_CONSTEXPR auto value_gy() noexcept -> double_sint_type { return base_class_type::value_g().my_y; }
    #else
    static auto value_p () noexcept -> const double_sint_type& { static const double_sint_type vp(FieldCharacteristicP); return vp; } // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    static auto value_n () noexcept -> const double_sint_type& { static const double_sint_type vn(SubGroupOrder);        return vn; } // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    static auto value_gx() noexcept -> const double_sint_type& { static const double_sint_type vgx(base_class_type::value_g().my_x); return vgx; }
    static auto value_gy() noexcept -> const double_sint_type& { static const double_sint_type vgy(base_class_type::value_g().my_y); return vgy; }
    #endif

    static auto inverse_mod(const double_sint_type& k, const double_sint_type& p) -> double_sint_type // NOLINT(misc-no-recursion)
    {
      // Returns the inverse of k modulo p.
      // This function returns the only integer x such that (x * k) % p == 1.
      // k must be non-zero and p must be a prime.

      if(k == 0)
      {
        // Error: Division by zero.
        return 0; // LCOV_EXCL_LINE
      }

      if(k < 0)
      {
        // k ** -1 = p - (-k) ** -1  (mod p)
        return p - inverse_mod(-k, p);
      }

      // Extended Euclidean algorithm.
      auto s = double_sint_type(0U); auto old_s = double_sint_type(1U);
      auto t = double_sint_type(1U); auto old_t = double_sint_type(0U);
      auto r = double_sint_type(p) ; auto old_r = double_sint_type(k);

      while(r != 0U) // NOLINT(altera-id-dependent-backward-branch)
      {
        double_sint_type quotient = divmod(old_r, r).first;

        const auto tmp_old_r = old_r; const auto tmp_r = r; old_r = r; r = tmp_old_r - quotient * tmp_r;
        const auto tmp_old_s = old_s; const auto tmp_s = s; old_s = s; s = tmp_old_s - quotient * tmp_s;
        const auto tmp_old_t = old_t; const auto tmp_t = t; old_t = t; t = tmp_old_t - quotient * tmp_t;
      }

      const auto mod_result = static_cast<uint_type>(divmod(old_s, p).second);

      return mod_result;
    }

    // Functions that work on curve points

    static auto is_on_curve(const point_type& point) -> bool
    {
      // Returns True if the given point lies on the elliptic curve.
      if((point.my_x == 0) && (point.my_y == 0))
      {
        // None represents the point at infinity.
        return true;
      }

      // Test the condition:
      //   (y * y - x * x * x - curve.a * x -curve.b) % curve.p == 0
      const auto num =
        sexatuple_sint_type
        (
            (sexatuple_sint_type(point.my_y) * sexatuple_sint_type(point.my_y))
          - (sexatuple_sint_type(point.my_x) * (sexatuple_sint_type(point.my_x) * sexatuple_sint_type(point.my_x)))
          - (sexatuple_sint_type(point.my_x) * CurveCoefficientA)
          - CurveCoefficientB
        );

      const auto divmod_result = divmod(num, sexatuple_sint_type(value_p())).second;

      return (divmod_result == 0);
    }

    // LCOV_EXCL_START
    static constexpr auto point_neg(const point_type& point) -> point_type
    {
      // Returns the negation of the point on the curve (i.e., -point).

      return
      {
        ((point.my_x == 0) && (point.my_y == 0))
          ? point_type(0)
          : point_type
            {
               point.my_x,
              -divmod(point.my_y, value_p()).second
            }
      };
    }
    // LCOV_EXCL_STOP

    static auto point_add(const point_type& point1, const point_type& point2) -> point_type
    {
      // Returns the result of point1 + point2 according to the group law.

      const auto& x1 = point1.my_x; const auto& y1 = point1.my_y;
      const auto& x2 = point2.my_x; const auto& y2 = point2.my_y;

      if((x1 == 0) && (y1 == 0))
      {
        // 0 + point2 = point2
        return point_type(point2);
      }

      if((x2 == 0) && (y2 == 0))
      {
        // point1 + 0 = point1
        return point_type(point1); // LCOV_EXCL_LINE
      }

      if((x1 == x2) && (y1 != y2))
      {
        // point1 + (-point1) = 0
        return point_type { }; // LCOV_EXCL_LINE
      }

      // Differentiate the cases (point1 == point2) and (point1 != point2).

      const auto m =
        sexatuple_sint_type
        (
          (x1 == x2)
            ? (sexatuple_sint_type(x1) * sexatuple_sint_type(x1) * 3 + CurveCoefficientA) * sexatuple_sint_type(inverse_mod(y1 * 2, value_p()))
            : sexatuple_sint_type(y1 - y2) * sexatuple_sint_type(inverse_mod(x1 - x2, value_p()))
        );

      const auto x3 =
        duodectuple_sint_type
        (
          duodectuple_sint_type(m) * duodectuple_sint_type(m) - duodectuple_sint_type(x1 + x2)
        );

      const auto y3 =
        duodectuple_sint_type
        (
          duodectuple_sint_type(y1) + duodectuple_sint_type(m) * (x3 - duodectuple_sint_type(x1))
        );

      return
      {
        double_sint_type(divmod( x3, duodectuple_sint_type(value_p())).second),
        double_sint_type(divmod(-y3, duodectuple_sint_type(value_p())).second)
      };
    }

    static auto scalar_mult(const double_sint_type& k, const point_type& point) -> point_type // NOLINT(misc-no-recursion)
    {
      // Returns k * point computed using the double and point_add algorithm.

      if(((k % value_n()) == 0) || ((point.my_x == 0) && (point.my_y == 0)))
      {
        return point_type { }; // LCOV_EXCL_LINE
      }

      if(k < 0)
      {
        // k * point = -k * (-point)
        return scalar_mult(-k, point_neg(point)); // LCOV_EXCL_LINE
      }

      point_type result { };
      point_type addend = point;

      double_sint_type k_val(k);

      while(k_val != 0) // NOLINT(altera-id-dependent-backward-branch)
      {
        const auto lo_bit =
          static_cast<std::uint8_t>
          (
            static_cast<std::uint8_t>(k_val) & static_cast<std::uint8_t>(UINT8_C(1))
          );

        if(lo_bit != static_cast<std::uint8_t>(UINT8_C(0)))
        {
          // Add.
          result = point_add(result, addend);
        }

        // Double.
        addend = point_add(addend, addend);

        k_val >>= 1;
      }

      return result;
    }

    static auto make_keypair() -> keypair_type
    {
      // Generates a random private-public key pair.
      //const auto private_key = random.randrange(1, curve.n)
      const auto private_key = uint_type("0xc6455bf2f380f6b81f5fd1a1dbc2392b3783ed1e7d91b62942706e5584ba0b92");
      const auto public_key  = scalar_mult(private_key, point_type(value_gx(), value_gy()));

      return
      {
        private_key,
        {
          uint_type(public_key.my_x),
          uint_type(public_key.my_y)
        }
      };
    }
  };

  constexpr char CurveName           [] = "secp256k1";                                                          // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char FieldCharacteristicP[] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char BasePointGx         [] = "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char BasePointGy         [] = "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char SubGroupOrderN      [] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)

} // namespace example013_ecdsa

#if defined(WIDE_INTEGER_NAMESPACE)
auto WIDE_INTEGER_NAMESPACE::math::wide_integer::example013_ecdsa_sign_verify() -> bool
#else
auto ::math::wide_integer::example013_ecdsa_sign_verify() -> bool
#endif
{
  auto result_is_ok = true;

  WIDE_INTEGER_CONSTEXPR std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(3))> abc
  {
    static_cast<std::uint8_t>(UINT8_C(0x61)),
    static_cast<std::uint8_t>(UINT8_C(0x62)),
    static_cast<std::uint8_t>(UINT8_C(0x63))
  };

  WIDE_INTEGER_CONSTEXPR auto hr = example013_ecdsa::hash(abc);

  WIDE_INTEGER_CONSTEXPR auto hash_ctrl =
    example013_ecdsa::hash_sha256::result_type
    {
      static_cast<std::uint8_t>(UINT8_C(0xBA)), static_cast<std::uint8_t>(UINT8_C(0x78)), static_cast<std::uint8_t>(UINT8_C(0x16)), static_cast<std::uint8_t>(UINT8_C(0xBF)), static_cast<std::uint8_t>(UINT8_C(0x8F)), static_cast<std::uint8_t>(UINT8_C(0x01)), static_cast<std::uint8_t>(UINT8_C(0xCF)), static_cast<std::uint8_t>(UINT8_C(0xEA)),
      static_cast<std::uint8_t>(UINT8_C(0x41)), static_cast<std::uint8_t>(UINT8_C(0x41)), static_cast<std::uint8_t>(UINT8_C(0x40)), static_cast<std::uint8_t>(UINT8_C(0xDE)), static_cast<std::uint8_t>(UINT8_C(0x5D)), static_cast<std::uint8_t>(UINT8_C(0xAE)), static_cast<std::uint8_t>(UINT8_C(0x22)), static_cast<std::uint8_t>(UINT8_C(0x23)),
      static_cast<std::uint8_t>(UINT8_C(0xB0)), static_cast<std::uint8_t>(UINT8_C(0x03)), static_cast<std::uint8_t>(UINT8_C(0x61)), static_cast<std::uint8_t>(UINT8_C(0xA3)), static_cast<std::uint8_t>(UINT8_C(0x96)), static_cast<std::uint8_t>(UINT8_C(0x17)), static_cast<std::uint8_t>(UINT8_C(0x7A)), static_cast<std::uint8_t>(UINT8_C(0x9C)),
      static_cast<std::uint8_t>(UINT8_C(0xB4)), static_cast<std::uint8_t>(UINT8_C(0x10)), static_cast<std::uint8_t>(UINT8_C(0xFF)), static_cast<std::uint8_t>(UINT8_C(0x61)), static_cast<std::uint8_t>(UINT8_C(0xF2)), static_cast<std::uint8_t>(UINT8_C(0x00)), static_cast<std::uint8_t>(UINT8_C(0x15)), static_cast<std::uint8_t>(UINT8_C(0xAD)),
    };

  WIDE_INTEGER_CONSTEXPR auto result_hash_is_ok = (hr == hash_ctrl);

  #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))
  static_assert(result_hash_is_ok, "Error: Compile-time hash has failed");
  #endif

  result_is_ok = (result_hash_is_ok && result_is_ok);

  using elliptic_curve_type =
    example013_ecdsa::elliptic_curve<static_cast<unsigned>(UINT16_C(256)),
                                     std::uint32_t,
                                     example013_ecdsa::CurveName,            // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                     example013_ecdsa::FieldCharacteristicP, // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                     static_cast<int>(INT8_C(0)),
                                     static_cast<int>(INT8_C(7)),
                                     example013_ecdsa::BasePointGx,          // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                     example013_ecdsa::BasePointGy,          // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                     example013_ecdsa::SubGroupOrderN,       // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                     static_cast<int>(INT8_C(1))>;

  #if (defined(WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST) && (WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST == 1))

  static_assert(elliptic_curve_type::value_p () == elliptic_curve_type::double_sint_type("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"),
                "Error: Elliptic curve Field Characteristic p is seemingly incorrect");

  static_assert(elliptic_curve_type::value_n () == elliptic_curve_type::double_sint_type("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"),
                "Error: Elliptic curve Sub-Group Order is seemingly incorrect");

  static_assert(elliptic_curve_type::value_gx() == elliptic_curve_type::double_sint_type("0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"),
                "Error: Elliptic curve base-point Gx is seemingly incorrect");

  static_assert(elliptic_curve_type::value_gy() == elliptic_curve_type::double_sint_type("0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"),
                "Error: Elliptic curve base-point Gx is seemingly incorrect");

  #else
  static_cast<void>(elliptic_curve_type::value_p());
  #endif

  const auto keypair = elliptic_curve_type::make_keypair();

  const auto result_is_on_curve_is_ok =
    elliptic_curve_type::is_on_curve
    (
      {
        std::get<1>(keypair).first,
        std::get<1>(keypair).second
      }
    );

  const auto result_private_is_ok  = (std::get<0>(keypair)        == "0xc6455bf2f380f6b81f5fd1a1dbc2392b3783ed1e7d91b62942706e5584ba0b92");
  const auto result_public_x_is_ok = (std::get<1>(keypair).first  == "0xc6235629f157690e1df37248256c4fb7eff073d0250f5bd85df40b9e127a8461");
  const auto result_public_y_is_ok = (std::get<1>(keypair).second == "0xcbaa679f07f9b98f915c1fb7d85a379d0559a9eee6735b1be0ce0e2e2b2e94de");

  const auto result_keygen_is_ok =
  (
       result_private_is_ok
    && result_public_x_is_ok
    && result_public_y_is_ok
  );

  result_is_ok = (result_is_on_curve_is_ok && result_keygen_is_ok && result_is_ok);

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if defined(WIDE_INTEGER_STANDALONE_EXAMPLE013_ECDSA_SIGN_VERIFY)

#include <iomanip>
#include <iostream>

auto main() -> int
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  const auto result_is_ok = WIDE_INTEGER_NAMESPACE::math::wide_integer::example013_ecdsa_sign_verify();
  #else
  const auto result_is_ok = ::math::wide_integer::example013_ecdsa_sign_verify();
  #endif

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return (result_is_ok ? 0 : -1);
}

#endif

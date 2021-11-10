///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <random>
#include <string>

#include <examples/example_uintwide_t.h>
#include <math/wide_integer/uintwide_t.h>

namespace local_rsa
{
  template<const std::size_t RsaBitCount,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>>
  class rsa_base
  {
  public:
    static constexpr std::size_t bit_count = RsaBitCount;

    using allocator_type = typename std::allocator_traits<AllocatorType>::template rebind_alloc<LimbType>;

    using my_uintwide_t  = ::math::wide_integer::uintwide_t< ::math::wide_integer::size_t(bit_count),
                                                            LimbType,
                                                            allocator_type>;

    using limb_type      = typename my_uintwide_t::limb_type;

    using crypto_char    = my_uintwide_t;
    using crypto_alloc   = typename std::allocator_traits<allocator_type>::template rebind_alloc<crypto_char>;
    using crypto_string  = math::wide_integer::detail::dynamic_array<crypto_char, crypto_alloc>;

    typedef struct private_key_type
    {
      my_uintwide_t s;
      my_uintwide_t p;
      my_uintwide_t q;
    }
    private_key_type;

    typedef struct public_key_type
    {
      my_uintwide_t r;
      my_uintwide_t m;
    }
    public_key_type;

    virtual ~rsa_base() = default;

    struct euclidean
    {
      template<typename IntegerType>
      static IntegerType extended_euclidean(const IntegerType& a,
                                            const IntegerType& b,
                                                  IntegerType* x,
                                                  IntegerType* y)
      {
        // Recursive extended Euclidean algorithm.
        using local_integer_type = IntegerType;

        if(a == 0)
        {
          *x = local_integer_type(0U);
          *y = local_integer_type(1U);

          return b;
        }

        local_integer_type tmp_x;
        local_integer_type tmp_y;

        const local_integer_type gcd_ext = extended_euclidean(b % a, a, &tmp_x, &tmp_y);

        *x = tmp_y - ((b / a) * tmp_x);
        *y = tmp_x;

        return gcd_ext;
      }
    };

    class encryptor
    {
    public:
      encryptor(const public_key_type& key) : public_key(key) { }

      template<typename InputIterator,
               typename OutputIterator>
      void encrypt(InputIterator in_first, const std::size_t count, OutputIterator out)
      {
        for(auto it = in_first; it != in_first + typename std::iterator_traits<InputIterator>::difference_type(count); ++it)
        {
          *out++ = powm(my_uintwide_t(*it), public_key.r, public_key.m);
        }
      }

    private:
      const public_key_type& public_key;
    };

    class decryptor
    {
    public:
      decryptor(const private_key_type& key) : private_key(key) { }

      template<typename InputIterator,
               typename OutputIterator>
      void decrypt(InputIterator cry_in, const std::size_t count, OutputIterator cypher_out)
      {
        InputIterator cry_end(cry_in + typename std::iterator_traits<InputIterator>::difference_type(count));

        for(auto it = cry_in; it !=  cry_end; ++it)
        {
          const my_uintwide_t tmp = powm(*it, private_key.s, private_key.q * private_key.p);

          *cypher_out++ = static_cast<typename std::iterator_traits<OutputIterator>::value_type>((limb_type) tmp);
        }
      }

    private:
      const private_key_type& private_key;
    };

    rsa_base(const rsa_base& other) : my_p       (other.my_p),
                                      my_q       (other.my_q),
                                      my_r       (other.my_r),
                                      my_m       (other.my_m),
                                      phi_of_m   (other.phi_of_m),
                                      public_key (other.public_key),
                                      private_key(other.private_key) { }

    rsa_base(rsa_base&& other) : my_p       ((my_uintwide_t&&) other.my_p),
                                 my_q       ((my_uintwide_t&&) other.my_q),
                                 my_r       ((my_uintwide_t&&) other.my_r),
                                 my_m       ((my_uintwide_t&&) other.my_m),
                                 phi_of_m   ((my_uintwide_t&&) other.phi_of_m),
                                 public_key ((public_key_type&&)     other.public_key),
                                 private_key((private_key_type&&)    other.private_key) { }

    rsa_base& operator=(const rsa_base& other)
    {
      if(this != &other)
      {
        my_p        = other.my_p;
        my_q        = other.my_q;
        my_r        = other.my_r;
        my_m        = other.my_m;
        phi_of_m    = other.phi_of_m;
        public_key  = other.public_key;
        private_key = other.private_key;
      }

      return *this;
    }

    rsa_base& operator=(rsa_base&& other)
    {
      my_p        = (my_uintwide_t&&) other.my_p;
      my_q        = (my_uintwide_t&&) other.my_q;
      my_r        = (my_uintwide_t&&) other.my_r;
      my_m        = (my_uintwide_t&&) other.my_m;
      phi_of_m    = (my_uintwide_t&&) other.phi_of_m;
      public_key  = (public_key_type&&)     other.public_key;
      private_key = (private_key_type&&)    other.private_key;

      return *this;
    }

    const public_key_type&  getPublicKey () const { return public_key; }
    const private_key_type& getPrivateKey() const { return private_key; }

    const crypto_char& get_p() const { return getPrivateKey().p; }
    const crypto_char& get_q() const { return getPrivateKey().q; }
    const crypto_char& get_d() const { return getPrivateKey().s; }
    const crypto_char& get_n() const { return getPublicKey().m; }

    crypto_string encrypt(const std::string& str) const
    {
      crypto_string str_out(str.length());

      encryptor(public_key).encrypt(str.cbegin(), str.length(), str_out.begin());

      return str_out;
    }

    std::string decrypt(const crypto_string& str) const
    {
      std::string res(str.size(), char('\0'));

      decryptor(private_key).decrypt(str.cbegin(), str.size(), res.begin());

      return res;
    }

    template<typename RandomEngineType = std::minstd_rand>
    static bool is_prime(const my_uintwide_t& p,
                         const RandomEngineType& generator = RandomEngineType(static_cast<typename RandomEngineType::result_type>(std::clock())))
    {
      using local_distribution_type =
        ::math::wide_integer::uniform_int_distribution< :: math::wide_integer::size_t(bit_count), limb_type, allocator_type>;

      local_distribution_type distribution;

      RandomEngineType local_generator(generator);

      const bool miller_rabin_result_is_ok = miller_rabin(p, 25U, distribution, local_generator);

      return miller_rabin_result_is_ok;
    }

  protected:
    my_uintwide_t my_p;
    my_uintwide_t my_q;
    my_uintwide_t my_r;
    my_uintwide_t my_m;
    my_uintwide_t phi_of_m;
    public_key_type     public_key;
    private_key_type    private_key;

    rsa_base(const my_uintwide_t& p_in,
              const my_uintwide_t& q_in,
              const my_uintwide_t& r_in) : my_p       (p_in),
                                          my_q       (q_in),
                                          my_r       (r_in),
                                          my_m       (my_p * my_q),
                                          phi_of_m   (),
                                          public_key (),
                                          private_key()
    {
      public_key = public_key_type { my_r, my_m };
    }

    void calculate_private_key()
    {
      my_uintwide_t a = phi_of_m;
      my_uintwide_t b = my_r;

      my_uintwide_t x(0U);
      my_uintwide_t s(0U);

      euclidean::extended_euclidean(a, b, &x, &s);

      s = is_neg(s) ? make_positive(s, phi_of_m) : s;

      private_key = private_key_type { s, my_p, my_q };
    }

  private:
    rsa_base() = delete;

    static bool is_neg(const my_uintwide_t& x)
    {
      const bool x_is_neg = ((x & (my_uintwide_t(1U) << (std::numeric_limits<my_uintwide_t>::digits - 1))) != 0);

      return x_is_neg;
    }

    static my_uintwide_t make_positive(const my_uintwide_t& numb, const my_uintwide_t& mod)
    {
      my_uintwide_t tmp = numb;

      while(is_neg(tmp))
      {
        tmp += mod;
      }

      return tmp;
    }
  };

  template<const std::size_t RsaBitCount,
           typename LimbType = std::uint32_t>
  class rsa_fips : public rsa_base<RsaBitCount, LimbType>
  {
  private:
    using base_class_type = rsa_base<RsaBitCount, LimbType>;

  public:
    rsa_fips(const typename base_class_type::my_uintwide_t& p_in,
             const typename base_class_type::my_uintwide_t& q_in,
             const typename base_class_type::my_uintwide_t& r_in)
      : base_class_type(p_in, q_in, r_in)
    {
      const typename base_class_type::my_uintwide_t my_one(1U);

      base_class_type::phi_of_m = lcm(base_class_type::my_p - my_one,
                                      base_class_type::my_q - my_one);

      base_class_type::calculate_private_key();
    }

    rsa_fips(const rsa_fips& other) : base_class_type(other) { }

    rsa_fips(rsa_fips&& other) : base_class_type(other) { }

    rsa_fips& operator=(const rsa_fips& other)
    {
      static_cast<void>(base_class_type::operator=(other));

      return *this;
    }

    rsa_fips& operator=(rsa_fips&& other)
    {
      static_cast<void>(base_class_type::operator=(other));

      return *this;
    }
  };

  template<const std::size_t RsaBitCount,
           typename LimbType = std::uint32_t>
  class rsa_traditional : public rsa_base<RsaBitCount, LimbType>
  {
  private:
    using base_class_type = rsa_base<RsaBitCount, LimbType>;

  public:
    rsa_traditional(const typename base_class_type::my_uintwide_t& p_in,
             const typename base_class_type::my_uintwide_t& q_in,
             const typename base_class_type::my_uintwide_t& r_in)
      : base_class_type(p_in, q_in, r_in)
    {
      const typename base_class_type::my_uintwide_t my_one(1U);

      base_class_type::phi_of_m = (  (base_class_type::my_p - my_one)
                                   * (base_class_type::my_q - my_one));

      base_class_type::calculate_private_key();
    }

    rsa_traditional(const rsa_traditional& other) : base_class_type(other) { }

    rsa_traditional(rsa_traditional&& other) : base_class_type(other) { }

    rsa_traditional& operator=(const rsa_traditional& other)
    {
      static_cast<void>(base_class_type::operator=(other));

      return *this;
    }

    rsa_traditional& operator=(rsa_traditional&& other)
    {
      static_cast<void>(base_class_type::operator=(other));

      return *this;
    }
  };
}

bool math::wide_integer::example012_rsa_crypto()
{
  // Consider lines 25-30 in the file "KeyGen_186-3.rsp".

  // e    = 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000001
  // seed = e5f707e49c4e7cc8fb202b5cd957963713f1c4726677c09b6a7f5dfe
  // p    = ff03b1a74827c746db83d2eaff00067622f545b62584321256e62b01509f10962f9c5c8fd0b7f5184a9ce8e81f439df47dda14563dd55a221799d2aa57ed2713271678a5a0b8b40a84ad13d5b6e6599e6467c670109cf1f45ccfed8f75ea3b814548ab294626fe4d14ff764dd8b091f11a0943a2dd2b983b0df02f4c4d00b413
  // q    = dacaabc1dc57faa9fd6a4274c4d588765a1d3311c22e57d8101431b07eb3ddcb05d77d9a742ac2322fe6a063bd1e05acb13b0fe91c70115c2b1eee1155e072527011a5f849de7072a1ce8e6b71db525fbcda7a89aaed46d27aca5eaeaf35a26270a4a833c5cda681ffd49baa0f610bad100cdf47cc86e5034e2a0b2179e04ec7
  // n    = d9f3094b36634c05a02ae1a5569035107a48029e39b3c6a1853817f063e18e761c0c538e55ff2c7e53d603bb35cabb3b8d07f82aa0afdeaf7441fcf6746c5bcaaa2cde398ad73edb9c340c3ffca559132581eaf8f65c13d02f3445a932a3e1fadb5912f7553edec5047e4d0ed06ee87effc549e194d38e06b73a971c961688ba2d4aa4f450d2523372f317d41d06f9f0360e962ce953a69f36c53c370799fcfba195e8f691ebe862f84ae4bbd7747bc14499bd0efffcdc7154325908355c2ffc5b3948b8102b33aa2420381470e4ee858380ff0eea58288516c263f6d51dbbd0e477d1393a0a3ee60e1fde4330856665bf522006608a6104c138c0f39e09c4c5
  // d    = 1bf009caddc664b4404d59711fde16d7c55822449de1c5a084d22ed5791fdaa37ea538867fc91a17e6856e277c2dedd70ca8bf6ec44b0e729917a88e5988cc561d948ddeea46e21fd8ff46cce7657c94bfb1bdf40b3b30d4595a8bc3a15f1d4ad4c665c09b3b265ba19cdb0b89cbaadd0097ff52e9f6e594f86829c5bb4e9ba0200f12fa6dc60fd28dec0d194f08deb50f5a7749540160d6e8338e75b11165b76f4650c2fcce08f979ad9941daedaa5e328473bf712f8f549c36967f5e15477dc643d1f48d563139134e5cdc4bb84f9782cd5125e864e067cb980290f215cb41090e297bac2714efba61115d85613851c2de50a82f4ab526b88c61b7c9a0b589

  using rsa_type          = local_rsa::rsa_fips<2048U>;
  using rsa_integral_type = typename rsa_type::my_uintwide_t;

  const rsa_integral_type p("0xFF03B1A74827C746DB83D2EAFF00067622F545B62584321256E62B01509F10962F9C5C8FD0B7F5184A9CE8E81F439DF47DDA14563DD55A221799D2AA57ED2713271678A5A0B8B40A84AD13D5B6E6599E6467C670109CF1F45CCFED8F75EA3B814548AB294626FE4D14FF764DD8B091F11A0943A2DD2B983B0DF02F4C4D00B413");
  const rsa_integral_type q("0xDACAABC1DC57FAA9FD6A4274C4D588765A1D3311C22E57D8101431B07EB3DDCB05D77D9A742AC2322FE6A063BD1E05ACB13B0FE91C70115C2B1EEE1155E072527011A5F849DE7072A1CE8E6B71DB525FBCDA7A89AAED46D27ACA5EAEAF35A26270A4A833C5CDA681FFD49BAA0F610BAD100CDF47CC86E5034E2A0B2179E04EC7");
  const rsa_integral_type e("0x100000001");
  const rsa_integral_type n("0xD9F3094B36634C05A02AE1A5569035107A48029E39B3C6A1853817F063E18E761C0C538E55FF2C7E53D603BB35CABB3B8D07F82AA0AFDEAF7441FCF6746C5BCAAA2CDE398AD73EDB9C340C3FFCA559132581EAF8F65C13D02F3445A932A3E1FADB5912F7553EDEC5047E4D0ED06EE87EFFC549E194D38E06B73A971C961688BA2D4AA4F450D2523372F317D41D06F9F0360E962CE953A69F36C53C370799FCFBA195E8F691EBE862F84AE4BBD7747BC14499BD0EFFFCDC7154325908355C2FFC5B3948B8102B33AA2420381470E4EE858380FF0EEA58288516C263F6D51DBBD0E477D1393A0A3EE60E1FDE4330856665BF522006608A6104C138C0F39E09C4C5");
  const rsa_integral_type d("0x1BF009CADDC664B4404D59711FDE16D7C55822449DE1C5A084D22ED5791FDAA37EA538867FC91A17E6856E277C2DEDD70CA8BF6EC44B0E729917A88E5988CC561D948DDEEA46E21FD8FF46CCE7657C94BFB1BDF40B3B30D4595A8BC3A15F1D4AD4C665C09B3B265BA19CDB0B89CBAADD0097FF52E9F6E594F86829C5BB4E9BA0200F12FA6DC60FD28DEC0D194F08DEB50F5A7749540160D6E8338E75B11165B76F4650C2FCCE08F979AD9941DAEDAA5E328473BF712F8F549C36967F5E15477DC643D1F48D563139134E5CDC4BB84F9782CD5125E864E067CB980290F215CB41090E297BAC2714EFBA61115D85613851C2DE50A82F4AB526B88C61B7C9A0B589");

  bool result_is_ok = true;

  {
    using local_random_engine_type = std::mt19937;

    local_random_engine_type generator(static_cast<typename std::mt19937::result_type>(std::clock()));

    const bool p_is_prime = rsa_type::is_prime(p, generator);

    result_is_ok &= p_is_prime;
  }

  result_is_ok &= rsa_type::is_prime(q);

  const rsa_type rsa(p, q, e);

  result_is_ok &= (   (rsa.get_p() == p)
                   && (rsa.get_q() == q)
                   && (rsa.get_d() == d));

  result_is_ok &= (n == (p * q));
  result_is_ok &= (n == rsa.get_n());

  // Select "abc" as the sample string to encrypt.
  const std::string in_str("abc");

  const typename rsa_type::crypto_string out_str = rsa.encrypt(in_str);
  const std::string                     res_str = rsa.decrypt(out_str);

  const char res_ch_a_manual = char(static_cast<typename rsa_integral_type::limb_type>(powm(out_str[0U], d, n)));
  const char res_ch_b_manual = char(static_cast<typename rsa_integral_type::limb_type>(powm(out_str[1U], d, n)));
  const char res_ch_c_manual = char(static_cast<typename rsa_integral_type::limb_type>(powm(out_str[2U], d, n)));

  result_is_ok &= (res_str         == "abc");
  result_is_ok &= (res_ch_a_manual == char('a'));
  result_is_ok &= (res_ch_b_manual == char('b'));
  result_is_ok &= (res_ch_c_manual == char('c'));

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example012_rsa_crypto();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif

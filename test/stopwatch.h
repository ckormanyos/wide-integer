///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STOPWATCH_2024_03_28_H // NOLINT(llvm-header-guard)
  #define STOPWATCH_2024_03_28_H

  #include <cstdint>
  #include <ctime>

  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define STOPWATCH_NODISCARD
  #else
  #if (defined(__cplusplus) && (__cplusplus >= 201703L))
  #define STOPWATCH_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define STOPWATCH_NODISCARD
  #endif
  #endif

  // See also: https://godbolt.org/z/37a4n9f4Y

  namespace concurrency {

  struct stopwatch
  {
  public:
    using time_point_type = std::uintmax_t;

    stopwatch()
    {
      reset();
    }

    auto reset() -> void
    {
      timespec ts { };

      timespec_get(&ts, TIME_UTC);

      m_start =
        static_cast<time_point_type>
        (
            static_cast<time_point_type>(static_cast<time_point_type>(ts.tv_sec) * UINTMAX_C(1000000000))
          + static_cast<time_point_type>(ts.tv_nsec)
        );
    }

    template<typename RepresentationRequestedTimeType>
    static auto elapsed_time(const stopwatch& my_stopwatch) noexcept -> RepresentationRequestedTimeType
    {
      using local_time_type = RepresentationRequestedTimeType;

      return
        local_time_type
        {
            static_cast<local_time_type>(my_stopwatch.elapsed())
          / local_time_type { UINTMAX_C(1000000000) }
        };
    }

  private:
    time_point_type m_start { }; // NOLINT(readability-identifier-naming)

    STOPWATCH_NODISCARD auto elapsed() const -> time_point_type
    {
      timespec ts { };

      timespec_get(&ts, TIME_UTC);

      time_point_type
        stop
        {
          static_cast<time_point_type>
          (
              static_cast<time_point_type>(static_cast<time_point_type>(ts.tv_sec) * UINTMAX_C(1000000000))
            + static_cast<time_point_type>(ts.tv_nsec)
          )
        };

      const std::uintmax_t
        elapsed_ns
        {
          static_cast<time_point_type>
          (
            stop - m_start
          )
        };

      return elapsed_ns;
    }
  };

  } // namespace concurrency

#endif // STOPWATCH_2024_03_28_H

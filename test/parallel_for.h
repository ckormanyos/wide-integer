///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PARALLEL_FOR_2017_12_18_H_
  #define PARALLEL_FOR_2017_12_18_H_

  #include <algorithm>
  #include <thread>
  #include <vector>

  namespace my_concurrency
  {
    template<typename index_type,
             typename callable_function_type>
    void parallel_for(index_type             start,
                      index_type             end,
                      callable_function_type parallel_function)
    {
      // Estimate the number of threads available.
      static const unsigned int number_of_threads_hint = std::thread::hardware_concurrency();

      static const unsigned int number_of_threads =
        ((number_of_threads_hint == 0U) ? 4U : number_of_threads_hint);

      // Set the size of a slice for the range functions.
      index_type n = index_type(end - start) + index_type(1);

      index_type slice =
        static_cast<index_type>(std::round(n / static_cast<double> (number_of_threads)));

      slice = (std::max)(slice, index_type(1));

      // Inner loop.
      auto launch_range =
        [&parallel_function](index_type index_lo, index_type index_hi)
        {
          for(index_type i = index_lo; i < index_hi; ++i)
          {
            parallel_function(i);
          }
        };

      // Create the thread pool and launch the jobs.
      std::vector<std::thread> pool;

      pool.reserve(number_of_threads);

      index_type i1 = start;
      index_type i2 = (std::min)(index_type(start + slice), end);

      for(unsigned i = 0U; ((index_type(i + 1) < number_of_threads) && (i1 < end)); ++i)
      {
        pool.emplace_back(launch_range, i1, i2);

        i1 = i2;

        i2 = (std::min)(index_type(i2 + slice), end);
      }

      if(i1 < end)
      {
        pool.emplace_back(launch_range, i1, end);
      }

      // Wait for the jobs to finish.
      for(std::thread& thread_in_pool : pool)
      {
        if(thread_in_pool.joinable())
        {
          thread_in_pool.join();
        }
      }
    }

    // Provide a serial version for easy comparison.
    template<typename index_type,
             typename callable_function_type>
    void sequential_for(index_type             start,
                        index_type             end,
                        callable_function_type sequential_function)
    {
      for(index_type i = start; i < end; i++)
      {
        sequential_function(i);
      }
    }
  } // namespace my_concurrency

#endif // PARALLEL_FOR_2017_12_18_H_

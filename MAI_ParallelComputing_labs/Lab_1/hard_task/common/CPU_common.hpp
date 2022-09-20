#ifndef LAB1_COMMON_CPU_COMMON_HPP_
#define LAB1_COMMON_CPU_COMMON_HPP_

#include <chrono>

namespace cpu_utils {

// Time point object 
using time_point = std::chrono::system_clock::time_point;

/**
 * @brief Enumeration of possible time units
 */
enum class TimeUnit {
    Second,
    Millisecond,
    Microsecond,
    Nanosecond
};

/**
 * @brief Get the time object
 * 
 * @return time_point - now time from system clock
 */
time_point get_time() { return std::chrono::system_clock::now(); };


/**
 * @brief Get the duration object
 * 
 * @param end_point - end time point
 * @param start_point - start time point
 * @param unit - Time unit
 * @return int - count of duration in time units
 */
int get_duration(time_point& end_point, time_point& start_point, TimeUnit unit) {
    switch (unit)
    {
    case TimeUnit::Second:
        return std::chrono::duration_cast<std::chrono::seconds>(end_point - start_point).count();
    case TimeUnit::Millisecond:
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_point - start_point).count();
    case TimeUnit::Microsecond:
        return std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point).count();
    case TimeUnit::Nanosecond:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_point - start_point).count(); 
    }
    return -1;
}

} // namespace cpu_utils

#endif // LAB1_COMMON_CPU_COMMON_HPP_
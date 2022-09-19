#include "cpu_implementation.hpp"
#include <omp.h>
#include <assert.h>
#include <iostream>
#include "../common/CPU_common.hpp"
#include "../common/GLOB_common.hpp"
#include <math.h>


/**
 * @brief Set the up threads object
 * 
 * @param threads_number - number of threads(optional). If value is equal 0, then setted automatically. (max)
 */
void setup_threads(unsigned int threads_number);

/**
 * @brief Calculates the square root of each element of the array using the OpenMP.
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CPU in microseconds
 */
int CPU_sqrt_array(float* array, int num_of_elements, OutMode out_mode) {

    // Calculate
    cpu_utils::time_point start = cpu_utils::get_time();
    {
        #pragma omp for
        for (unsigned int i = 0; i < num_of_elements; i++) {
            array[i] = sqrt(array[i]);
        }
    }
    cpu_utils::time_point end = cpu_utils::get_time();


    // Get duration
    int duration_mc = cpu_utils::get_duration(end, start, cpu_utils::TimeUnit::Microsecond);
    
    // Output results if needed 
    switch (out_mode) {
        case OutMode::FormattedOutput:
        {
            std::cout << "CPU time simple (microseconds): " << duration_mc << std::endl;
            global_utils::save_array_to_stdout(array, num_of_elements);
            break;
        }
        case OutMode::TableOutput:
        {
            std::cout << num_of_elements << ";" << duration_mc << std::endl;
            break;
        }
    }

    return duration_mc;
}

void setup_threads(unsigned int threads_number) {

    // Default: threads_number
    int real_threads_count{ static_cast<int>(threads_number) };
    
    std::cout << "   ::: OpenMP preset :::   " << std::endl;
    
    
    if (threads_number == 0) {
        real_threads_count = omp_get_max_threads();
        std::cout << "\tNumber of threads setted automattically.";
    } 
    else
        std::cout << "\tNumber of threads setted by user.";
    
    std::cout << "\tNumber of threads: " << real_threads_count << std::endl;

    omp_set_num_threads(real_threads_count);
}

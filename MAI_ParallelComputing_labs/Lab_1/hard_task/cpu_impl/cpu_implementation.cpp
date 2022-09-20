#include "cpu_implementation.hpp"
#include <omp.h>
#include <assert.h>
#include <iostream>
#include <math.h>

#include "../common/CPU_common.hpp"
#include "../common/GLOB_common.hpp"

/**
 * @brief Set the up threads object
 * 
 * @param threads_number - number of threads(optional). If value is equal 0, then setted automatically. (max)
 */
void setup_threads(unsigned int threads_number=0);

/**
 * @brief Calculates the square root of each element of the array using the OpenMP.
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CPU in microseconds
 */
int CPU_add_matrices(float* dst, float* mat1, float* mat2, int N, int M, OutMode out_mode) {

    setup_threads();

    // Calculate
    cpu_utils::time_point start = cpu_utils::get_time();
    {
        // N - rows
        // M - cols
        #pragma omp for
        for(int i=0; i < N * M; i++) {
            dst[i] = mat1[i] + mat2[i];
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
            global_utils::save_array_to_stdout(dst, N * M);
            break;
        }
        case OutMode::TableOutput:
        {
            std::cout << N * M << ";" << duration_mc << std::endl;
            break;
        }
    }

    return duration_mc;
}

void setup_threads(unsigned int threads_number) {

    // Default: threads_number
    int real_threads_count{ static_cast<int>(threads_number) };
    
    if (threads_number == 0) {
        real_threads_count = omp_get_max_threads();
    } 

    omp_set_num_threads(real_threads_count);
}

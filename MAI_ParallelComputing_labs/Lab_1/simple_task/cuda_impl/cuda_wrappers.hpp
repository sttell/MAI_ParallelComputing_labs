#include "../common/out_mode.hpp"

/**
 * @brief Calculates the square root of each element of the array using the CUDA kernel
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CUDA kernel in microseconds
 */
int CUDA_sqrt_array(float* array, int num_of_elements, OutMode out_mode=OutMode::FormattedOutput);
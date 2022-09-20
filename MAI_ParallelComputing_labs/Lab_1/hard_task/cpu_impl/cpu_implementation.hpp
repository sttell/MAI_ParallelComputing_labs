#include "../common/out_mode.hpp"


/**
 * @brief Calculates the square root of each element of the array using the OpenMP.
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CPU in microseconds
 */
int CPU_add_matrices(float* dst, float* mat1, float* mat2, int N, int M, OutMode out_mode=OutMode::FormattedOutput);
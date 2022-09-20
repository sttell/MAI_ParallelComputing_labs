#ifndef LAB1_COMMON_CUDA_COMMON_HPP_
#define LAB1_COMMON_CUDA_COMMON_HPP_

#include <cuda.h>

#define checkCudaErrors(val) check( (val), #val, __FILE__, __LINE__)

/**
 * @brief Check cuda errors
 * 
 * @tparam T - Error type
 * @param err - error object
 * @param func - checkable function
 * @param file - source filename
 * @param line - line in source filename
 */
template<typename T>
void check(T err, const char* const func, const char* const file, const int line) {
  if (err != cudaSuccess) {
    std::cerr << "CUDA error at: " << file << ":" << line << std::endl;
    std::cerr << cudaGetErrorString(err) << " " << func << std::endl;
    exit(1);
  }
}

namespace gpu_utils {


} // namespace gpu_utils

#endif // LAB1_COMMON_CUDA_COMMON_HPP_

#include <iostream>
#include <string>
#include "cuda_wrappers.hpp"
#include "../common/CUDA_common.hpp"
#include "../common/GLOB_common.hpp"

#define THREAD_NUM 1024


/**
 * @brief Calculate sqrt for all element in array.
 *
 * @param data - float array with number
 */
__global__ void cuda_sqrt(float* data) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    data[idx] = sqrt(data[idx]);
}


/**
 * @brief Calculates the square root of each element of the array using the CUDA kernel
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CUDA kernel in microseconds
 */
int CUDA_sqrt_array(float* array, int num_of_elements, OutMode out_mode) {
    
    if (num_of_elements < 1) 
        throw std::runtime_error("Number of array elements must be only > 1.");
    
    int num_bytes = num_of_elements * sizeof(float);

    dim3 threads(THREAD_NUM);
    dim3 blocks(num_of_elements / THREAD_NUM);

    cudaEvent_t start, stop;
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
    }

    // Memory allocate
    float* in_dev;
    {
        checkCudaErrors(cudaMalloc(&in_dev, num_bytes));
        checkCudaErrors(cudaMemcpy(in_dev, array, num_bytes, cudaMemcpyHostToDevice));
    }

    // Calculation
    {
        cudaEventRecord(start);
        cuda_sqrt<<<blocks, threads>>>(in_dev);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaDeviceSynchronize(); 
        checkCudaErrors(cudaGetLastError());

    }
    
    // Memory deallocate
    {
        checkCudaErrors(cudaMemcpy(array, in_dev, num_bytes, cudaMemcpyDeviceToHost));
        checkCudaErrors(cudaFree(in_dev));
    }

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    int microseconds = static_cast<int>(1000.f * milliseconds);

    switch (out_mode) {
        case OutMode::FormattedOutput:
        {
            std::cout << "CUDA time simple (microseconds): " << microseconds << std::endl;
            global_utils::save_array_to_stdout(array, num_of_elements);
            break;
        }
        case OutMode::TableOutput:
        {
            std::cout << num_of_elements << ";" << microseconds << std::endl;
            break;
        }
    }

    return microseconds;
}

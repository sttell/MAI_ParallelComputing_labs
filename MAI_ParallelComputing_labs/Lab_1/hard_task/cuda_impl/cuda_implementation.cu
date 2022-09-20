
#include <iostream>
#include <string>
#include "cuda_wrappers.hpp"
#include "../common/CUDA_common.hpp"
#include "../common/GLOB_common.hpp"

#define MAX_THREADS_PER_BLOCK 1024
#define BLOCK_SIZE 32

/**
 * @brief Calculate sqrt for all element in array.
 *
 * @param data - float array with number
 */
__global__ void cuda_sqrt(float* dst, float* mat1, float* mat2, int cols) {
    int idx = (blockIdx.y * blockDim.y + threadIdx.y) * cols + blockIdx.x * blockDim.x + threadIdx.x;
    dst[idx] = mat1[idx] + mat2[idx];    
}


/**
 * @brief Calculates the square root of each element of the array using the CUDA kernel
 * 
 * @param array           - Array with values
 * @param num_of_elements - Number of elements in the array
 * @param out_mode        - Output mode of results
 * @return int - Net operating time of CUDA kernel in microseconds
 */
int CUDA_sqrt_array(float* dst, float* mat1, float* mat2, int N, int M, OutMode out_mode) {
    
    if (BLOCK_SIZE * BLOCK_SIZE > MAX_THREADS_PER_BLOCK) {
        throw std::runtime_error("Block size is soo big. Expected size: 1024 threads.");
    }

    if (N < 1 || M < 1) 
        throw std::runtime_error("Number of array elements must be only > 1.");
    
    int sizeof_matrix = N * M * sizeof(float);

    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
    dim3 blocks(N / threads.x, M / threads.y);

    cudaEvent_t start, stop;
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
    }

    // Memory allocate
    float* out_dev;
    float* in1_dev;
    float* in2_dev;
    {
        checkCudaErrors(cudaMalloc(&in1_dev, sizeof_matrix));
        checkCudaErrors(cudaMemcpy(in1_dev, mat1, sizeof_matrix, cudaMemcpyHostToDevice));

        checkCudaErrors(cudaMalloc(&in2_dev, sizeof_matrix));
        checkCudaErrors(cudaMemcpy(in2_dev, mat2, sizeof_matrix, cudaMemcpyHostToDevice));

        checkCudaErrors(cudaMalloc(&out_dev, sizeof_matrix));
    }

    if (out_mode == OutMode::FormattedOutput) {
        std::cout << "Matrix size:  {" << N << ", " << M << "}\n";
        std::cout << "CUDA threads: {" << threads.x << ", " << threads.y << "}\n";
        std::cout << "CUDA blocks : {" << blocks.x  << ", " << blocks.y << "}\n";
    }

    // Calculation
    {
        cudaEventRecord(start);
        cuda_sqrt<<<blocks, threads>>>(out_dev, in1_dev, in2_dev, M);
        
        checkCudaErrors(cudaGetLastError());

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaDeviceSynchronize(); 
        

    }
    
    // Memory deallocate
    {
        checkCudaErrors(cudaMemcpy(dst, out_dev, sizeof_matrix, cudaMemcpyDeviceToHost));
        checkCudaErrors(cudaFree(out_dev));
        checkCudaErrors(cudaFree(in1_dev));
        checkCudaErrors(cudaFree(in2_dev));
    }

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    int microseconds = static_cast<int>(1000.f * milliseconds);

    switch (out_mode) {
        case OutMode::FormattedOutput:
        {
            std::cout << "CUDA time simple (microseconds): " << microseconds << std::endl;
            global_utils::save_array_to_stdout(dst, N * M);
            break;
        }
        case OutMode::TableOutput:
        {
            std::cout << N * M << ";" << microseconds << std::endl;
            break;
        }
    }

    return microseconds;
}

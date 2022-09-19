#include <iostream>


// Settings for performance testing
// The size of the array at each iteration of testing is calculated by the formula:
//           SIZE[i] = N_MINIMAL * COEFF[i]
//           COEFF[i] = COEFF[i - 1] + N_MUL_STEP
// For ex:   
//      N_MUL_STEP = 5          i |  0   |    1     |    2      | ...
//      N_MINIMAL  = 1024      ---------------------------------------
//                              N | 1024 | 1024 * 5 | 1024 * 10 | ...


#define NUM_TESTS 100      // Number of tests for performance mode
#define N_MINIMAL 1024     // Minimal size of test array
#define N_MUL_STEP 5       // Multiplication factor step for performance test. New_coeff = Old_coeff + N_MUL_STEP
#define N_MUL_MAXV 2000    // Maximum multiplication factor.


/*
 * ---------------------------------------------
 *             Preset for CPU Mode
 * ---------------------------------------------
 */
#ifdef CPU_MODE_ENABLE

#include "cpu_impl/cpu_implementation.hpp"
#define FUNC_NAME CPU_sqrt_array

#endif // CPU_MODE_ENABLE


/*
 * ---------------------------------------------
 *             Preset for GPU Mode
 * ---------------------------------------------
 */
#ifdef GPU_MODE_ENABLE

#include "cuda_impl/cuda_wrappers.hpp"
#define FUNC_NAME CUDA_sqrt_array

#endif // GPU_MODE_ENABLE


/*
 * ---------------------------------------------
 *          Preset for Verify mode
 * ---------------------------------------------
 */
#ifdef VERIFY_ENABLE
#include "verify/verify.hpp"
void verify_test();
#endif // VERIFY_ENABLE



/*
 * ---------------------------------------------
 *      Preset for Performance test mode
 * ---------------------------------------------
 */
#ifdef PERFORMANCE_ENABLE
void performance_test();
#endif // PERFORMANCE_ENABLE


int main(int argc, char** argv) {
    
    #ifdef PERFORMANCE_ENABLE
    performance_test();
    #endif // PERFORMANCE_ENABLE

    #ifdef VERIFY_ENABLE
    verify_test();
    #endif // VERIFY_ENABLE

    return 0;
}

#ifdef VERIFY_ENABLE
void verify_test() {

    // Create 2 arrays.
    int N = N_MINIMAL;
    float* verify_array = new float[N];
    float* result_array = new float[N];
    
    for(int i=0; i < N; i++) {
        verify_array[i] = i;
        result_array[i] = i;
    }

    // Create verification result
    get_verify_array(verify_array, N);

    // Create test result
    int duration = FUNC_NAME(result_array, N, OutMode::Mute);
    
    // Compare arrays
    bool is_equal = true;

    std::cout << "Verify | Result" << std::endl;
    for (int i=0; i < N; i++) {
        
        std::cout << verify_array[i] << " - " << result_array[i] << std::endl;

        is_equal = is_equal && (std::abs(verify_array[i] - result_array[i]) < 0.000001);
    }
    std::cout << "Verifying result: ";
    if (is_equal) std::cout << " OK\n";
    else          std::cout << " FAIL\n";

    // Deallocate memory
    delete[] verify_array;
    delete[] result_array;
}
#endif // VERIFY_ENABLE


#ifdef PERFORMANCE_ENABLE
void performance_test() {

    // Calculate maximum size
    int N_MAX = N_MINIMAL * N_MUL_MAXV;

    // Create and fill max size array
    float* array = new float[N_MAX];
    for(int i=0; i < N_MAX; i++)
        array[i] = i;
    

    // Testing
    for (int coeff = 1; coeff < N_MUL_MAXV; coeff += N_MUL_STEP) {
        
        // Current number of elements
        int N = N_MINIMAL * coeff;
        
        // Summary duration for all tests
        int duration_summary = 0;
        
        // Run tests
        for (int i=0; i < NUM_TESTS; i++) {
            int duration = FUNC_NAME(array, N, OutMode::Mute);
            duration_summary += duration;
        }
        
        // Create table frame
        std::cout << N << ";" << (duration_summary / NUM_TESTS) << std::endl;
       
    }

    // Deallocate memory
    delete[] array;
}
#endif // PERFORMANCE_ENABLE
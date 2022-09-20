#ifndef LAB1_COMMON_GLOB_COMMON_HPP_
#define LAB1_COMMON_GLOB_COMMON_HPP_

#include <fstream>
#include <iostream>

namespace global_utils {

/**
 * @brief Save float array to file
 * 
 * @param filename - path to output file
 * @param array    - pointer to array
 * @param size     - number of elements in array
 */
void save_array_to_file(const char* filename, float* array, int size) {
    std::ofstream stream(filename);
    
    if (!stream.is_open()) 
        throw std::runtime_error("Error opening output file.");

    for(int i=0; i < size; i++) {
        stream << array[i] << std::endl;
    }

    stream.close();
}

/**
 * @brief Dump array to standard output
 * 
 * @param array    - pointer to array
 * @param size     - number of elements in array
 */
void save_array_to_stdout(float* array, int size) {

    for(int i=0; i < size; i++) {
        std::cout << array[i] << std::endl;
    }
}

} // namespace global_utils

#endif // LAB1_COMMON_GLOB_COMMON_HPP_
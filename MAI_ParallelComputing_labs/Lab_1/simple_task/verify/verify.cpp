#include <math.h>

void get_verify_array(float* array, int num_of_elements) {

    for(int i=0; i < num_of_elements; i++) {
        array[i] = sqrt(array[i]);
    }

}
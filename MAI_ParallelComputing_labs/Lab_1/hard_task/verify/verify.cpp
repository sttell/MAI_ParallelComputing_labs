void get_verify_array(float* result, float* matrix1, float* matrix2, int N, int M) {

    for(int i=0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            result[i * M + j] = matrix1[i * M + j] + matrix2[i * M + j];
        }
    }
}
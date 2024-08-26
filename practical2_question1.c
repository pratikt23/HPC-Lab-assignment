#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void vector_scalar_addition(float *vector, float scalar, int size, int num_threads) {
    // Set the number of threads to use in OpenMP
    omp_set_num_threads(num_threads);

    // Parallel region with OpenMP
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int size;
    float scalar;
    int num_threads;

    // Initialize vector size, scalar value, and number of threads
    printf("Enter the size of the vector: ");
    scanf("%d", &size);

    printf("Enter the scalar value: ");
    scanf("%f", &scalar);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Allocate memory for the vector
    float *vector = (float *)malloc(size * sizeof(float));

    // Initialize the vector with some values
    for (int i = 0; i < size; i++) {
        vector[i] = i * 1.0;  // Example initialization
    }

    // Record the start time
    double start_time = omp_get_wtime();

    // Perform vector-scalar addition
    vector_scalar_addition(vector, scalar, size, num_threads);

    // Record the end time
    double end_time = omp_get_wtime();

    // Output the time taken
    printf("Time taken with %d threads: %f seconds\n", num_threads, end_time - start_time);

    // Clean up
    free(vector);

    return 0;
}

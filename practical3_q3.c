#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to perform scalar addition
void scalar_addition(int *vector, int size, int scalar, int chunk_size, int schedule_type) {
    if (schedule_type == 0) {
        // STATIC schedule
        #pragma omp parallel for schedule(static, chunk_size)
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }
    } else {
        // DYNAMIC schedule
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }
    }
}

int main() {
    int size = 200;
    int scalar = 5;
    int chunk_sizes[] = {1, 2, 4, 10, 20};
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    int *vector = (int *)malloc(size * sizeof(int));

    // Initialize vector with random values
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
    }

    // Test STATIC scheduling
    printf("STATIC Scheduling:\n");
    for (int c = 0; c < num_chunks; c++) {
        int chunk_size = chunk_sizes[c];
        double start_time = omp_get_wtime();
        scalar_addition(vector, size, scalar, chunk_size, 0);
        double end_time = omp_get_wtime();
        printf("Chunk Size: %d, Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    // Reinitialize vector for next test
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
    }

    // Test DYNAMIC scheduling
    printf("\nDYNAMIC Scheduling:\n");
    for (int c = 0; c < num_chunks; c++) {
        int chunk_size = chunk_sizes[c];
        double start_time = omp_get_wtime();
        scalar_addition(vector, size, scalar, chunk_size, 1);
        double end_time = omp_get_wtime();
        printf("Chunk Size: %d, Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    // Demonstrate nowait clause
    printf("\nDemonstrating NOWAIT Clause:\n");
    #pragma omp parallel
    {
        #pragma omp for schedule(static, 1)
        for (int i = 0; i < size / 2; i++) {
            vector[i] += scalar;
        }
        #pragma omp for schedule(static, 1) nowait
        for (int i = size / 2; i < size; i++) {
            vector[i] += scalar;
        }
    }
    
    // Clean up
    free(vector);
    return 0;
}

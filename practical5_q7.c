#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000000

int main() {
    int i, total_sum = 0;
    int array[ARRAY_SIZE];

    // Initialize the array with some values
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1;  // simple values for testing, each element is 1
    }
    // Start measuring time
    double start_time, end_time;
    // --- UNSYNCHRONIZED VERSION (Data race issue) ---
    total_sum = 0;  
    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (i = 0; i < ARRAY_SIZE; i++) {
        total_sum += array[i];  // Race condition here!
    }

    end_time = omp_get_wtime();
    printf("Unsynchronized total_sum: %d, Time taken: %f seconds\n", total_sum, end_time - start_time);

    // --- SYNCHRONIZED VERSION USING CRITICAL SECTION ---
    total_sum = 0;  // Reset total_sum
    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (i = 0; i < ARRAY_SIZE; i++) {
        #pragma omp critical
        {
            total_sum += array[i];
        }
    }
    end_time = omp_get_wtime();
    printf("Synchronized total_sum using critical: %d, Time taken: %f seconds\n", total_sum, end_time - start_time);

    // --- SYNCHRONIZED VERSION USING ATOMIC DIRECTIVE ---
    total_sum = 0;  // Reset total_sum
    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (i = 0; i < ARRAY_SIZE; i++) {
        #pragma omp atomic
        total_sum += array[i];
    }

    end_time = omp_get_wtime();
    printf("Synchronized total_sum using atomic: %d, Time taken: %f seconds\n", total_sum, end_time - start_time);

    return 0;
}
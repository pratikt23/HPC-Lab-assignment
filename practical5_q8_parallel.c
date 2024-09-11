#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int array_size, num_threads;

    // Taking input from the user for array size and number of threads
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Dynamically allocating memory for the array
    int *array = (int *)malloc(array_size * sizeof(int));

    // Initialize array with values (1 to array_size)
    for (int i = 0; i < array_size; i++) {
        array[i] = i + 1;
    }

    // --- Parallel sum calculation using OpenMP reduction clause ---
    long long parallel_sum = 0;
    double start_parallel = omp_get_wtime();

    #pragma omp parallel for num_threads(num_threads) reduction(+:parallel_sum)
    for (int i = 0; i < array_size; i++) {
        parallel_sum += array[i];
    }

    double end_parallel = omp_get_wtime();
    double time_parallel = end_parallel - start_parallel;

    // Output the parallel sum and time taken
    printf("Parallel sum: %lld\n", parallel_sum);
    printf("Time taken for parallel sum: %f seconds\n", time_parallel);

    // Free the dynamically allocated memory
    free(array);

    return 0;
}

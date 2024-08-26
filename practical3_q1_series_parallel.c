// #include <stdio.h>
// #include <omp.h>  // Include OpenMP for timing

// #define N 1000  // Size of the vectors

// int main() {
//     int A[N], B[N];
//     int dot_product = 0;

//     // Initialize vectors A and B
//     for (int i = 0; i < N; i++) {
//         A[i] = i + 1;
//         B[i] = i + 1;
//     }

//     // Start the timer
//     double start_time = omp_get_wtime();

//     // Compute dot product
//     for (int i = 0; i < N; i++) {
//         dot_product += A[i] * B[i];
//     }

//     // End the timer
//     double end_time = omp_get_wtime();

//     printf("Dot Product (Serial): %d\n", dot_product);
//     printf("Time taken (Serial): %f seconds\n", end_time - start_time);

//     return 0;
// }

//parallel
#include <stdio.h>
#include <omp.h>  // Include OpenMP for parallelization and timing

#define N 1000  // Size of the vectors

int main() {
    int A[N], B[N];
    int dot_product = 0;
    int num_threads;

    // Ask user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Initialize vectors A and B
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
        B[i] = i + 1;
    }

    // Start the timer
    double start_time = omp_get_wtime();

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Compute dot product in parallel
    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < N; i++) {
        dot_product += A[i] * B[i];
    }

    // End the timer
    double end_time = omp_get_wtime();

    printf("Dot Product (Parallel): %d\n", dot_product);
    printf("Time taken (Parallel) with %d threads: %f seconds\n", num_threads, end_time - start_time);

    return 0;
}

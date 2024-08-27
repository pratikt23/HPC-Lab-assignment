#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compute the Fibonacci series up to n terms
void fibonacci_series(int n, int num_threads) {
    int *fib = (int *)malloc((n + 1) * sizeof(int));
    if (fib == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initialize first two Fibonacci numbers
    fib[0] = 0;
    if (n > 0) {
        fib[1] = 1;
    }

    // Compute Fibonacci numbers in parallel
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
    }

    // Print the Fibonacci series
    printf("Fibonacci series up to %d terms:\n", n + 1);
    for (int i = 0; i <= n; i++) {
        printf("Fibonacci(%d) = %d\n", i, fib[i]);
    }

    // Free allocated memory
    free(fib);
}

int main() {
    int n, num_threads;

    // Prompt the user for the number of terms
    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &n);

    // Check if the input is valid
    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1; // Exit with error code
    }

    // Prompt the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Compute and print the Fibonacci series
    double start = omp_get_wtime();
    fibonacci_series(n, num_threads);
    double end = omp_get_wtime();

    // Print the time taken
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}

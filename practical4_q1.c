#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compute Fibonacci numbers up to n using iterative approach
void fibonacci(int n, long long *fib) {
    // Base cases
    if (n >= 0) fib[0] = 0;
    if (n >= 1) fib[1] = 1;

    // Parallel section for Fibonacci computation
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }
}

int main() {
    int n = 10;  // Number of Fibonacci numbers to compute
    long long *fib = (long long *)malloc((n + 1) * sizeof(long long));

    // Measure execution time
    double start_time = omp_get_wtime();
    fibonacci(n, fib);
    double end_time = omp_get_wtime();

    // Print Fibonacci numbers
    for (int i = 0; i <= n; i++) {
        printf("Fibonacci(%d) = %lld\n", i, fib[i]);
    }
    
    // Print execution time
    printf("Time taken: %f seconds\n", end_time - start_time);

    free(fib);
    return 0;
}

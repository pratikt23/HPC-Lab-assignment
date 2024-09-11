#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int i, j, k;
    int N, num_threads;

    // Take matrix size and number of threads as input from the user
    printf("Enter the size of the matrix (N x N): ");
    scanf("%d", &N);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Dynamically allocate memory for the matrices
    double **a = (double **)malloc(N * sizeof(double *));
    double **b = (double **)malloc(N * sizeof(double *));
    double **c = (double **)malloc(N * sizeof(double *));
    
    for (i = 0; i < N; i++) {
        a[i] = (double *)malloc(N * sizeof(double));
        b[i] = (double *)malloc(N * sizeof(double));
        c[i] = (double *)malloc(N * sizeof(double));
    }

    // Initialize matrices a and b
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = (i + j) * 1.0;
            b[i][j] = (i - j) * 1.0;
            c[i][j] = 0.0;
        }
    }

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Start timing
    double start_time = omp_get_wtime();

    // Perform matrix multiplication using OpenMP
    #pragma omp parallel for private(i, j, k) shared(a, b, c)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // End timing
    double end_time = omp_get_wtime();

    // Print the time required for the matrix multiplication
    printf("Time required for matrix multiplication: %f seconds\n", end_time - start_time);

    // Free the allocated memory
    for (i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}

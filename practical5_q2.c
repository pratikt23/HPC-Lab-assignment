#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int i, j;
    int N, num_threads;

    // Take matrix size (N x N) and number of threads as input from the user
    printf("Enter the size of the matrix (N x N): ");
    scanf("%d", &N);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Dynamically allocate memory for the matrix and vectors
    double **matrix = (double **)malloc(N * sizeof(double *));
    double *vector = (double *)malloc(N * sizeof(double));
    double *result = (double *)malloc(N * sizeof(double));
    
    for (i = 0; i < N; i++) {
        matrix[i] = (double *)malloc(N * sizeof(double));
    }

    // Initialize the matrix and vector
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrix[i][j] = (i + j) * 1.0;  // Assigning some arbitrary values
        }
        vector[i] = i * 1.0;  // Initialize vector with arbitrary values
        result[i] = 0.0;      // Initialize result vector to 0
    }

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Start timing
    double start_time = omp_get_wtime();

    // Perform matrix-vector multiplication using OpenMP
    #pragma omp parallel for private(i, j) shared(matrix, vector, result)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    // End timing
    double end_time = omp_get_wtime();

    // Print the time required for matrix-vector multiplication
    printf("Time required for matrix-vector multiplication: %f seconds\n", end_time - start_time);

    // Free the allocated memory
    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}

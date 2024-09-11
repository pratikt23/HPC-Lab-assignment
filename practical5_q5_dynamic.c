#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 500  // Size of the matrices

int main() {
    int A[N][N], B[N][N], C[N][N];
    int i, j, k;
    double start_time, end_time;

    // Initialize matrices A and B with random values
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Initialize matrix C to zero
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // Start time for dynamic scheduling
    start_time = omp_get_wtime();

    // Parallel matrix multiplication with dynamic scheduling
    #pragma omp parallel for private(i, j, k) schedule(dynamic)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End time for dynamic scheduling
    end_time = omp_get_wtime();

    // Print matrices A, B, and resultant matrix C
    printf("Matrix A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d ", B[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant Matrix C:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d ", C[i][j]);
        }
        printf("\n");
    }

    // Print execution time
    printf("\nDynamic execution time: %f seconds\n", end_time - start_time);

    return 0;
}

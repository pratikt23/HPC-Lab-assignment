#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>  // Include this header for the time function

#define N 500  // Size of the matrix

void matrixMultiplyOpenMPStatic(int A[N][N], int B[N][N], int C[N][N], int num_threads) {
    #pragma omp parallel for num_threads(num_threads) schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    int num_threads;

    // Initialize matrices with random values
    srand(time(NULL));  // Initialize random seed
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    printf("Matrix A:\n");
    printMatrix(A);
    
    printf("\nMatrix B:\n");
    printMatrix(B);

    printf("\nEnter number of threads: ");
    scanf("%d", &num_threads);

    double start = omp_get_wtime();
    matrixMultiplyOpenMPStatic(A, B, C, num_threads);
    double end = omp_get_wtime();

    printf("\nResultant Matrix C:\n");
    printMatrix(C);

    printf("\nStatic scheduling execution time: %f seconds\n", end - start);

    return 0;
}

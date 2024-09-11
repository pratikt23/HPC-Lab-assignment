#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500 // Adjust size as needed

void matrixMultiplySerial(int A[N][N], int B[N][N], int C[N][N]) {
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
    
    // Initialize matrices with random values
    srand(time(NULL));
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

    clock_t start = clock();
    matrixMultiplySerial(A, B, C);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nResultant Matrix C:\n");
    printMatrix(C);

    printf("\nSerial execution time: %f seconds\n", time_taken);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to perform matrix addition
void matrix_addition(int **A, int **B, int **C, int size, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to allocate memory for a matrix
int** allocate_matrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to initialize matrix with random values
void initialize_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;  // Initialize with random values
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_threads_arr[] = {1, 2, 4, 8};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_thread_counts = sizeof(num_threads_arr) / sizeof(num_threads_arr[0]);

    // Loop over different matrix sizes
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int **A = allocate_matrix(size);
        int **B = allocate_matrix(size);
        int **C = allocate_matrix(size);
        initialize_matrix(A, size);
        initialize_matrix(B, size);

        // Loop over different thread counts
        for (int t = 0; t < num_thread_counts; t++) {
            int num_threads = num_threads_arr[t];
            double start_time = omp_get_wtime();
            
            matrix_addition(A, B, C, size, num_threads);
            
            double end_time = omp_get_wtime();
            double execution_time = end_time - start_time;

            printf("Matrix Size: %d, Threads: %d, Time: %f seconds\n", size, num_threads, execution_time);
        }

        // Free allocated memory
        for (int i = 0; i < size; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}

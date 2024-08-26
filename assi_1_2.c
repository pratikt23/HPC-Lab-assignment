#include <stdio.h>
#include <omp.h>

int main(void)
{
    // #pragma omp parallel
    // printf("Hello, world.\n");
    // return 0;

    int num_threads;

    // Ask the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Print "Hello, World" sequentially
    printf("\nSequential printing:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello, World (sequential) %d\n", i);
    }

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Print "Hello, World" in parallel
    printf("\nParallel printing:\n");
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, World (parallel) from thread %d\n", thread_id);
    }

    return 0;
}

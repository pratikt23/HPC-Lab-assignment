#include <stdio.h>
#include <omp.h>

int main() {
    int Aryabhatta = 10; // Variable with a fixed value
    int num_threads;

    // Prompt user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Parallel region
    #pragma omp parallel num_threads(num_threads) private(Aryabhatta)
    {
        int thread_id = omp_get_thread_num(); // Get the current thread ID

        // Initialize private variable Aryabhatta for each thread
        Aryabhatta = 10;

        // Compute and print the result of multiplication
        printf("Thread %d: %d * %d = %d\n", thread_id, thread_id, Aryabhatta, thread_id * Aryabhatta);
    }

    return 0;
}

#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    int sum = 0;

    // Prompt user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Parallel region to compute the squares of thread IDs
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num(); // Get the current thread ID
        int square = thread_id * thread_id; // Compute the square of the thread ID

        // Print the square value of the current thread ID
        printf("Thread %d: Square of %d is %d\n", thread_id, thread_id, square);

        // Use a critical section to update the sum safely
        #pragma omp critical
        {
            sum += square; // Add the square to the total sum
        }
    }

    // Print the total sum of squares after the parallel region
    printf("Sum of squares of thread IDs: %d\n", sum);

    return 0;
}

#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0; // Variable to store the final total sum
    int num_threads;
    const int n = 20; // Number of natural numbers to sum

    // Prompt user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    #pragma omp parallel num_threads(num_threads)
    {
        int partial_sum = 0; // Variable to store each thread's partial sum
        int thread_id = omp_get_thread_num(); // Get the current thread ID
        int num_threads = omp_get_num_threads(); // Get the total number of threads
        int chunk_size = n / num_threads; // Calculate the number of elements per thread
        int start = thread_id * chunk_size + 1; // Start index for each thread
        int end = (thread_id + 1) * chunk_size; // End index for each thread

        // Ensure the last thread handles any remaining elements
        if (thread_id == num_threads - 1) {
            end = n;
        }

        // Compute the partial sum for the assigned range
        for (int i = start; i <= end; i++) {
            partial_sum += i;
        }

        // Display the partial sum computed by this thread
        printf("Thread %d: Partial sum from %d to %d = %d\n", thread_id, start, end, partial_sum);

        // Update total_sum in a critical section to avoid race conditions
        #pragma omp critical
        {
            total_sum += partial_sum;
        }
    }

    // Print the final total sum after the parallel region
    printf("Total sum of the first %d natural numbers: %d\n", n, total_sum);

    return 0;
}

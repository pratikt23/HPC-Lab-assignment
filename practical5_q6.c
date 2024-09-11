#include <stdio.h>
#include <omp.h>

int main() {
    int max_terms = 10; // Number of terms in each series

    // Set number of threads to 2
    omp_set_num_threads(2);

    // Parallel region with two threads
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Get the ID of the current thread

        if (thread_id == 0) {
            // Thread 0 prints the series of 2
            printf("Series of 2:\n");
            for (int i = 1; i <= max_terms; i++) {
                printf("%d from thread  %d ", 2 * i,thread_id);
            }
            printf("\n");
        } else if (thread_id == 1) {
            // Thread 1 prints the series of 4
            printf("Series of 4:\n");
            for (int i = 1; i <= max_terms; i++) {
                printf(" %d from thread %d ", 4 * i,thread_id);
            }
            printf("\n");
        }
    }

    return 0;
}

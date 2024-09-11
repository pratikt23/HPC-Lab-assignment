#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int array_size = 1000000; // Example: 1 million elements
    int *array = (int *)malloc(array_size * sizeof(int));

    // Initialize array with values (1 to array_size)
    for (int i = 0; i < array_size; i++) {
        array[i] = i + 1;
    }

    // Sequential sum calculation
     clock_t start_seq = clock();
    long long sum = 0;
    for (int i = 0; i < array_size; i++) {
        sum += array[i];
    }
     clock_t end_seq = clock();
      double time_seq = ((double)(end_seq - start_seq)) / CLOCKS_PER_SEC;

    printf("Sequential sum: %lld\n", sum);
     printf("Sequential execution time: %f seconds\n", time_seq);

    free(array);
    return 0;
}

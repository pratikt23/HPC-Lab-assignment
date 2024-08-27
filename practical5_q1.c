#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_members;

    // Prompt user for the number of family members
    printf("Enter the number of family members: ");
    scanf("%d", &num_members);

    // Allocate memory dynamically for names
    char **names = (char **)malloc(num_members * sizeof(char *));
    for (int i = 0; i < num_members; i++) {
        names[i] = (char *)malloc(50 * sizeof(char)); // Allocate memory for each name
    }

    // Input names
    for (int i = 0; i < num_members; i++) {
        printf("Enter name for family member %d: ", i + 1);
        scanf("%s", names[i]);
    }

    // Parallel region to print family members' names
    #pragma omp parallel num_threads(num_members)
    {
        int thread_id = omp_get_thread_num(); // Get the current thread ID

        // Ensure each thread accesses the correct family member
        #pragma omp critical
        {
            if (thread_id < num_members) {
                printf("Thread %d: %s\n", thread_id, names[thread_id]);
            }
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < num_members; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}

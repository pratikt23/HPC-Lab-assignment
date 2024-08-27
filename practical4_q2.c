#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10 // Size of the shared buffer

// Shared buffer and synchronization variables
int *buffer;
int count = 0; // Number of items in the buffer
int in = 0;    // Index for producer to add items
int out = 0;   // Index for consumer to remove items
omp_lock_t mutex; // Mutex lock for buffer access
omp_lock_t empty; // Semaphore to track empty slots
omp_lock_t full;  // Semaphore to track full slots

void producer(int num_items) {
    for (int i = 0; i < num_items; i++) {
        int item = rand() % 100; // Produce an item

        omp_set_lock(&empty); // Wait for an empty slot
        omp_set_lock(&mutex); // Acquire mutex to modify buffer

        // Check if the buffer has space before adding an item
        if (count < BUFFER_SIZE) {
            buffer[in] = item; // Add item to buffer
            in = (in + 1) % BUFFER_SIZE;
            count++;
            printf("Produced: %d\n", item);
        }

        omp_unset_lock(&mutex); // Release mutex
        omp_unset_lock(&full);  // Signal that there is a new item
    }
}

void consumer(int num_items) {
    for (int i = 0; i < num_items; i++) {
        omp_set_lock(&full); // Wait for a full slot
        omp_set_lock(&mutex); // Acquire mutex to modify buffer

        // Check if there are items to consume
        if (count > 0) {
            int item = buffer[out]; // Remove item from buffer
            out = (out + 1) % BUFFER_SIZE;
            count--;
            printf("Consumed: %d\n", item);
        }

        omp_unset_lock(&mutex); // Release mutex
        omp_unset_lock(&empty); // Signal that there is now an empty slot
    }
}

int main() {
    int num_producers, num_consumers, num_items;

    // Get user inputs
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);
    printf("Enter the number of items to be produced/consumed: ");
    scanf("%d", &num_items);

    // Allocate buffer
    buffer = (int *)malloc(BUFFER_SIZE * sizeof(int));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize OpenMP locks
    omp_init_lock(&mutex);
    omp_init_lock(&empty);
    omp_init_lock(&full);

    // Initialize semaphore states
    for (int i = 0; i < BUFFER_SIZE; i++) {
        omp_unset_lock(&empty); // All slots are initially empty
    }
    for (int i = 0; i < 0; i++) {
        omp_set_lock(&full); // No slots are initially full
    }

    // Create producer and consumer threads
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = 0; i < num_producers; i++) {
                producer(num_items);
            }
        }
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = 0; i < num_consumers; i++) {
                consumer(num_items);
            }
        }
    }

    // Destroy OpenMP locks
    omp_destroy_lock(&mutex);
    omp_destroy_lock(&empty);
    omp_destroy_lock(&full);

    // Free allocated memory
    free(buffer);

    return 0;
}

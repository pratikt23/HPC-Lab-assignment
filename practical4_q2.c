#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 25

// Shared buffer and synchronization variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;
omp_lock_t lock;
omp_lock_t not_empty;
omp_lock_t not_full;

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS / NUM_PRODUCERS; i++) {
        int item = rand() % 100; // Produce an item

        omp_set_lock(&lock);

        while (count == BUFFER_SIZE) {
            omp_unset_lock(&lock);
            // Wait until buffer is not full
            // Spin-wait or use a more sophisticated waiting method in production code
            #pragma omp critical
            {
                while (count == BUFFER_SIZE) {
                    // This is a busy-wait loop for simplicity
                }
            }
            omp_set_lock(&lock);
        }

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        omp_unset_lock(&not_empty);
        omp_unset_lock(&lock);
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS / NUM_CONSUMERS; i++) {
        int item;

        omp_set_lock(&lock);

        while (count == 0) {
            omp_unset_lock(&lock);
            // Wait until buffer is not empty
            // Spin-wait or use a more sophisticated waiting method in production code
            #pragma omp critical
            {
                while (count == 0) {
                    // This is a busy-wait loop for simplicity
                }
            }
            omp_set_lock(&lock);
        }

        // Remove item from buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        omp_unset_lock(&not_full);
        omp_unset_lock(&lock);

        // Process the item
        printf("Consumer %d consumed item %d\n", id, item);
    }
}

int main() {
    omp_init_lock(&lock);
    omp_init_lock(&not_empty);
    omp_init_lock(&not_full);

    // Initializing locks
    omp_set_lock(&not_full);
    omp_set_lock(&not_empty);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Start producers
            #pragma omp parallel num_threads(NUM_PRODUCERS)
            {
                producer(omp_get_thread_num());
            }
        }

        #pragma omp section
        {
            // Start consumers
            #pragma omp parallel num_threads(NUM_CONSUMERS)
            {
                consumer(omp_get_thread_num());
            }
        }
    }

    // Clean up
    omp_destroy_lock(&lock);
    omp_destroy_lock(&not_empty);
    omp_destroy_lock(&not_full);

    return 0;
}

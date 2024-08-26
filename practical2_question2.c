#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void calculate_pi(long long num_samples, int num_threads) {
    long long inside_circle = 0;  // Counter for points inside the circle
    double pi_estimate;
    double start_time, end_time;

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Start timing
    start_time = omp_get_wtime();

    // Parallel region
    #pragma omp parallel reduction(+:inside_circle)
    {
        // Initialize random number generator with a unique seed for each thread
        unsigned int seed = time(NULL) + omp_get_thread_num();

        #pragma omp for
        for (long long i = 0; i < num_samples; i++) {
            // Generate random x and y values between 0 and 1
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;

            // Check if the point is inside the unit circle
            if (x * x + y * y <= 1.0) {
                inside_circle++;
            }
        }
    }

    // Calculate the estimated value of Pi
    pi_estimate = (double)inside_circle / num_samples * 4.0;

    // End timing
    end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Print results
    printf("Threads: %d, Samples: %lld, Estimated Pi: %f, Time: %f seconds\n", 
           num_threads, num_samples, pi_estimate, elapsed_time);
}

int main() {
    int num_threads;
    long long num_samples;

    // Take user input for number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Take user input for number of samples
    printf("Enter the number of samples: ");
    scanf("%lld", &num_samples);

    // Calculate Pi with the provided inputs
    calculate_pi(num_samples, num_threads);

    return 0;
}

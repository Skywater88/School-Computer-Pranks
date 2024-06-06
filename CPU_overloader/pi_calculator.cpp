#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define NUM_POINTS 1000000000 // You can adjust this for better precision

double calculate_pi(int num_points) {
    int i, count = 0;
    double x, y, pi;

    for (i = 0; i < num_points; i++) {
        // Generate random coordinates between 0 and 1
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point is within the unit circle
        if (x * x + y * y <= 1)
            count++;
    }

    // Calculate Pi based on the ratio of points within the circle
    pi = (double)count / num_points * 4;
    return pi;
}

int main() {
    clock_t start_time, end_time;
    double pi_estimate;
    int num_points = NUM_POINTS;

    // Start timing
    start_time = clock();

    // Calculate Pi
    pi_estimate = calculate_pi(num_points);

    // End timing
    end_time = clock();

    // Get the time taken
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    printf("Estimated value of Pi using %d points: %f\n", num_points, pi_estimate);
    printf("Time taken to compute: %f seconds\n", time_taken);

getch();
    return 0;
}

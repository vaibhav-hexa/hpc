/*
 * Calculation of value of PI using Monte-Carlo method
 * using OpenMP
 */

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  long long int tosses = 0;
  int number_in_circle = 0, toss = 0;
  long double x, y, distance_squared, pi_estimate, pi2, fi_pi;
  double time1, time2;

  // Get number of tosses as command-line argument
  tosses = atoi(argv[1]);
  srand(time(NULL));

  // Create 10 number of threads for following code-block
  #pragma omp parallel num_threads(10)
  {
    if (omp_get_thread_num() == 0)
      time1 = omp_get_wtime();  // Note the start time

    for (toss = 0; toss < tosses; toss++) {
      x = (long double)rand() / RAND_MAX * 2.0 - 1;
      y = (long double)rand() / RAND_MAX * 2.0 - 1;

      distance_squared = x * x + y * y;

      if (distance_squared <= 1) {
        #pragma omp critical
        number_in_circle++; // Critical section for atomic updates
      }
    }

    printf("Number of threads: %d\n", omp_get_num_threads());

    if (omp_get_thread_num() == 0) {
      time2 = omp_get_wtime();  // Note the end time
      printf("\nWork time in seconds: %f", time2 - time1);
    }
  }

  pi_estimate = 4.0 * number_in_circle / ((long double)tosses);
  fi_pi = pi_estimate;
  printf("\nPi : %Lf\n", fi_pi);
}

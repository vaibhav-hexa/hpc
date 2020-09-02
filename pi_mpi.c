/*
 * Calculation of value of PI using Monte-Carlo method
 * using MPI Bcast and Reduce
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  // Initialize MPI world
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Larger number of tosses yield precise value of PI
  long long int tosses = 0;
  int number_in_circle = 0, toss = 0;

  long double x, y, distance_squared, pi_estimate, pi2, fi_pi;

  tosses = atoi(argv[1]);   // Get number of tosses as command-line argument

  MPI_Bcast(&tosses, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);  // Broadcast number of tosses to all processes

  srand(time(NULL));  // Generate seed for random number for each process
  for (toss = 0; toss < tosses; toss++) {
    x = (long double)rand() / RAND_MAX * 2.0 - 1;
    y = (long double)rand() / RAND_MAX * 2.0 - 1;

    distance_squared = x * x + y * y;
    if (distance_squared <= 1) {
      number_in_circle++;
    }
  }
  pi_estimate = 4.0 * number_in_circle / ((long double)tosses);  // Monte-carlo method

  MPI_Reduce(&pi_estimate, &pi2, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);   // Summation by reduction of PI values calculated by all processes at master process

  if (world_rank == 0) {
    fi_pi = pi2 / (long double)world_size;  // find the actual PI value as average from all processes
    printf("\nPi : %Lf\n", fi_pi);
  }

  MPI_Finalize(); // Wrap up MPI world
}

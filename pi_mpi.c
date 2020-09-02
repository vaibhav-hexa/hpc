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
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  long long int tosses = 0;
  int number_in_circle = 0, toss = 0;

  long double x, y, distance_squared, pi_estimate, pi2, fi_pi;

  tosses = atoi(argv[1]);

  MPI_Bcast(&tosses, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);

  srand(time(NULL));

  for (toss = 0; toss < tosses; toss++) {
    x = (long double)rand() / RAND_MAX * 2.0 - 1;
    y = (long double)rand() / RAND_MAX * 2.0 - 1;

    distance_squared = x * x + y * y;
    if (distance_squared <= 1) {
      number_in_circle++;
    }
  }
  pi_estimate = 4.0 * number_in_circle / ((long double)tosses);

  MPI_Reduce(&pi_estimate, &pi2, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  if (world_rank == 0) {
    fi_pi = pi2 / (long double)world_size;
    printf("\nPi : %Lf\n", fi_pi);
  }

  MPI_Finalize();
}

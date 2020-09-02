/*
 * Butterfly summation using MPI_Reduce call
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  // Initialize variables
  int world_size, world_rank;
  int sum, gsum = 0;

  // Initialize MPI world
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Generate random number for each process
  srand(time(0));
  sum = (world_rank * rand()) % 100;

  printf("Rank: %d & MyValue: %d\n", world_rank, sum);

  // Calculate sum by reduction at master process
  MPI_Reduce(&sum, &gsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (world_rank == 0) {
    printf("*Reduced sum: %d\n", gsum);
  }

  MPI_Finalize();
}

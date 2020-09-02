/*
 * Butterfly summation using MPI_Reduce call
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv) {

  int world_size, world_rank;
  int sum, gsum = 0;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  srand(time(0));
  sum = (world_rank * rand()) % 100;

  printf("Rank: %d & MyValue: %d\n", world_rank, sum);

  MPI_Reduce(&sum, &gsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (world_rank == 0) {
    printf("*Reduced sum: %d\n", gsum);
  }

  MPI_Finalize();
}
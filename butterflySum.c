/*
 * Butterfly summation using MPI Send and Receive call
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int world_size, world_rank;
int temp, stages, mask = 1, partner = 0, sum;

int sumf();

int main(int argc, char **argv) {
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  stages = (int)(log10(world_size) / log10(2));

  if (world_rank == 0) {

    printf("Stages and World size %d, %d\n\n", stages, world_size);
  }

  srand(time(0));
  sum = world_rank * (rand() % 10);
  printf("Rank: %d, Global sum: %d & MyValue: %d\n", world_rank, sumf(), sum);

  MPI_Finalize();
}

int sumf() {
  for (int i = 0; i < stages; i++) {
    partner = world_rank ^ mask;

    MPI_Send(&sum, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
    MPI_Recv(&temp, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    sum += temp;
    mask <<= 1;
  }
  return sum;
}

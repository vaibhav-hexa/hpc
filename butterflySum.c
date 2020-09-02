/*
 * Butterfly summation using MPI Send and Receive call
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize variables
int world_size, world_rank;
int temp, stages, mask = 1, partner = 0, sum;

// Declare sumf() which gets called by each process
int sumf();

int main(int argc, char **argv) {
  // Initialize MPI world
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Calculate number of stages based on the world size for binary tree-like summation
  stages = (int)(log10(world_size) / log10(2));

  // Print information about MPI world only if it is a master process
  if (world_rank == 0) {
    printf("Stages and World size %d, %d\n\n", stages, world_size);
  }

  // Generate random number for each process
  srand(time(0));
  sum = world_rank * (rand() % 10);
  printf("Rank: %d, Global sum: %d & MyValue: %d\n", world_rank, sumf(), sum);

  // Close the MPI world after summation
  MPI_Finalize();
}

int sumf() {
  for (int i = 0; i < stages; i++) {
    // Find new partner number
    partner = world_rank ^ mask;

    // Exchange data with partner
    MPI_Send(&sum, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
    MPI_Recv(&temp, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    sum += temp; // Calulate local sum
    mask <<= 1;  // Advance to next level in tree
  }
  return sum;
}

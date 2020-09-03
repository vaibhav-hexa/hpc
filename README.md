# HPC

HPC codes using [OpenMP](https://www.openmp.org/) and [MPI](https://computing.llnl.gov/tutorials/mpi/#What) - Problems solved using parallelization methods

1) [butterflySum.c](https://github.com/vaibhav-hexa/hpc/blob/master/butterflySum.c) technique of [Butterfly network - WIKI](https://en.wikipedia.org/wiki/Butterfly_network) for calculating sum of numbers from each process in MPI COMM world of processes using Point-to-point communication.
2) [butterflySumReduce.c](https://github.com/vaibhav-hexa/hpc/blob/master/butterflySumReduce.c) applies same method as [butterflySum.c](https://github.com/vaibhav-hexa/hpc/blob/master/butterflySum.c), but [MPI_Reduce()](https://www.mpich.org/static/docs/latest/www3/MPI_Reduce.html) is used for Collective operation.
3) [pi_mpi.c](https://github.com/vaibhav-hexa/hpc/blob/master/pi_mpi.c) uses [Monte-Carlo method for caclulation of PI value](http://sites.nd.edu/code-fair/2018/09/12/monte-carlo-pi-calculation/) using [MPI_Reduce()](https://www.mpich.org/static/docs/latest/www3/MPI_Reduce.html) for Collective operation.
4) [pi_openmp.c](https://github.com/vaibhav-hexa/hpc/blob/master/pi_openmp.c) uses same Monte-Carlo method as used in [pi_mpi.c](https://github.com/vaibhav-hexa/hpc/blob/master/pi_mpi.c) but parallelization is achieved using [OpenMP calls](https://www.openmp.org/).

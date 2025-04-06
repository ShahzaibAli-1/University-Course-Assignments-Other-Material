#include <mpi.h>
#include <stdio.h>
// Blocks all processes in the communicator until every process has called MPI_Barrier. Only then do they continue execution.


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Process %d reached the barrier\n", rank);

    // All processes wait here until everyone arrives
    // syntax: MPI_Barrier(MPI_Comm comm);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d passed the barrier\n", rank);

    MPI_Finalize();
    return 0;
}

#include <mpi.h>
#include <stdio.h>
// Combines values from all processes using a reduction operation (like sum, max, product, etc.), and stores the result on the root process.
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, result;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // MPI_Reduce(void *sendbuf, void *recvbuf, int count,
    //     MPI_Datatype datatype, MPI_Op op,
    //     int root, MPI_Comm comm);


    // Each process sends its rank to be summed
    MPI_Reduce(&rank, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of all ranks = %d\n", result);
    }

    MPI_Finalize();
    return 0;
}

// MPI_SUM	Sum of values
// MPI_PROD	Product
// MPI_MAX	Maximum
// MPI_MIN	Minimum
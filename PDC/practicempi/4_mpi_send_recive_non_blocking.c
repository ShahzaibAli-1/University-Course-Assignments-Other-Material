// MPI_Isend and MPI_Irecv
// Non-blocking calls return immediately.
// You must later use MPI_Wait (or MPI_Test) to ensure the operation is complete.
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Request request;

    if (rank == 0) {
        int number = 99;
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);  // Ensure send is done
        printf("Process 0 sent number %d to Process 1 (non-blocking)\n", number);
    } else if (rank == 1) {
        int number;
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);  // Ensure receive is done
        printf("Process 1 received number %d from Process 0 (non-blocking)\n", number);
    }

    MPI_Finalize();
    return 0;
}

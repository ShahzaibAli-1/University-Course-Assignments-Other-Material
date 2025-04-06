#include <mpi.h>
#include <stdio.h>
// MPI_Wait(MPI_Request *request, MPI_Status *status);

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number;
    MPI_Request request;

    if (rank == 0) {
        number = 123;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

        // Do something else here...

        // Wait for the message to arrive
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d\n", number);
    }

    MPI_Finalize();
    return 0;
}

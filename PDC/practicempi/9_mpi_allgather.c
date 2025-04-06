#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank * 10;
    int recv_data[4];  // adjust size as needed


    // MPI_Allgather(void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //     void *recvbuf, int recvcount, MPI_Datatype recvtype,
    //     MPI_Comm comm);

    // All processes gather everyone's data
    MPI_Allgather(&send_data, 1, MPI_INT,
                  recv_data, 1, MPI_INT,
                  MPI_COMM_WORLD);

    printf("Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

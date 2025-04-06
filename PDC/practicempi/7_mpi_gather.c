#include <mpi.h>
#include <stdio.h>
// 🧲 What it does:
// Gathers data from all processes.

// Combines it into a single array on the root process.
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = (rank + 1) * 100;
    int recv_data[4];  // Only needed on root

    printf("Process %d sending %d to root\n", rank, send_data);

    // Gather 1 int from each process to root

    // MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //     void *recvbuf, int recvcount, MPI_Datatype recvtype,
    //     int root, MPI_Comm comm);

    MPI_Gather(&send_data, 1, MPI_INT,
               recv_data, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Root process gathered: ");
        for (int i = 0; i < size; i++)
            printf("%d ", recv_data[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

// Function	Direction	Use Case
// MPI_Scatter	One → Many	Divide work/data to all processes
// MPI_Gather	Many → One	Collect results from all processes
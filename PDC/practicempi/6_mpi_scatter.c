//  MPI_Scatter – Distribute Data from One to All
//  What it does:
// Splits an array on the root process into equal parts.

// Sends one chunk to each process, including the root itself.
#include<stdio.h>
#include<mpi.h>
int main(int argc, int **argv){

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank );
    MPI_Comm_size(MPI_COMM_WORLD,&size );
    int data[4];
    int chunk;//each process gets one chunk

    if (rank == 0){
        data[0] = 10;
        data[1] = 20;
        data[3] = 30;
        data[4] = 40;
        printf("Proces  0 is scattering\n");
    }

    // MPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //     void *recvbuf, int recvcount, MPI_Datatype recvtype,
    //     int root, MPI_Comm comm);
    // scatter 1 element to each process
    MPI_Scatter(data, 1, MPI_INT, &chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received chunk %d\n", rank, chunk);
    MPI_Finalize();
    return 0;
}
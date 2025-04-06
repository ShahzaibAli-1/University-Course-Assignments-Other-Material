// #include<stdio.h>
// #include<mpi.h>
// int main(int argc, int **argv){
//     MPI_Init(&argc, &argv);
//     int rank;
//     int size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
//     MPI_Comm_size(MPI_COMM_SIZE, &size);
//     int data = rank+1 * 100; 
//     int arr[5];
//     int root;

//     if(root!=0){
//         // MPI_Send(Buffer,size, datatype, int destination, tag,MPI_Comm comm  )
//         MPI_Send(&arr, 5, MPI_INT, 0, 0, MPI_COMM_WORLD);
//     }
//     // MPI_Gather(sendbuf, sendcount, MPI datatypesend , receivebuffer, int recvcount, MPI datatype recv,int root, MPI comm)
//     MPI_Gather(data, 1, MPI_INT, &arr, 1, MPI_INT, 0, MPI_COMM_WORLD)
//     if(root==0){
//         MPI_Receive(&arr,5,MPI_INT,1,0,MPI_COMM_WORLD, MPI_IGNORE);
//     }
//     MPI_Finalize();
//     return 0;
// }


//statement
// Suppose you are in a scenario where you have to transmit an array buffer from all
// other nodes to one node by using send/ receive functions that are used for intra- process synchronous communication. The figure below demonstrates the required
// functionality of the program.
//corect solution 
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    const int ARR_SIZE = 5;
    int buffer[ARR_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Fill the array with dummy data unique to each process
    for (int i = 0; i < ARR_SIZE; i++) {
        buffer[i] = rank * 100 + i;
    }

    if (rank != 0) {
        // Non-root nodes send their array to root (rank 0)
        MPI_Send(buffer, ARR_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Root receives arrays from all other nodes
        for (int i = 1; i < size; i++) {
            int recv_buffer[ARR_SIZE];
            MPI_Recv(recv_buffer, ARR_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Print received data for demonstration
            printf("Received array from Node %d: ", i);
            for (int j = 0; j < ARR_SIZE; j++) {
                printf("%d ", recv_buffer[j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

// #include<stdio.h>
// #include<mpi.h>

// int main(int argc, int **argv){

//     MPI_Init(&argc, &argv);
//     int root = 0;
//     int rank;
//     int buffer;
//     int size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     buffer = (size*rank+1)/size ;
//     for(int i=  0; i<size;i++){
//         if(rank<size && rank>0)
//         MPI_Send(&buffer,1, MPI_INT, rank+1,0, MPI_COMM_WORLD);
//         MPI_Recieve(&buffer,1, MPI_INT, rank-1,0, MPI_COMM_WORLD);
//         if(rank==0){
//             MPI_Send(&buffer,1, MPI_INT, rank+1,0, MPI_COMM_WORLD);
//             MPI_Recieve(&buffer,1, MPI_INT, size-1,0, MPI_COMM_WORLD);
//         }
//         if(rank==size-1){
//             MPI_Send(&buffer,1, MPI_INT, root,0, MPI_COMM_WORLD);
//             MPI_Recieve(&buffer,1, MPI_INT, rank-1,0, MPI_COMM_WORLD);
//         }

//     }
    
//     MPI_Finalize();

//     return 0;
// }

// statement 
//1. Write a program in which every node receives from its left node and sends message
// to its right node simultaneously as depicted in the following figure


#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    int send_data, recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    send_data = rank * 10; // example data to send

    int dest = (rank + 1) % size;        // send to right neighbor (wrap around)
    int source = (rank - 1 + size) % size; // receive from left neighbor (wrap around)

    MPI_Sendrecv(
        &send_data, 1, MPI_INT, dest, 0,
        &recv_data, 1, MPI_INT, source, 0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );

    printf("Process %d sent %d to %d and received %d from %d\n",
           rank, send_data, dest, recv_data, source);

    MPI_Finalize();
    return 0;
}

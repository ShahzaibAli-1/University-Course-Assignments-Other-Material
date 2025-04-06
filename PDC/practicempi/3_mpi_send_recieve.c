#include<stdio.h>
#include<mpi.h>
int main(int argc, int **argv){
    MPI_INIT(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0){
        int number =40;

        // MPI_Send(void *buf, int count, MPI_Datatype datatype,
        //     int dest, int tag, MPI_Comm comm);   
        MPI_Send(&number,1, MPI_INT, 1, 0 , MPI_COMM_WORLD);
        printf("Process 0 sent number %d to Process 1\n", number);
    }
    else if(rank ==1){
        int number; 
        // MPI_Recv(void *buf, int count, MPI_Datatype datatype,
        //     int source, int tag, MPI_Comm comm, MPI_Status *status);
   
        MPI_Recieve(&number,1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

//These are the most basic forms of communication.
//MPI_Send: Blocks until the message data is safely copied out.
//MPI_Recv: Blocks until the message is received.

MPI_Finalize();
    return 0;
}
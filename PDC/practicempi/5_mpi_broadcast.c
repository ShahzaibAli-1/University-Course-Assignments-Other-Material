#include<stdio.h>
#include<mpi.h>
int main(int argc, int **argv){
    // Broadcast sends the same data from one process to other
    // All other processes recives value automatically
    // This is useful when:
    // You want to share the same configuration or data with all workers.
    // You want to avoid writing separate MPI_Send calls to each process.
    // syntax

    // MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    //     int root, MPI_Comm comm);


    //syntax
    // MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    //     int root, MPI_Comm comm);
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int number;
    if(rank ==0){
        number=  42;
        printf("Broadcasting the number %d every process", number);
    }
    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Now every process should have the same number
    printf("Process %d received number %d from broadcast\n", rank, number);
    MPI_Finalize();
    return 0;
}

//expected output
// Process 0 broadcasting number 42
// Process 0 received number 42 from broadcast
// Process 1 received number 42 from broadcast
// Process 2 received number 42 from broadcast
// Process 3 received number 42 from broadcast

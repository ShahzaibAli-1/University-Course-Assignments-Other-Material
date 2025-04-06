#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int a, b;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes

    // Each node initializes 'a' to its rank
    a = rank;
    
    // Exchange 'a' with other nodes
    // First, send 'a' to the next node, and receive 'a' from the previous node
    if (rank == 0) {
        // Process 0 sends 'a' to process 1
        MPI_Send(&a, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        // Process 0 does not receive from anyone (no previous node)
        b = 0;
    } else if (rank == size - 1) {
        // Last node receives from previous node and has no one to send to
        MPI_Recv(&b, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        a += b;  // Update 'a' with the received value
    } else {
        // Intermediate nodes send and receive
        MPI_Send(&a, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&b, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        a += b;  // Update 'a' with the received value
    }
    
    // All processes now print their updated value of 'a' (prefix sum)
    printf("Process %d has prefix sum: %d\n", rank, a);
    
    // Finalize MPI
    MPI_Finalize();
    return 0;
}

// 1. Code the above example program in C that calculates the sum of numbers in
// parallel on different numbers of nodes. Also calculate the execution time. [Note: You have to use time stamp function to also print the time at begging and end
// of parallel code segment]
// Output: (On Single Node)
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int mynode, totalnodes;
    int sum = 0, startval, endval, accum;
    MPI_Status status;

    // Start MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &totalnodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynode);

    // Start time (after MPI_Init)
    double start_time = MPI_Wtime();

    // Divide the range [1–1000] among nodes
    startval = 1000 * mynode / totalnodes + 1;
    endval = 1000 * (mynode + 1) / totalnodes;

    // Each process calculates its partial sum
    for (int i = startval; i <= endval; i++) {
        sum += i;
    }

    // Send partial sums to root (rank 0)
    if (mynode != 0) {
        MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    } else {
        // Root receives and adds all the partial sums
        for (int j = 1; j < totalnodes; j++) {
            MPI_Recv(&accum, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
            sum += accum;
        }

        // End time (only root measures total time)
        double end_time = MPI_Wtime();
        double exec_time = end_time - start_time;

        printf("The sum from 1 to 1000 is: %d\n", sum);
        printf("Execution Time: %f seconds\n", exec_time);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

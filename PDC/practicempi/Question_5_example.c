#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value, prefix_sum;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes

    // Initialize the value at each process (for simplicity, we use rank as the value)
    value = rank;

    // Perform the scan operation to compute the prefix sum
    MPI_Scan(&value, &prefix_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Print the result for each process
    printf("Process %d has prefix sum: %d\n", rank, prefix_sum);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

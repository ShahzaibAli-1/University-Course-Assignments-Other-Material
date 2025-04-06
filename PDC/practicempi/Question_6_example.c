#include <stdio.h>
#include <mpi.h>

double f(double x) {
    // Function to compute 4 / (1 + x^2)
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int rank, size;
    int n;
    double local_sum = 0.0, total_sum = 0.0;
    double start_x, end_x, step_size;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes

    // Master process (rank 0) asks for the number of intervals (n)
    if (rank == 0) {
        printf("Enter the number of intervals: ");
        fflush(stdout);  // Ensure the prompt is printed before waiting for input
        scanf("%d", &n);
    }

    // Broadcast the number of intervals to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the step size (width of each interval)
    step_size = 1.0 / (2.0 * n);  // The range is from -1/2 to 1/2, so the total length is 1
                                   // Each interval covers 1/n, but the number of subintervals
                                   // is divided by 2 (from -1/2 to 1/2).

    // Calculate the subintervals for each process
    start_x = -0.5 + rank * step_size;  // The starting point for this process
    end_x = start_x + step_size;        // The ending point for this process
    
    // Each process computes its partial sum
    for (int i = 0; i < n / size; i++) {
        double x = start_x + i * step_size;
        local_sum += f(x);
    }

    // Reduce all the local sums to the master process (rank 0)
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Master process prints the final result
    if (rank == 0) {
        total_sum *= step_size;  // Multiply by step size to get the final approximation of Pi
        printf("Approximation of PI: %.15f\n", total_sum);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

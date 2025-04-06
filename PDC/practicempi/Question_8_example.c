//statement
// Problem # 6
// You are given two square integer matrices, A and B, of size N x N. Your task is to
// implement matrix multiplication using MPI. You will use MPI_Scatter and
// MPI_Reduce operations to distribute the workload among multiple processes and
// combine the results. Task Steps:
// 1. Matrix Generation:
// o Generate two random square matrices, A and B, of size N x N. 2. Sequential Matrix Multiplication:
// o Implement a sequential matrix multiplication algorithm in Python
// without MPI. o Perform matrix multiplication of matrices A and B using the sequential
// algorithm. o Print the resulting matrix C, which is the product of A and B. 3. MPI Scatter:
// o Initialize MPI and get the total number of processes and the current
// process rank. o If the current process rank is 0:  Scatter matrix A to all other processes using MPI_Scatter. o If the current process rank is not 0:  Receive the scattered portion of matrix A using MPI_Scatter. o Print the received portion of matrix A on each process. o Scatter matrix B to all processes using MPI_Scatter. o Print the received portion of matrix B on each process. 4. Matrix Multiplication:
// o Perform the local matrix multiplication of the scattered portions of
// matrices A and B on each process. o Implement the matrix multiplication algorithm for the local portions of
// A and B. o Print the resulting local matrix on each process. 5. MPI Reduce:
// o Use MPI_Reduce to collect all the local matrix portions from different
// processes. o Reduce the local matrix portions using MPI_Reduce with the
// MPI_SUM operation. o On process rank 0, print the resulting matrix C, which is the product of
// A and B.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 4  // Size of the matrix (4x4 for this example)

// Function to generate a random matrix of size N x N
void generate_random_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;  // Random integers between 0 and 9
        }
    }
}

// Sequential matrix multiplication for verification
void sequential_matrix_multiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    int local_A[N / 2][N], local_C[N / 2][N];  // Local matrices for each process

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(time(NULL) + rank);

    if (rank == 0) {
        // Generate matrices A and B on the master process
        generate_random_matrix(A);
        generate_random_matrix(B);

        // Print the generated matrices on the master process
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        printf("\nMatrix B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }
    }

    // Scatter the rows of matrix A to all processes
    MPI_Scatter(A, N * N / size, MPI_INT, local_A, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter matrix B to all processes
    MPI_Scatter(B, N * N / size, MPI_INT, local_B, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication
    for (int i = 0; i < N / size; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                local_C[i][j] += local_A[i][k] * local_B[k][j];
            }
        }
    }

    // Gather the results back into matrix C on the root process
    MPI_Gather(local_C, N * N / size, MPI_INT, C, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the resulting matrix C (A * B) on the master process
    if (rank == 0) {
        printf("\nResultant matrix C (A * B):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }

        // Perform sequential multiplication for comparison
        int C_sequential[N][N];
        sequential_matrix_multiply(A, B, C_sequential);
        
        // Print the sequential result
        printf("\nSequential matrix multiplication result C (A * B):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C_sequential[i][j]);
            }
            printf("\n");
        }

        // Verify if the parallel and sequential results match
        int is_correct = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (C[i][j] != C_sequential[i][j]) {
                    is_correct = 0;
                    break;
                }
            }
        }

        if (is_correct) {
            printf("\nMatrix multiplication successful, results match!\n");
        } else {
            printf("\nMatrix multiplication failed, results do not match!\n");
        }
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

#include<stdio.h>
#include<mpi.h>

int main(int argc, int **argv){

MPI_Init(&argc, &argv);
int world_size;
int world_rank;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);// get the total number of processes
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);// get the id out of current process

printf("Hello world from process %d out of %d in MPI_WORLD\n", world_rank, world_size);


    return 0;
}
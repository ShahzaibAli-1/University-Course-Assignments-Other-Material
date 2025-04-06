#include <mpi.h>
#include <stdio.h>

// C Type	MPI Equivalent
// int	MPI_INT
// float	MPI_FLOAT
// double	MPI_DOUBLE
// char	MPI_CHAR
// long	MPI_LONG
// unsigned	MPI_UNSIGNED

struct Particle {
    float position[3];
    float velocity[3];
    int id;
};

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct Particle p;

    if (rank == 0) {
        p.position[0] = 1.0; p.position[1] = 2.0; p.position[2] = 3.0;
        p.velocity[0] = 0.1; p.velocity[1] = 0.2; p.velocity[2] = 0.3;
        p.id = 42;
    }

    // Step 1: Define block lengths
    int block_lengths[3] = {3, 3, 1};

    // Step 2: Define types
    MPI_Datatype types[3] = {MPI_FLOAT, MPI_FLOAT, MPI_INT};

    // Step 3: Define displacements
    MPI_Aint displacements[3];
    displacements[0] = offsetof(struct Particle, position);
    displacements[1] = offsetof(struct Particle, velocity);
    displacements[2] = offsetof(struct Particle, id);

    // Step 4: Create and commit the new MPI type
    MPI_Datatype MPI_Particle;
    MPI_Type_create_struct(3, block_lengths, displacements, types, &MPI_Particle);
    MPI_Type_commit(&MPI_Particle);

    // Send/Receive the struct
    if (rank == 0) {
        MPI_Send(&p, 1, MPI_Particle, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&p, 1, MPI_Particle, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received Particle: pos[0]=%.1f, vel[0]=%.1f, id=%d\n",
               p.position[0], p.velocity[0], p.id);
    }

    MPI_Type_free(&MPI_Particle);
    MPI_Finalize();
    return 0;
}

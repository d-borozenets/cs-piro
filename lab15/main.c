#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    // printf("Hello from %d of %d\n", , );

    MPI_Finalize();
    return 0;
}
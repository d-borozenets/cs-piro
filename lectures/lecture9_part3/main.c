#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size;
    int rank; ushrt_t port;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//    printf("Hello from process %d of %d\n", rank, size);
    if (rank == 0) {
        printf("Coordinator: %d processes are running\n", size);
    } else {
        printf("Worker %d is ready\n", rank);
    }



    MPI_Finalize();

    return 0;
}
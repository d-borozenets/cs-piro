#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size;
    int rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 2) {
        if (rank == 0) {
            printf("Run this program with exactly 2 processes.\n");
        }

        MPI_Finalize();
        return 1;
    }

    int partner = 1 - rank;
    int send_value = (rank + 1) * 10;
    int recv_value = 0;

    printf("Process %d: before exchange\n", rank);
    fflush(stdout);

    MPI_Send(&send_value, 1, MPI_INT, partner, 0,
             MPI_COMM_WORLD);

    // MPI_Ssend(&send_value, 1, MPI_INT, partner, 0,
    //          MPI_COMM_WORLD);

    MPI_Recv(&recv_value, 1, MPI_INT, partner, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);


    // if (rank == 0) {
    //     MPI_Send(&send_value, 1, MPI_INT, partner, 0,
    //              MPI_COMM_WORLD);
    //
    //     MPI_Recv(&recv_value, 1, MPI_INT, partner, 0,
    //              MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // } else {
    //     MPI_Recv(&recv_value, 1, MPI_INT, partner, 0,
    //              MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //
    //     MPI_Send(&send_value, 1, MPI_INT, partner, 0,
    //              MPI_COMM_WORLD);
    // }

    // MPI_Sendrecv(
    //     &send_value, 1, MPI_INT, partner, 0,
    //     &recv_value, 1, MPI_INT, partner, 0,
    //     MPI_COMM_WORLD, MPI_STATUS_IGNORE
    // );
    //
    // printf("Process %d: sent %d, received %d\n",
    //        rank, send_value, recv_value);

    MPI_Finalize();
    return 0;
}
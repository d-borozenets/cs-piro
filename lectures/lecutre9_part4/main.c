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

    if (rank == 0) {
        int value = 42;

        MPI_Send(&value, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);

        // int values[5] = {10, 20, 30, 40, 50};
        //
        // MPI_Send(values, 5, MPI_INT, 1, 20, MPI_COMM_WORLD);
    } else {
        int received_value = 0;

        MPI_Recv(&received_value, 1, MPI_INT, 0, 10,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received: %d\n", rank, received_value);


        // int received_values[5];
        // // int received_values[10] = {0};
        // MPI_Status status;
        //
        //
        // MPI_Recv(received_values, 5, MPI_INT, 0, 20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // // MPI_Recv(received_values, 10, MPI_INT, 0, 20, MPI_COMM_WORLD, &status);
        // // MPI_Recv(received_values, 10, MPI_INT,MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        //
        // // int received_count;
        // // MPI_Get_count(&status, MPI_INT, &received_count);
        // // printf("Source: %d, tag: %d, count: %d\n", status.MPI_SOURCE, status.MPI_TAG, received_count);
        //
        //
        // printf("Received array:");
        //
        // // for (int i = 0; i < received_count; ++i) {
        //     for (int i = 0; i < 5; ++i) {
        //     printf(" %d", received_values[i]);
        // }

        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

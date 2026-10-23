#include <stdio.h>
#include <mpi.h>

#define ITERATIONS 1000000

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

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

    MPI_Request requests[2];

    MPI_Irecv(&recv_value, 1, MPI_INT, partner, 0,
              MPI_COMM_WORLD, &requests[0]);

    MPI_Isend(&send_value, 1, MPI_INT, partner, 0,
              MPI_COMM_WORLD, &requests[1]);

    int completed;

    MPI_Test(&requests[0], &completed, MPI_STATUS_IGNORE);

    if (completed) {
        printf("Process %d: receive has completed\n", rank);
    } else {
        printf("Process %d: receive has not completed yet\n", rank);
    }

    double local_result = 0.0;

    for (int i = 1; i <= ITERATIONS; ++i) {
        local_result += 1.0 / (i + rank);
    }

    MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);

    printf("Process %d: sent %d, received %d, local result = %.6f\n",
           rank, send_value, recv_value, local_result);

    MPI_Finalize();
    return 0;
}
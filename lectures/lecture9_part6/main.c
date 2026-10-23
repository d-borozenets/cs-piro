#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

#define PROCESS_COUNT 4
#define BLOCK_SIZE 2
#define ARRAY_SIZE (PROCESS_COUNT * BLOCK_SIZE)

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != PROCESS_COUNT) {
        if (rank == 0) {
            printf("Run this program with exactly %d processes.\n",
                   PROCESS_COUNT);
        }

        MPI_Finalize();
        return 1;
    }

    int factor = 0;
    int values[ARRAY_SIZE] = {0};
    int local_values[BLOCK_SIZE];
    int partial_sums[PROCESS_COUNT];

    if (rank == 0) {
        factor = 2;

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            values[i] = i + 1;
        }
    }

    MPI_Bcast(&factor, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(
        values, BLOCK_SIZE, MPI_INT,
        local_values, BLOCK_SIZE, MPI_INT,
        0, MPI_COMM_WORLD
    );

    int local_sum = 0;

    for (int i = 0; i < BLOCK_SIZE; ++i) {
        local_values[i] *= factor;
        local_sum += local_values[i];
    }

    MPI_Gather(
        &local_sum, 1, MPI_INT,
        partial_sums, 1, MPI_INT,
        0, MPI_COMM_WORLD
    );

    if (rank == 0) {
        printf("Partial sums:");

        for (int i = 0; i < PROCESS_COUNT; ++i) {
            printf(" %d", partial_sums[i]);
        }

        printf("\n");
    }

    int total_sum = 0;

    MPI_Reduce(
        &local_sum, &total_sum, 1, MPI_INT,
        MPI_SUM, 0, MPI_COMM_WORLD
    );

    if (rank == 0) {
        printf("Reduce result: %d\n", total_sum);
    }

    int global_sum = 0;

    MPI_Allreduce(
        &local_sum, &global_sum, 1, MPI_INT,
        MPI_SUM, MPI_COMM_WORLD
    );

    printf("Process %d: Allreduce result = %d\n", rank, global_sum);

    if (rank == 0) {
        sleep(3);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: passed the barrier\n", rank);

    MPI_Finalize();
    return 0;
}
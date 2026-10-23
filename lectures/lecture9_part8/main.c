#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    // MPI_Init(&argc, &argv);
    int provided;

    MPI_Init_thread(
        &argc,
        &argv,
        MPI_THREAD_FUNNELED,
        &provided
    );

    if (provided < MPI_THREAD_FUNNELED) {
        fprintf(stderr, "Required MPI thread support is unavailable.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long n = 10000000000LL;
    const double h = 1.0 / (double)n;

    double local_sum = 0.0;
    double total_sum = 0.0;
    double pi = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    #pragma omp parallel for reduction(+:local_sum) schedule(static)
    for (long long i = rank; i < n; i += size) {
        double x = ((double)i + 0.5) * h;
        local_sum += 4.0 / (1.0 + x * x);
    }

    MPI_Reduce(
        &local_sum,
        &total_sum,
        1,
        MPI_DOUBLE,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        pi = h * total_sum;
    }

    double local_time = MPI_Wtime() - start;
    double parallel_time = 0.0;

    MPI_Reduce(
        &local_time,
        &parallel_time,
        1,
        MPI_DOUBLE,
        MPI_MAX,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        printf("Processes: %d\n", size);
        printf("Intervals: %lld\n", n);
        printf("Pi: %.15f\n", pi);
        printf("Parallel time: %.6f seconds\n", parallel_time);
    }

    MPI_Finalize();
    return 0;
}
#include <math.h>
#include <omp.h>
#include <stdio.h>

static double compute_item(int index, int steps) {
    double value = 1.0 + (double) (index % 1000) / 1000.0;
    for (int step = 0; step < steps; ++step) {
        value = sqrt(value + 1.0);
    }
    return value;
}

static double run_serial(int count, int steps) {
    double sum = 0.0;
    for (int i = 0; i < count; ++i) {
        sum += compute_item(i, steps);
    }
    return sum;
}

static double run_parallel(int count, int steps,
                           int *actual_threads) {
    double sum = 0.0;
#pragma omp parallel default(none) \
        shared(count, steps, actual_threads) reduction(+:sum)
    {
#pragma omp single
        {
            *actual_threads = omp_get_num_threads();
        }
#pragma omp for schedule(runtime)
        for (int i = 0; i < count; ++i) {
            sum += compute_item(i, steps);
        }
    }
    return sum;
}

static double median3(double a, double b, double c) {
    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    }
    if (b > c) {
        double temp = b;
        b = c;
        c = temp;
    }
    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    }
    return b;
}

int main(void) {
    const int count = 200000;
    const int steps = 200;
    double serial_times[3];
    double parallel_times[3];
    double serial_result = 0.0;
    double parallel_result = 0.0;
    double warmup_result;
    int actual_threads = 0;
    omp_set_dynamic(0);

    warmup_result = run_serial(count, steps);
    warmup_result += run_parallel(count, steps, &actual_threads);
    printf("Warmup checksum %.12f\n", warmup_result);

    for (int trial = 0; trial < 3; ++trial) {
        double start;
        /* Alternate the order to reduce a fixed order bias. */
        if (trial % 2 == 0) {
            start = omp_get_wtime();
            serial_result = run_serial(count, steps);
            serial_times[trial] = omp_get_wtime() - start;
            start = omp_get_wtime();
            parallel_result = run_parallel(count, steps,
                                           &actual_threads);
            parallel_times[trial] = omp_get_wtime() - start;
        } else {
            start = omp_get_wtime();
            parallel_result = run_parallel(count, steps,
                                           &actual_threads);
            parallel_times[trial] = omp_get_wtime() - start;
            start = omp_get_wtime();
            serial_result = run_serial(count, steps);
            serial_times[trial] = omp_get_wtime() - start;
        }
        double tolerance = 1.0e-8 * fmax(1.0, fabs(serial_result));
        if (!isfinite(serial_result) || !isfinite(parallel_result)
            || fabs(serial_result - parallel_result) > tolerance) {
            fprintf(stderr, "Result validation failed\n");
            return 1;
        }
        printf("Trial %d serial %.6f s parallel %.6f s\n",
               trial + 1, serial_times[trial],
               parallel_times[trial]);
    }
    double serial_time = median3(serial_times[0], serial_times[1],
                                 serial_times[2]);
    double parallel_time = median3(parallel_times[0],
                                   parallel_times[1],
                                   parallel_times[2]);
    if (serial_time <= 0.0 || parallel_time <= 0.0) {
        fprintf(stderr, "Increase the workload for timing\n");
        return 1;
    }
    double speedup = serial_time / parallel_time;
    double efficiency = speedup / (double) actual_threads;
    printf("Threads %d\n", actual_threads);
    printf("Serial result %.12f\n", serial_result);
    printf("Parallel result %.12f\n", parallel_result);
    printf("Median serial %.6f s\n", serial_time);
    printf("Median parallel %.6f s\n", parallel_time);
    printf("Speedup %.3f\n", speedup);
    printf("Efficiency %.1f%%\n", efficiency * 100.0);
    return 0;
}

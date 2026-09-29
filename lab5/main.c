#define _POSIX_C_SOURCE 200809L

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

double get_time_in_seconds(void);

typedef struct {
    int label;
    long count;
    double result;
} Task;

static void heavy_calculations(Task *task) {
    double x = 6464.3232;

    for (long i = 0; i < task->count; ++i) {
        x = sqrt(x * x + 0.01);
    }

    task->result = x;
}


double run_sequential(long num_of_calc, Task* task){
    double result = 0.0;
    return result;
}

double run_parallel(long num_of_calc, Task * task) {
    double result = 0.0;
    return result;
}

int main(void) {
    int iterations = 10000;


    //Works for linux only
    long processors_count = sysconf(_SC_NPROCESSORS_ONLN);
    // long processors_count = 2;

    if (processors_count < 1) {
        fprintf(stderr, "Could not determine the logical processor count.\n");
        return EXIT_FAILURE;
    }
    printf("Logical processors: %ld\n", processors_count);


    Task seq_task = {.label = 0, .count = iterations, .result = 0.0};

    long num_of_calcs = processors_count;
    double time_before = get_time_in_seconds();
    // double sequentialResult = run_sequential(num_of_calcs, &seq_task);
    double time_after = get_time_in_seconds();
    // printf("Sequential. Number of calcs: %ld\t Duration: %.12f\ts  result: %.12f\n",num_of_calcs,
    //     time_after-time_before, sequentialResult);


    Task parallel_task = {.label = 0, .count = iterations, .result = 0.0};

    time_before = get_time_in_seconds();
    // double parallelResult = run_parallel(num_of_calcs, &parallel_task);
    time_after = get_time_in_seconds();
    // printf("Parallel. Number of calcs: %ld\t Duration: %.12f\ts  result: %.12f\n",
    //     num_of_calcs, time_after-time_before, parallelResult);

    return EXIT_SUCCESS;
}

double get_time_in_seconds(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (double)now.tv_sec
         + (double)now.tv_nsec / 1000000000.0;
}

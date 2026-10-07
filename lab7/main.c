#define _POSIX_C_SOURCE 200809L


#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define  COUNTER_THREADS  2
#define  WORKER_THREADS 5
#define  PERMITS 2

double get_time_in_seconds(void);

static void print_result(const char *name, long long actual, double seconds);


static long long iterations = 10000;
static volatile long long unsafe_counter;
static long long mutex_counter;
static atomic_llong atomic_counter;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

static sem_t slots;

static void *increment_unsafe(void *argument) {
    return NULL;
}

static void *increment_mutex(void *argument) {
    return NULL;
}

static void *increment_atomic(void *argument) {
    return NULL;
}

static double run_counter(void *(*worker)(void *)) {
    double start = get_time_in_seconds();
    //запускаємо потоки
    //очкіємо їх завершення
    //опрацьовуємо результати
    //видаляємо ці коменетарі
    return 0;
}


static void *semaphore_worker(void *argument) {
    //Захопвлюлємо одиницю семафору
    //виконуємо "роботу" sleep(1);
    //відпускаємо одиницю семафору
    //видаляємо ці коменетарі
    return NULL;
}

static void run_semaphore_demo(void) {
    //створємо семафор
    //запускаємо потоки
    //очкіємо їх завершення
    //опрацьовуємо результати
    //заврешуємо роботу з семафором
    //видаляємо ці коменетарі
}

int main(int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [iterations_per_thread]\n", argv[0]);
        return EXIT_FAILURE;
    }
    double elapsed = 0;
    int correct = 1;

    // printf("Iterations per thread: %lld; threads: %d\n", iterations, COUNTER_THREADS);
    // printf("%-22s %14s %14s %12s\n", "Method", "Expected", "Actual", "Time, ms");
    // unsafe_counter = 0;
    // elapsed = run_counter(increment_unsafe);
    // print_result("No synchronization*", unsafe_counter, elapsed);

    // mutex_counter = 0;
    // elapsed = run_counter(increment_mutex);
    // print_result("Mutex", mutex_counter, elapsed);
    // correct = (mutex_counter == iterations * COUNTER_THREADS);

    // atomic_init(&atomic_counter, 0);
    // elapsed = run_counter(increment_atomic);
    // long long actual = atomic_load(&atomic_counter);
    // print_result("Atomic", actual, elapsed);
    // correct = correct && (actual == iterations * COUNTER_THREADS);

    // run_semaphore_demo();

    pthread_mutex_destroy(&counter_mutex);

    return correct ? EXIT_SUCCESS : EXIT_FAILURE;
}

double get_time_in_seconds(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (double) now.tv_sec
           + (double) now.tv_nsec / 1000000000.0;
}

static void print_result(const char *name, long long actual, double seconds) {
    printf("%-22s %14lld %14lld %12.3f\n", name,
           iterations * COUNTER_THREADS, actual, seconds * 1000.0);
}

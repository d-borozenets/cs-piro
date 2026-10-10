#include <math.h>
#include <omp.h>
#include <stdio.h>

#define N 10000000LL
#define THREADS 4
#define DEMO_N 32
#define DEMO_STEPS 1000000


double calculate_demo_part(int interval) {
    double step = 1.0 / ((long long) DEMO_N * DEMO_STEPS);
    double sum = 0.0;
    long long first = (long long) interval * DEMO_STEPS;
    for (int j = 0; j < DEMO_STEPS; ++j) {
        double x = (first + j + 0.5) * step;
        sum += 1.0 / (1.0 + x * x);
    }
    return 4.0 * step * sum;
}

void print_distribution(const char *name, const int owners[], const double parts[]) {
    printf("\n%s\n", name);
    for (int thread = 0; thread < THREADS; ++thread) {
        printf("Thread %d:", thread);
        for (int i = 0; i < DEMO_N; ++i) {
            if (owners[i] == thread) printf(" %d", i);
        }
        printf("\n");
    }
    double pi = 0.0;
    for (int i = 0; i < DEMO_N; ++i) pi += parts[i];
    printf("Demo pi: %.15f\n", pi);
}

/* This demonstration is separate from the timed calculations. */
void show_distribution(int chunk) {
    int owners[DEMO_N];
    double parts[DEMO_N];
    char name[64];

#pragma omp parallel for num_threads(THREADS)
    for (int i = 0; i < DEMO_N; ++i) {
        owners[i] = omp_get_thread_num();
        parts[i] = calculate_demo_part(i);
    }

}

double pi_sequential(long long n) {
    //TODO: використайте вашу релізацію з попередніх робіт
    return 0.0;
}

double pi_static_default(long long n, int chunk) {
    //TODO: використайте вашу релізацію з попередніх робіт (з використанням редукції)
    //TODO: застосуйте schedule, що відповідає імені функції
    return 0.0;
}

double pi_static(long long n, int chunk) {
    //TODO: використайте вашу релізацію з попередніх робіт (з використанням редукції)
    //TODO: застосуйте schedule, що відповідає імені функції
    return 0.0;
}

double pi_dynamic(long long n, int chunk) {
    //TODO: використайте вашу релізацію з попередніх робіт (з використанням редукції)
    //TODO: застосуйте schedule, що відповідає імені функції
    return 0.0;
}

double pi_guided(long long n, int chunk) {
    //TODO: використайте вашу релізацію з попередніх робіт (з використанням редукції)
    //TODO: застосуйте schedule, що відповідає імені функції
    return 0.0;
}

int main(void) {
    omp_set_dynamic(0);
    int actual_threads = 0;
#pragma omp parallel num_threads(THREADS)
    {
#pragma omp single
        actual_threads = omp_get_num_threads();
    }
    if (actual_threads != THREADS) {
        fprintf(stderr, "Expected %d threads, got %d.\n", THREADS, actual_threads);
        return 1;
    }

    return 0;
}

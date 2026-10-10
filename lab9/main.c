#define N 1000000000LL
#define RUNS 3
#define MAX_THREADS 4

double pi_sequential(long long n) {
    return 0.0;
}

double pi_parallel(long long n, int requested_threads, int *used_threads) {
    double partial_sums[MAX_THREADS] = {0.0};


    //TODO: порахувати рельну кількість виористаних потоків actual_threads
    *used_threads = 0;
    return 0.0;
}

double average(const double *times, int count) {
    double sum = 0.0;
    for (int i = 0; i < count; ++i) {
        sum += times[i];
    }
    return sum / count;
}

int main(void) {
    return 0;
}

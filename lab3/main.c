#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long long three_sum_On3(const int *values, int n) {
    long long count = 0;

    return count;
}

int compare_ints(const void *first, const void *second) {
    int a = *(const int *) first;
    int b = *(const int *) second;

    return (a > b) - (a < b);
}

long long three_sum_On2(int *values, int n) {
    qsort(values, n, sizeof(int), compare_ints);

    long long count = 0;

    return count;
}

int main(void) {
    const int n = 1000;
    int *values = malloc(n * sizeof(*values));

    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        values[i] = n / 2 - i;
    }

    struct timespec start, end;
    double elapsed = 0;



    // clock_gettime(CLOCK_MONOTONIC, &start);
    // long long on3_count = three_sum_On3(values, n);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    //
    // elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    //
    // printf("on3_count: %lld\n", on3_count);
    // printf("Time: %.6f milliseconds\n", elapsed * 1000);



    // clock_gettime(CLOCK_MONOTONIC, &start);
    // long long on2_count = three_sum_On2(values, n);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    //
    // elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    // printf("on2_count: %lld\n", on2_count);
    // printf("Time: %.6f milliseconds\n", elapsed * 1000);



    free(values);
    return EXIT_SUCCESS;
}

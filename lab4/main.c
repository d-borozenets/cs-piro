#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#ifdef __aarch64__
#else
#include <xmmintrin.h>   // SSE
#include <immintrin.h>   // AVX (на майбутнє)
#endif

#define N 4
#define COLUMNS 4096
#define ROWS 4096
#define THREAD_COUNT 2

float *generate(size_t element_count);
double get_time_in_seconds(void);

void apply_scalar(const float *image, const float *filter, float *result,
                  int start_row, int row_count);
void apply_simd(const float *image, const float *filter, float *result,
                int start_row, int row_count);
void apply_hybrid(const float *image, const float *filter, float *result,
                  int thread_count);

int main(void) {
    printf("Hello, world!");
    srand((unsigned int)time(NULL));
    size_t element_count = (size_t)ROWS * COLUMNS * N;

    // free(image);
    // free(filter);
    // free(result);
    return EXIT_SUCCESS;
}

float *generate(size_t element_count) {
    float *values = malloc(element_count * sizeof(*values));
    if (values == NULL) {
        return NULL;
    }

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLUMNS; ++x) {
            for (int k = 0; k < N; ++k) {
                size_t pos = ((size_t)y * COLUMNS + x) * N + k;
                values[pos] = (float)((double)rand() / RAND_MAX);
            }
        }
    }
    return values;
}

double get_time_in_seconds(void) {
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (double)now.tv_sec + (double)now.tv_nsec / 1000000000.0;
}

void apply_scalar(const float *image, const float *filter, float *result,
                  int start_row, int row_count) {
}

void apply_simd(const float *image, const float *filter, float *result,
                int start_row, int row_count) {
}

void apply_hybrid(const float *image, const float *filter, float *result,
                  int thread_count) {
}
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#ifdef __aarch64__
#else
#include <xmmintrin.h>   // SSE
#include <immintrin.h>   // AVX
#endif

#define N 4
#define COLUMNS 4096
#define ROWS 4096

float *image;
float *filter;
float *result;

float *generate(size_t element_count);
double get_time_in_milliseconds(void);

void apply_scalar(int start_row, int row_count);
void apply_simd(int start_row, int row_count);
void apply_hybrid();

int main(void) {
    printf("Hello, world!");
    srand((unsigned int)time(NULL));
    size_t element_count = (size_t)ROWS * COLUMNS * N;
    size_t buffer_size = element_count * sizeof(float);

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

double get_time_in_milliseconds(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (double)now.tv_sec * 1000.0
         + (double)now.tv_nsec / 1000000.0;
}


void apply_scalar(int start_row, int row_count) {
}

void apply_simd(int start_row, int row_count) {
}

void *process_first_half(void *argument) {
    return NULL;
}

void *process_second_half(void *argument) {
    return NULL;
}

void apply_hybrid() {
}
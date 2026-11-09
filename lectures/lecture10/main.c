#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        const int thread_id = omp_get_thread_num();
        const int place_id = omp_get_place_num();

#pragma omp critical
        {
            printf("Thread %d -> place %d\n", thread_id, place_id);
        }
    }

    return 0;
}
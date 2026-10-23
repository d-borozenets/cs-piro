#include <stdio.h>
#include <omp.h>

int main(void) {
// #pragma omp parallel default(none)
//     {
//         const int id = omp_get_thread_num();
// // #pragma omp critical(output)
//         printf("Thread %d step 1\n", id);
// #pragma omp barrier
// // #pragma omp critical(output)
//         printf("Thread %d step 2\n", id);
//     }


    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int sum = 10;
    //         long long count = 0;
    //         double total = 0.0;
    // #pragma omp parallel for default(none) shared(values, n, count, total)
    //         for (int i = 0; i < n; ++i) {
    //             double value = values[i];
    //             if (value > 0.0) {
    // #pragma omp critical(statistics)
    //                 {
    //                     ++count;
    //                     total += value;
    //                 }
    //             }
    //         }

    #pragma omp parallel for default(none) \
        shared(values, n) reduction(+:sum)
        for (int i = 0; i < n; ++i) {
            sum += values[i];
        }

    return 0;
}

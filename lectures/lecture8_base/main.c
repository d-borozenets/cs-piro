#include <stdio.h>
#include <omp.h>

int main(void) {
    printf("Before parallel region\n");
    // #pragma omp parallel default(none)
    //     {
    //         int id = omp_get_thread_num();
    //         int team_size = omp_get_num_threads();
    // // #pragma omp critical(output)
    //         {
    //             printf("Hello from thread %d of %d\n",
    //                    id, team_size);
    //         }
    //     }

    // #pragma omp parallel
    // {
    //     for (int i = 0; i < 8; ++i) {
    //         printf("Thread %d iteration %d\n",
    //                omp_get_thread_num(), i);
    //     }
    // }

// #pragma omp parallel default(none)
//     {
// #pragma omp for
//         for (int i = 0; i < 8; ++i) {
//             printf("Thread %d iteration %d\n",
//                    omp_get_thread_num(), i);
//         }
//     }

// #pragma omp parallel for default(none)//default(none)   shared(input, output, n)
//     for (int i = 0; i < 8; ++i) {
//         printf("Thread %d iteration %d\n",
//                omp_get_thread_num(), i);
//     }

    int temp = 100;
#pragma omp parallel default(none)  firstprivate(temp)
    {
        // printf("Private temp before: %d\n", temp);
        temp += omp_get_thread_num();
        printf("Private temp after:  %d\n", temp);
    }
    printf("Outer temp %d\n", temp);

    printf("After parallel region\n");
    return 0;
}

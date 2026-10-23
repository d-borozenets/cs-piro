#include <omp.h>
#include <stdio.h>
int main(void)
{
    int owner[12];
    omp_set_dynamic(0);
#pragma omp parallel for num_threads(3) default(none) \
shared(owner) schedule(static, 3)
    for (int i = 0; i < 12; ++i) {
        owner[i] = omp_get_thread_num();
    }





    for (int i = 0; i < 12; ++i) {
        printf("Iteration %2d thread %d\n", i, owner[i]);
    }




    return 0;
}

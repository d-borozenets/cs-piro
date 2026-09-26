#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int num;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        for (num = 0; num < 6; num++) {
            printf("Child: num = %d\n", num);
            fflush(stdout);
            sleep(1);
        }
    } else {
        for (num = 0; num < 6; num += 2) {
            printf("Parent: num = %d\n", num);
            fflush(stdout);
            sleep(1);
        }
    }

    return EXIT_SUCCESS;
}

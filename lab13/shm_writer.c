#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/lab13_memory"
#define BUFFER_SIZE 256

int main(void) {
    int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(fd, BUFFER_SIZE) == -1) {
        perror("ftruncate");
        close(fd);
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    char *message = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE,
                         MAP_SHARED, fd, 0);
    if (message == MAP_FAILED) {
        perror("mmap");
        close(fd);
        shm_unlink(SHM_NAME);
        return EXIT_FAILURE;
    }

    close(fd);

    snprintf(message, BUFFER_SIZE, "%s", "Hello from shared memory!");

    printf("Writer: PID=%ld\n", (long)getpid());
    printf("Shared memory: %s\n", SHM_NAME);
    printf("Message: %s\n", message);

    munmap(message, BUFFER_SIZE);

    // The reader will remove the shared memory name.
    return EXIT_SUCCESS;
}
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/lab13_memory"
#define BUFFER_SIZE 256

int main(void) {
    int fd = shm_open(SHM_NAME, O_RDONLY, 0);
    if (fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    struct stat info;
    if (fstat(fd, &info) == -1) {
        perror("fstat");
        close(fd);
        return EXIT_FAILURE;
    }

    if (info.st_size < BUFFER_SIZE) {
        fprintf(stderr, "Shared memory object is too small\n");
        close(fd);
        return EXIT_FAILURE;
    }

    const char *message = mmap(NULL, BUFFER_SIZE, PROT_READ,
                               MAP_SHARED, fd, 0);
    if (message == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    printf("Reader: PID=%ld\n", (long)getpid());
    printf("Shared memory: %s\n", SHM_NAME);
    printf("Message: %.*s\n", BUFFER_SIZE, message);

    munmap((void *)message, BUFFER_SIZE);

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        return EXIT_FAILURE;
    }

    printf("Shared memory name removed.\n");
    return EXIT_SUCCESS;
}
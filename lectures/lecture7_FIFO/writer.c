#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/lecture_fifo"

int main(void) {
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        return EXIT_FAILURE;
    }

    printf("FIFO created at %s Waiting for reader\n", FIFO_PATH);
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        unlink(FIFO_PATH);
        return EXIT_FAILURE;
    }

    const char *message = "Hello through FIFO\n";

    printf("Reader ready. Sending message");
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        unlink(FIFO_PATH);
        return EXIT_FAILURE;
    }

    if (close(fd) == -1) {
        perror("close");
        unlink(FIFO_PATH);
        return EXIT_FAILURE;
    }

    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

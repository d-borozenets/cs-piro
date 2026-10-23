#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/lecture_fifo"
#define BUFFER_SIZE 128

int main(void) {
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];

    for (;;) {
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));

        if (bytes_read == 0) {
            break;
        }

        if (bytes_read == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("read");
            close(fd);
            return EXIT_FAILURE;
        }

        if (fwrite(buffer, 1, (size_t) bytes_read, stdout)
            != (size_t) bytes_read) {
            perror("fwrite");
            close(fd);
            return EXIT_FAILURE;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

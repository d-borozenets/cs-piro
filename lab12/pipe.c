#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    double x;
    double y;
    double z;
} Vector;

int main(void) {
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        close(pipe_fd[1]);

        Vector received;
        ssize_t bytes_read = read(pipe_fd[0], &received, sizeof(received));

        if (bytes_read == -1) {
            perror("read");
            close(pipe_fd[0]);
            return EXIT_FAILURE;
        }

        if (bytes_read != (ssize_t)sizeof(received)) {
            fprintf(stderr, "Incomplete vector received\n");
            close(pipe_fd[0]);
            return EXIT_FAILURE;
        }

        printf("Child: received vector (%.2f, %.2f, %.2f)\n",
               received.x, received.y, received.z);

        close(pipe_fd[0]);
        return EXIT_SUCCESS;
    }

    close(pipe_fd[0]);

    Vector vector = {3.0, 4.0, 0.0};

    printf("Parent: sending vector (%.2f, %.2f, %.2f)\n",
           vector.x, vector.y, vector.z);
    fflush(stdout);

    ssize_t bytes_written = write(pipe_fd[1], &vector, sizeof(vector));
    int result = EXIT_SUCCESS;

    if (bytes_written == -1) {
        perror("write");
        result = EXIT_FAILURE;
    } else if (bytes_written != (ssize_t)sizeof(vector)) {
        fprintf(stderr, "Incomplete vector sent\n");
        result = EXIT_FAILURE;
    }

    close(pipe_fd[1]);

    int status;

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return result;
}
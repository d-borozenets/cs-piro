#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 128

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
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        close(pipe_fd[1]);

        printf("Child received: ");

        while ((bytes_read = read(
                    pipe_fd[0],
                    buffer,
                    sizeof(buffer))) > 0) {
            fwrite(buffer, 1, (size_t) bytes_read, stdout);
        }

        if (bytes_read == -1) {
            perror("read");
            close(pipe_fd[0]);
            return EXIT_FAILURE;
        }

        printf("\n");
        close(pipe_fd[0]);

        return EXIT_SUCCESS;
    }

    const char *message = "Hello from parent";

    close(pipe_fd[0]);

    if (write(
            pipe_fd[1],
            message,
            strlen(message)) == -1) {
        perror("write");
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0);
        return EXIT_FAILURE;
    }

    close(pipe_fd[1]);
    waitpid(pid, NULL, 0);

    return EXIT_SUCCESS;
}

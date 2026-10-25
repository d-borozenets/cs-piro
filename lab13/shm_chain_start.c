#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/lab13_chain"
#define BUFFER_SIZE 256
#define PROCESS_COUNT 4

static const char *SEM_NAMES[PROCESS_COUNT] = {
    "/lab13_sem0",
    "/lab13_sem1",
    "/lab13_sem2",
    "/lab13_sem3"
};

typedef struct {
    int fd;
    char *message;
    sem_t *semaphores[PROCESS_COUNT];
    int shm_created;
    int sem_created;
} Resources;

static int open_resources(Resources *r, int id) {
    if (id == 0) {
        r->fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    } else {
        r->fd = shm_open(SHM_NAME, O_RDWR, 0);
    }

    if (r->fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (id == 0) {
        r->shm_created = 1;

        if (ftruncate(r->fd, BUFFER_SIZE) == -1) {
            perror("ftruncate");
            return EXIT_FAILURE;
        }
    }

    struct stat info;
    if (fstat(r->fd, &info) == -1) {
        perror("fstat");
        return EXIT_FAILURE;
    }

    if (info.st_size < BUFFER_SIZE) {
        fprintf(stderr, "Shared memory object is too small\n");
        return EXIT_FAILURE;
    }

    r->message = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE,
                      MAP_SHARED, r->fd, 0);
    if (r->message == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }


    for (int i = 0; i < PROCESS_COUNT; ++i) {
        if (id == 0) {
            r->semaphores[i] = sem_open(
                SEM_NAMES[i], O_CREAT | O_EXCL, 0600, 0
            );
        } else {
            r->semaphores[i] = sem_open(SEM_NAMES[i], 0);
        }

        if (r->semaphores[i] == SEM_FAILED) {
            perror("sem_open");
            return EXIT_FAILURE;
        }

        if (id == 0) {
            ++r->sem_created;
        }
    }

    return EXIT_SUCCESS;
}

static int release_resources(Resources *r) {
    int result = EXIT_SUCCESS;

    for (int i = 0; i < PROCESS_COUNT; ++i) {
        if (r->semaphores[i] != SEM_FAILED) {
            sem_close(r->semaphores[i]);
        }
    }

    if (r->message != MAP_FAILED) {
        munmap(r->message, BUFFER_SIZE);
    }

    if (r->fd != -1) {
        close(r->fd);
    }

    // Remove only names created by this process.
    for (int i = 0; i < r->sem_created; ++i) {
        if (sem_unlink(SEM_NAMES[i]) == -1) {
            perror("sem_unlink");
            result = EXIT_FAILURE;
        }
    }

    if (r->shm_created && shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        result = EXIT_FAILURE;
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) != 1 ||
        argv[1][0] < '0' || argv[1][0] > '3') {
        fprintf(stderr, "Usage: %s <0|1|2|3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int id = argv[1][0] - '0';

    Resources resources = {
        .fd = -1,
        .message = MAP_FAILED,
        .shm_created = 0,
        .sem_created = 0
    };

    for (int i = 0; i < PROCESS_COUNT; ++i) {
        resources.semaphores[i] = SEM_FAILED;
    }

    if (open_resources(&resources, id) != EXIT_SUCCESS) {
        release_resources(&resources);
        return EXIT_FAILURE;
    }

    char *message = resources.message;

    if (id == 0) {
        snprintf(message, BUFFER_SIZE, "%s", "Hello");

        printf("Process 0: PID=%ld, initialization complete.\n",
               (long)getpid());
        printf("Shared memory: %s, address=%p\n",
               SHM_NAME, (void *)message);
        printf("Initial message: %s\n", message);
        fflush(stdout);

        // TODO: Дозвольте процесу 1 почати обробку повідомлення.
        // TODO: Дочекайтеся завершення обробки повідомлення процесом 3.

        // TODO: Замініть цю тимчасову паузу синхронізацією через семафори.
        printf("Run participants, then press Enter to clean up.\n");
        fflush(stdout);
        getchar();

        printf("Process 0: final message: %s\n", message);
    } else {
        printf("Process %d: PID=%ld, address=%p\n",
               id, (long)getpid(), (void *)message);
        fflush(stdout);

        // TODO: Дочекайтеся своєї черги на обробку повідомлення.
        // TODO: Допишіть A, B або C відповідно до номера процесу.

        printf("Process %d: message: %s\n", id, message);
        fflush(stdout);

        // TODO: Дозвольте наступному процесу продовжити роботу.
        // Процес 3 має повідомити процес 0 про завершення обробки.
    }

    return release_resources(&resources);
}
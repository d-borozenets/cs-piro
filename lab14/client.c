#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUF_SIZE 64
#define ADDR "127.0.0.1"

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main() {
  struct sockaddr_in addr;
  int sfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, ADDR, &addr.sin_addr) <= 0) {
    handle_error("inet_pton");
  }

  printf("Connecting to %s:%d\n", ADDR, PORT);
  int res = connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (res == -1) {
    handle_error("connect");
  }
  printf("Connected to server.\n");

  while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 1) {
    // Для підключеного TCP-сокета можна використати write() замість send() з прапорцями 0.
    // write() працює з файловим дескриптором, який тут посилається на сокет.
    if (write(sfd, buf, num_read) != num_read) {
    // if (send(sfd, buf, num_read, 0) != num_read) {
      handle_error("write");
    }
    printf("Just sent %zd bytes.\n", num_read);
  }

  if (num_read == -1) {
    handle_error("read");
  }

  close(sfd);
  exit(EXIT_SUCCESS);
}

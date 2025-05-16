#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(pipefd[1], F_GETFL, 0);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);


    size_t nbytes = 65536;
    char *buffer = malloc(nbytes);
    memset(buffer, 'A', nbytes);

    ssize_t count = write(pipefd[1], buffer, nbytes);
    if (count == -1) {
        perror("write");
    } else {
        printf("Requested to write %zu bytes, actually wrote %zd bytes\n", nbytes, count);
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
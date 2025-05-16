#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};

    int fd = open("temp.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (write(fd, data, sizeof(data)) != sizeof(data)) {
        perror("write");
        close(fd);
        return 1;
    }

    lseek(fd, 0, SEEK_SET);

    lseek(fd, 3, SEEK_SET);

    unsigned char buffer[4];

	ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Прочитані байти: ");
    for (int i = 0; i < bytes_read; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    remove("temp.bin");

    return 0;
}

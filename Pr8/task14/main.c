#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	const char *filename = "sample.txt";
	int fd;
	ssize_t bytes_read;
	char buffer[5]; 

	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open for write");
		return 1;
	}

	write(fd, "ABCDEFGHIJ", 10); 
	close(fd);

	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open for read");
		return 1;
	}

	buffer[4] = '\0'; 

	
	bytes_read = pread(fd, buffer, 4, 0);
	if (bytes_read > 0)
	{
		printf("pread з позиції 0: %s\n", buffer); 
	}

	
	bytes_read = pread(fd, buffer, 4, 4);
	if (bytes_read > 0)
	{
		printf("pread з позиції 4: %s\n", buffer); 
	}

	
	bytes_read = pread(fd, buffer, 4, 6);
	if (bytes_read > 0)
	{
		printf("pread з позиції 6: %s\n", buffer); 
	}

	close(fd);
	return 0;
}

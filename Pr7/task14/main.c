#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define MIN_TEXT_LEN 20

int is_printable_text(const char *buf, size_t size)
{
	int printable = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if ((buf[i] >= 32 && buf[i] <= 126) || buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\t')
		{
			printable++;
		}
	}
	return printable > size * 0.8;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Використання: %s <шлях_до_пристрою_чи_файлу>\n", argv[0]);
		return 1;
	}

	FILE *input = fopen(argv[1], "rb");
	if (!input)
	{
		perror("Не вдалось відкрити файл");
		return 1;
	}

	char buffer[BLOCK_SIZE];
	int file_count = 0;
	FILE *out = NULL;
	int writing = 0;

	while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
	{
		if (is_printable_text(buffer, BLOCK_SIZE))
		{
			if (!writing)
			{
				// Починаємо писати новий файл
				char filename[64];
				snprintf(filename, sizeof(filename), "recovered_%03d.txt", ++file_count);
				out = fopen(filename, "wb");
				if (!out)
				{
					perror("Не вдалося створити файл");
					fclose(input);
					return 1;
				}
				writing = 1;
				printf("Відновлення файлу %s\n", filename);
			}
			fwrite(buffer, 1, BLOCK_SIZE, out);
		}
		else
		{
			if (writing)
			{
				fclose(out);
				writing = 0;
			}
		}
	}

	if (writing)
		fclose(out);
	fclose(input);

	printf("Відновлення завершено. Відновлено файлів: %d\n", file_count);
	return 0;
}

// echo -e "Hello, this is a test.\n\n\nSome random text here.\n\n\nAnother block of text." > disk_image.bin
// ./recover disk_image.bin

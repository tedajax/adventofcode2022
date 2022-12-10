#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file(const char *filename, size_t *bytes_read);

int main(int argc, char *argv[])
{
	return 0;
}

char *read_file(const char *filename, size_t *bytes_read)
{
	struct stat info;
	if (stat(filename, &info) < 0)
	{
		return NULL;
	}

	FILE *fp = fopen(filename, "r");

	if (!fp)
		return NULL;

	char *buffer = (char *)calloc(info.st_size + 1, 1);
	size_t read = fread(buffer, 1, (size_t)info.st_size, fp);

	if (bytes_read)
		*bytes_read = read;

	return buffer;
}

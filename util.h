#pragma once

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

size_t read_file_to_buffer(const char *filename, char **buf_ptr)
{
	FILE *fp = fopen(filename, "r");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	size_t len = (size_t)ftell(fp);
	rewind(fp);

	char *buffer = (char *)malloc(len + 1);
	memset(buffer, 0, len + 1);

	char *curr = buffer;
	while (!feof(fp))
	{
		*curr = fgetc(fp);
		curr++;
	}

	ptrdiff_t read_bytes = curr - buffer;

	buffer[len] = 0;

	*buf_ptr = buffer;

	return (size_t)read_bytes;
}

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

struct point
{
	int x, y;
};

struct entry
{
	uint64_t key;
	struct point value;
};

char *read_file(const char *filename, size_t *bytes_read);

int touching(const struct point *head, const struct point *tail)
{
	int dx = abs(head->x - tail->x);
	int dy = abs(head->y - tail->y);

	if (dx == 0 && dy == 0)
		return 1;
	if (dx == 1 && dy == 0)
		return 1;
	if (dx == 0 && dy == 1)
		return 1;
	if (dx == 1 && dy == 1)
		return 1;

	return 0;
}

int touching_close(const struct point *head, const struct point *tail, int mx, int my)
{
	int dx = abs(head->x + mx - tail->x);
	int dy = abs(head->y + my - tail->y);

	return (dx == 0 && dy == 0) || (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

void move(struct point *head, struct point *tail, struct point delta)
{
	head->x += delta.x;
	head->y += delta.y;

	if (!touching(head, tail))
	{
		if (head->x == tail->x || head->y == tail->y)
		{
			tail->x += delta.x;
			tail->y += delta.y;
		}
		else
		{
			tail->x += delta.x;
			tail->y += delta.y;

			if (delta.x != 0)
				tail->y = head->y;
			else if (delta.y != 0)
				tail->x = head->x;
		}
	}
}

int sgn(int v)
{
	if (v == 0)
		return 0;
	else if (v < 0)
		return -1;
	else
		return 1;
}

void move_body_helper(struct point body[10], struct point delta, int offset)
{
	struct point *b0 = NULL, *b1 = NULL, *b2 = NULL;
	if (offset > 0)
		b0 = &body[offset - 1];
	b1 = &body[offset];
	if (offset < 9)
		b2 = &body[offset + 1];

	if (b0 && delta.x != 0 && delta.y != 0)
	{
		if (touching_close(b1, b0, delta.x, 0))
			delta.y = 0;
		else if (touching_close(b1, b0, 0, delta.y))
			delta.x = 0;
	}

	b1->x += delta.x;
	b1->y += delta.y;

	if (!b2)
		return;

	if (!touching(b1, b2))
	{
		if (b1->x != b2->x && b1->y != b2->y)
		{
			if (delta.x != 0)
				delta.y = sgn(b1->y - b2->y);
			else if (delta.y != 0)
				delta.x = sgn(b1->x - b2->x);
		}

		move_body_helper(body, delta, offset + 1);
	}
}

void move_body(struct point body[10], struct point delta)
{
	move_body_helper(body, delta, 0);
}

uint64_t hash_point(const struct point *p)
{
	return ((uint64_t)p->x << 32) + ((uint64_t)p->y);
}

int main(int argc, char *argv[])
{
	size_t len;
	char *text = read_file("day9_input.txt", &len);

	struct point body[10] = {0};
	struct point head = {0}, tail = {0};
	struct entry *visited1 = NULL;
	struct entry *visited2 = NULL;

	char *line = strtok(text, "\n");
	while (line && *line > 0)
	{
		char dir;
		int num;
		sscanf(line, "%c %d", &dir, &num);

		struct point delta = {0};
		if (dir == 'L')
			delta.x = -1;
		if (dir == 'R')
			delta.x = 1;
		if (dir == 'U')
			delta.y = -1;
		if (dir == 'D')
			delta.y = 1;

		for (int i = 0; i < num; ++i)
		{
			{
				move(&head, &tail, delta);
				uint64_t key = hash_point(&tail);
				if (hmgeti(visited1, key) < 0)
				{
					hmput(visited1, key, tail);
				}
			}

			{
				move_body(body, delta);
				uint64_t key = hash_point(&body[9]);
				if (hmgeti(visited2, key) < 0)
				{
					hmput(visited2, key, tail);
				}
			}
		}

		line = strtok(NULL, "\n");
	}

	printf("Part 1: %d\n", hmlen(visited1));
	printf("Part 2: %d\n", hmlen(visited2));

	free(text);

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

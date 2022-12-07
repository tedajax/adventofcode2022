#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

enum shape
{
	e_shape_none,
	e_shape_rock,
	e_shape_paper,
	e_shape_scissors,
};

enum shape Winners[] = {
	e_shape_none,
	e_shape_paper,
	e_shape_scissors,
	e_shape_rock,
};

enum shape Losers[] = {
	e_shape_none,
	e_shape_scissors,
	e_shape_rock,
	e_shape_paper,
};

int score_round(enum shape opp, enum shape self)
{
	if (opp == e_shape_none || self == e_shape_none)
		return -1;

	int shape_score = (int)self;
	int outcome_score = 0;

	if (self == opp)
		outcome_score = 3;
	else if (self == Winners[opp])
		outcome_score = 6;

	return shape_score + outcome_score;
}

enum shape get_shape(char c)
{
	switch (toupper(c))
	{
	case 'A':
	case 'X':
		return e_shape_rock;
	case 'B':
	case 'Y':
		return e_shape_paper;
	case 'C':
	case 'Z':
		return e_shape_scissors;
	default:
		return e_shape_none;
	}
}

size_t read_file_to_buffer(const char *filename, char **buf_ptr)
{
	FILE *fp = fopen(filename, "r");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	size_t len = (size_t)ftell(fp);
	rewind(fp);

	char *buffer = (char *)malloc(len + 1);
	char *curr = buffer;
	*buf_ptr = buffer;
	char c;
	while (!feof(fp))
	{
		*curr = fgetc(fp);
		curr++;
	}

	buffer[len] = 0;

	return len;
}

int score_round2(const char *in)
{
	enum shape opp = get_shape(in[0]);
	int outcome = -1;
	switch (toupper(in[2]))
	{
	case 'X':
		outcome = 0;
		break;
	case 'Y':
		outcome = 1;
		break;
	case 'Z':
		outcome = 2;
		break;
	}

	enum shape self = e_shape_none;
	switch (outcome)
	{
	case 0:
		self = Losers[opp];
		break;
	case 1:
		self = opp;
		break;
	case 2:
		self = Winners[opp];
		break;
	}

	if (opp == e_shape_none || self == e_shape_none)
		return -1;

	return score_round(opp, self);
}

int main(int argc, char *argv[])
{
	char *file_text;
	size_t len = read_file_to_buffer("day2_input.txt", &file_text);

	enum shape opp,
		self;
	int score = 0;
	int score2 = 0;

	char *line = strtok(file_text, "\n");
	while (line)
	{
		if (strlen(line) < 3)
			break;
		printf("%s\n", line);
		opp = get_shape(line[0]);
		self = get_shape(line[2]);
		int round = score_round(opp, self);
		if (round < 0)
		{
			break;
		}
		score += round;
		score2 += score_round2(line);
		line = strtok(NULL, "\n");
	}

	free(file_text);

	printf("Score: %d\n", score);
	printf("Score2: %d\n", score2);

	return 0;
}
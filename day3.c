#include "util.h"

int ItemPriorities[256] = {0};

int score_rucksack(char *input)
{
	bool found[256] = {0};
	size_t len = strlen(input);
	size_t mid = len / 2;
	for (size_t i = 0; i < mid; ++i)
	{
		found[input[i]] = true;
	}

	for (size_t i = mid; i < len; ++i)
	{
		if (found[input[i]])
		{
			return ItemPriorities[input[i]];
		}
	}
	return 0;
}

void count_items(char *inv, int counts[256])
{
	bool found[256] = {0};
	char *curr = inv;
	char c;
	while ((c = *curr))
	{
		if (!isalpha(c))
		{
			printf("error\n");
		}

		if (!found[c])
		{
			printf("common: %c\n", c);
			found[c] = true;
			counts[c]++;
		}
		curr++;
	}
}

int find_comn_prio(char *group[3])
{
	int counts[256] = {0};
	count_items(group[0], counts);
	count_items(group[1], counts);
	count_items(group[2], counts);

	int result = 0;
	for (int c = 0; c < 256; ++c)
	{
		if (counts[c] == 3)
		{
			if (result == 0)
			{
				result = ItemPriorities[c];
			}
			else
			{
				return -1;
			}
		}
	}
	return result;
}

int main(int argc, char *argv[])
{
	const char *delim = "\n";
	int prio = 1;
	for (char c = 'a'; c <= 'z'; c++)
		ItemPriorities[c] = prio++;
	for (char c = 'A'; c <= 'Z'; c++)
		ItemPriorities[c] = prio++;

	char *text;
	size_t len = read_file_to_buffer("day3_input.txt", &text);
	char *buffer = (char *)malloc(len);
	memcpy(buffer, text, len);

	int score = 0;
	int score2 = 0;
	char *line = strtok(buffer, delim);
	char *group[3] = {0};
	int gid = 0;
	while (line)
	{
		score += score_rucksack(line);
		group[gid++] = line;
		if (gid == 3)
		{
			gid = 0;
			score2 += find_comn_prio(group);
		}
		line = strtok(NULL, delim);
	}

	free(buffer);

	free(text);

	printf("Score1: %d\n", score);
	printf("Score2: %d\n", score2);

	return 0;
}

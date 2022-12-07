#include "util.h"

#define STACK_NUM 9

char stacks[STACK_NUM][256] = {
	"NDMQBPZ",
	"CLZQMDHV",
	"QHRDVFZG",
	"HGDFN",
	"NFQ",
	"DQVZFBT",
	"QMTZDVSH",
	"MGFPNQ",
	"BWRM",
};

int counts[STACK_NUM] = {7, 8, 8, 5, 3, 7, 8, 6, 4};

int move(int count, int from, int to)
{
	int fromIdx = from - 1;
	int toIdx = to - 1;

	for (int i = 0; i < count; ++i)
	{
		stacks[toIdx][counts[toIdx]] = stacks[fromIdx][counts[fromIdx] - 1];
		counts[fromIdx]--;
		counts[toIdx]++;
	}
}

int movem(int count, int from, int to)
{
	int fromIdx = from - 1;
	int toIdx = to - 1;

	for (int i = 0; i < count; ++i)
	{
		stacks[toIdx][counts[toIdx] + i] = stacks[fromIdx][counts[fromIdx] - (count - i)];
	}
	counts[toIdx] += count;
	counts[fromIdx] -= count;
}

void print_top_stacks()
{
	for (int i = 0; i < STACK_NUM; ++i)
	{
		char c = ' ';
		if (counts[i] != 0)
		{
			c = stacks[i][counts[i] - 1];
		}
		printf("%c ", c);
	}
	printf("\n");
	for (int i = 0; i < STACK_NUM; ++i)
		printf("%d ", i + 1);
	printf("\n");
}

int main(int argc, char *argv[])
{
	char *text;
	size_t len = read_file_to_buffer("day5_input.txt", &text);

	char *line = strtok(text, "\n");

	while (line && *line > 0)
	{
		int count, from, to;
		sscanf(line, "move %d from %d to %d", &count, &from, &to);

		// part 1
		// move(count, from, to);

		// part 2
		print_top_stacks();

		movem(count, from, to);

		line = strtok(NULL, "\n");
	}

	print_top_stacks();

	return 0;
}

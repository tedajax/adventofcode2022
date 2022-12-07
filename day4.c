#include "util.h"

struct range
{
	int lower, upper;
};

void parse_ranges(char *line, struct range *r1, struct range *r2)
{
	int sepidx[4];

	{
		char *curr = line;
		char c;
		int idx = 0;
		int si = 0;
		while ((c = *curr))
		{
			if (c == '-' || c == ',')
			{
				sepidx[si++] = idx;
			}
			idx++;
			curr++;
		}
		sepidx[3] = idx;

		if (si < 3)
		{
			memset(r1, 0, sizeof(struct range));
			memset(r2, 0, sizeof(struct range));
			return;
		}
	}

	char strbufs[4][16] = {0};

	int head = 0, tail = 0;
	int si = 0;
	while (si < 4)
	{
		tail = sepidx[si];
		memcpy(strbufs[si], line + head, tail - head);
		head = tail + 1;
		si++;
	}

	int parsed[4] = {0};

	for (int i = 0; i < 4; ++i)
	{
		parsed[i] = strtol(strbufs[i], NULL, 10);
	}

	r1->lower = parsed[0];
	r1->upper = parsed[1];
	r2->lower = parsed[2];
	r2->upper = parsed[3];
}

bool range_overlaps(const struct range *r, int pos)
{
	return pos >= r->lower && pos <= r->upper;
}

int main(int argc, char *argv[])
{
	char *text;
	size_t len = read_file_to_buffer("day4_input.txt", &text);

	char *line = strtok(text, "\n");

	struct range r1, r2;

	int sum = 0;
	int sum2 = 0;

	while (line && *line > 0)
	{
		parse_ranges(line, &r1, &r2);
		printf("%d-%d,%d-%d\n", r1.lower, r1.upper, r2.lower, r2.upper);

		if (r1.lower <= r2.lower && r1.upper >= r2.upper || r2.lower <= r1.lower && r2.upper >= r1.upper)
		{
			sum++;
		}

		if (r1.upper >= r2.lower && r1.lower <= r2.upper)
		{
			sum2++;
		}

		line = strtok(NULL, "\n");
	}

	printf("sum: %d\n", sum);
	printf("sum2: %d\n", sum2);

	free(text);

	return 0;
}

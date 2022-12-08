#include "util.h"

const int DELTAS[] = {
	-1, 0,
	1, 0,
	0, -1,
	0, 1};

int is_visible(char *data, int width, int height, int x, int y)
{
	char start = data[y * width + x];

	for (int d = 0; d < 4; ++d)
	{
		int px = x, py = y;
		int dx = DELTAS[d * 2 + 0];
		int dy = DELTAS[d * 2 + 1];

		do
		{
			px += dx;
			py += dy;

			// got to edge, visible
			if (px < 0 || py < 0 || px >= width || py >= height)
			{
				return 1;
			}

			char v = data[py * width + px];
			if (v >= start)
			{
				break;
			}
		} while (1);
	}

	return 0;
}

int dir_score(char *data, int width, int height, int x, int y, int d)
{
	int dx = DELTAS[d * 2 + 0];
	int dy = DELTAS[d * 2 + 1];
	int px = x + dx, py = y + dy;
	int score = 0;
	int v = data[y * width + x];

	while (px >= 0 && py >= 0 && px < width && py < height)
	{
		score++;
		if (data[py * width + px] >= v)
		{
			break;
		}
		px += dx;
		py += dy;
	}
	return score;
}

int tree_score(char *data, int width, int height, int x, int y)
{
	int score = 1;
	for (int d = 0; d < 4; ++d)
	{
		score *= dir_score(data, width, height, x, y, d);
	}
	return score;
}

int main(int argc, char *argv[])
{
	char *text;
	ptrdiff_t len = read_file_to_buffer("day8_input.txt", &text);

	const char *delim = "\r\n";

	char *copy = (char *)malloc(len);
	memcpy(copy, text, len);

	char *line = strtok(copy, delim);

	int width = 0, height = 0;

	while (line && *line > 0)
	{
		if (width == 0)
			width = strlen(line);
		height++;
		line = strtok(NULL, delim);
	}

	free(copy);

	char *data = (char *)malloc(width * height);

	int y = 0;
	line = strtok(text, delim);
	while (line && *line > 0)
	{
		for (int x = 0; x < width; ++x)
		{
			data[y * width + x] = line[x];
		}
		y++;
		line = strtok(NULL, delim);
	}

	int sum = 0;
	int best_score = -1;
	int best_x = -1, best_y = -1;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			sum += is_visible(data, width, height, x, y);

			int score = tree_score(data, width, height, x, y);
			if (score > best_score)
			{
				best_score = score;
				best_x = x;
				best_y = y;
			}
		}
	}

	printf("Visible Trees: %d\n%c %c\n", sum, data[99], data[100]);
	printf("Highest Scenic Score: (%d, %d) -> %d\n", best_x, best_y, best_score);

	free(data);
	free(text);

	return 0;
}
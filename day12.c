#include "util.h"

#if 1
enum
{
	map_width = 93,
	map_height = 41,
};

const char *map = "abacccaaaacccccccccccaaaaaacccccaaaaaaccccaaacccccccccccccccccccccccccccccccccccccccccccaaaaa"
				  "abaaccaaaacccccccccccaaaaaaccccccaaaaaaaaaaaaaccccccccccccccccccccccccccccccccccccccccccaaaaa"
				  "abaaccaaaacccccccccccaaaaacccccaaaaaaaaaaaaaaaccccccccccccccccccccccccccccccccccccccccccaaaaa"
				  "abccccccccccccccccccccaaaaacccaaaaaaaaaaaaaaaacccccccccccccccccccccccccccaaaccccccccccccaaaaa"
				  "abccccccccccccccccccccaacaacccaaaaaaaaccaaaaaccccccccccccccccccccccccccccaaaccccccccccccaccaa"
				  "abcccccccccccccaacccaaaccccccaaaaaaaaaccaaaaaccccccccccccccccccccccccccccccacccccccccccccccca"
				  "abcccccccccccaaaaaaccaaaccacccccaaaaaaacccccccccccccccccccccccccciiiicccccccddddddccccccccccc"
				  "abcccccccccccaaaaaaccaaaaaaaccccaaaaaacccccaacccccccaaaccccccccciiiiiiiicccdddddddddacaaccccc"
				  "abccccccccccccaaaaaaaaaaaaacccccaaaaaaacaaaacccccccaaaacccccccchhiiiiiiiiicddddddddddaaaccccc"
				  "abcccccccccccaaaaaaaaaaaaaacccccccaaacccaaaaaacccccaaaaccccccchhhipppppiiiijjjjjjjddddaaccccc"
				  "abcccccccccccaaaaaaaaaaaaaaccccccccccccccaaaaaccccccaaaccccccchhhpppppppiijjjjjjjjjddeeaccccc"
				  "abcccccccccccccccccaaaaaaaacccccccccccccaaaaaccccccccccccccccchhppppppppppjjqqqjjjjjeeeaacccc"
				  "abccccccccccccccccccaaaaaaaacccccccccccccccaacccccccccccccccchhhpppuuuupppqqqqqqqjjjeeeaacccc"
				  "abcccccccccccccccccccaacccacccccccccccccccccccccccccccccccccchhhopuuuuuuppqqqqqqqjjjeeecccccc"
				  "abacccccccccccccaaacaaaccccccccccccccccccccccccccccaaccccccchhhhoouuuuuuuqvvvvvqqqjkeeecccccc"
				  "abaccccccccccccaaaaaacccccaaccccccccccccccccccccccaaaccccccchhhooouuuxxxuvvvvvvqqqkkeeecccccc"
				  "abaccccccccccccaaaaaacccaaaaaaccccccccccccccccccaaaaaaaaccchhhhooouuxxxxuvyyyvvqqqkkeeecccccc"
				  "abcccccccccccccaaaaacccaaaaaaaccccccccccccccccccaaaaaaaaccjjhooooouuxxxxyyyyyvvqqqkkeeecccccc"
				  "abccccccccccccccaaaaaacaaaaaaaccccccccaaaccccccccaaaaaaccjjjooootuuuxxxxyyyyyvvqqkkkeeecccccc"
				  "abccccccccccccccaaaaaaaaaaaaacccccccccaaaacccccccaaaaaacjjjooootttuxxxxxyyyyvvrrrkkkeeecccccc"
				  "SbccccccccccccccccccaaaaaaaaacccccccccaaaacccccccaaaaaacjjjoootttxxxEzzzzyyvvvrrrkkkfffcccccc"
				  "abcccccccccccaaacccccaaaaaaacaaaccccccaaaccccccccaaccaacjjjoootttxxxxxyyyyyyvvvrrkkkfffcccccc"
				  "abcccccccccaaaaaacccaaaaaacccaaacacccaacccccccccccccccccjjjoootttxxxxyxyyyyyywvvrrkkkfffccccc"
				  "abcccccccccaaaaaacccaaaaaaaaaaaaaaaccaaacaaacccccaacccccjjjnnnttttxxxxyyyyyyywwwrrkkkfffccccc"
				  "abcaacacccccaaaaacccaaacaaaaaaaaaaaccaaaaaaacccccaacaaacjjjnnnntttttxxyywwwwwwwwrrrlkfffccccc"
				  "abcaaaaccccaaaaacccccccccaacaaaaaaccccaaaaaacccccaaaaacccjjjnnnnnttttwwywwwwwwwrrrrllfffccccc"
				  "abaaaaaccccaaaaaccccccaaaaaccaaaaacaaaaaaaaccccaaaaaaccccjjjjinnnntttwwwwwsssrrrrrllllffccccc"
				  "abaaaaaaccccccccccccccaaaaacaaaaaacaaaaaaaaacccaaaaaaacccciiiiinnnntswwwwssssrrrrrlllfffccccc"
				  "abacaaaaccccccccccccccaaaaaacaaccccaaaaaaaaaaccccaaaaaaccccciiiinnnssswwsssssllllllllfffccccc"
				  "abccaaccccccccccccccccaaaaaaccccccccccaaacaaaccccaaccaacccccciiiinnsssssssmmllllllllfffaacccc"
				  "abccccccccccccccccccccaaaaaaccccccccccaaaccccccccaaccccccccccciiinnmsssssmmmmlllllgggffaacccc"
				  "abcccccccccccccccaccccccaaacccccccccccaaccccccccccccccccccccccciiimmmsssmmmmmgggggggggaaacccc"
				  "abcccccccccaaaaaaaaccccccccccccccccccccccccccccaaaaaccccccccccciiimmmmmmmmmgggggggggaaacccccc"
				  "abccccccccccaaaaaaccccccccccccccccccaacccccccccaaaaacccccccccccciiimmmmmmmhhggggcaaaaaaaccccc"
				  "abccccccccccaaaaaacccccccccccccccccaacccccccccaaaaaacccccccccccciihhmmmmhhhhgccccccccaacccccc"
				  "abccccaacaaaaaaaaaaccccccccccccccccaaaccccccccaaaaaaccccccccccccchhhhhhhhhhhaaccccccccccccccc"
				  "abccccaaaaaaaaaaaaaaccccccccccaaccaaaaccccccccaaaaaacccaaacccccccchhhhhhhhaaaaccccccccccccccc"
				  "abcccaaaaaaaaaaaaaaaccccccccaaaaaacaaaacacaccccaaaccccaaaacccccccccchhhhccccaaccccccccccaaaca"
				  "abcccaaaaaacacaaacccccccccccaaaaaaaaaaaaaaacccccccccccaaaacccccccccccaaaccccccccccccccccaaaaa"
				  "abcccccaaaacccaaaccccccccccaaaaaaaaaaaaaaaaccccccccccccaaacccccccccccaaacccccccccccccccccaaaa"
				  "abcccccaacccccaacccccccccccaaaaaaaaaaaaaccccccccccccccccccccccccccccccccccccccccccccccccaaaaa";
#else
enum
{
	map_width = 8,
	map_height = 5,
};

const char *map = "Sabqponm"
				  "abcryxxl"
				  "accszExk"
				  "acctuvwj"
				  "abdefghi";
#endif

struct point
{
	int x, y;
};

int valid_point(struct point p)
{
	return p.x >= 0 && p.y >= 0 && p.x < map_width && p.y < map_height;
}

char get_z(struct point p)
{
	if (!valid_point(p))
	{
		return '\0';
	}

	char raw = map[p.x + p.y * map_width];
	if (raw == 'S')
		return 'a';
	else if (raw == 'E')
		return 'z';
	return raw;
}

int can_move(struct point from, struct point to)
{
	int z1 = get_z(from);
	int z2 = get_z(to);

	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	return ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) && (z2 - z1 <= 1);
}

int dist(struct point a, struct point b)
{
	return abs(b.x - a.x) + abs(b.y - a.y);
}

int contains(struct point *p, int x, int y)
{
	for (int i = 0; i < arrlen(p); ++i)
	{
		if (p[i].x == x && p[i].y == y)
		{
			return 1;
		}
	}
	return 0;
}

struct node
{
	struct node *parent;
	struct point p;
	int g, h;
};

struct node *node_pool = NULL;
struct node **open_list = NULL;
struct node **closed_list = NULL;
struct point start, end;

void print_map_w_lists(struct node **open_list, struct node **closed_list);

struct node *make_node(struct node *parent, struct point p, int g, int h)
{
	if (node_pool == NULL)
		arrsetcap(node_pool, 16384);

	arrput(node_pool, ((struct node){
						  .parent = parent,
						  .p = p,
						  .g = g,
						  .h = h,
					  }));

	struct node *new_node = &node_pool[arrlen(node_pool) - 1];
	// printf("new node: [%d,%d]\n", p.x, p.y);

	return new_node;
}

int node_f(struct node *node) { return node->g + node->h; }

int indexof_node(struct node **list, const struct node *node)
{
	for (int i = 0; i < arrlen(list); ++i)
	{
		if (list[i]->p.x == node->p.x && list[i]->p.y == node->p.y)
		{
			return i;
		}
	}

	return -1;
}

void add_to_open(struct node *node)
{
	if (indexof_node(open_list, node) >= 0 || indexof_node(closed_list, node) >= 0)
	{
		return;
	}
	arrput(open_list, node);
}

void add_to_closed(struct node *node)
{
	if (indexof_node(closed_list, node) >= 0)
	{
		return;
	}

	int i = indexof_node(open_list, node);
	if (i >= 0)
	{
		arrdel(open_list, i);
	}
	arrput(closed_list, node);
}

void print_lists()
{
	printf("open: ");
	for (int i = 0, len = arrlen(open_list); i < len; ++i)
		printf("[%d,%d] ", open_list[i]->p.x, open_list[i]->p.y);
	printf("\nclosed: ");
	for (int i = 0, len = arrlen(closed_list); i < len; ++i)
		printf("[%d,%d] ", closed_list[i]->p.x, closed_list[i]->p.y);
	printf("\n");
}

struct node *process_node(struct node *node)
{
	if (node->p.x == end.x && node->p.y == end.y)
		return node;

	print_lists();

	add_to_closed(node);

	const struct point dirs[4] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	};

	for (int d = 0; d < 4; ++d)
	{
		struct point dir = dirs[d];
		struct point test = node->p;
		test.x += dir.x;
		test.y += dir.y;

		if (valid_point(test) && can_move(node->p, test))
		{
			int d = dist(test, end);
			struct node *new_node = make_node(node, test, node->g + 1, dist(test, end));

			add_to_open(new_node);
		}
	}

	// find adjacent nodes in the open list
	struct node **adjacent = NULL;
	arrsetcap(adjacent, 4);
	for (int i = 0; i < arrlen(open_list); ++i)
	{
		struct node *adj = open_list[i];
		int dx = abs(adj->p.x - node->p.x);
		int dy = abs(adj->p.y - node->p.y);
		if ((dx == 0 && dy == 1) || (dx == 1 && dy == 0))
		{
			arrput(adjacent, adj);
		}
	}

	for (int i = 0; i < arrlen(adjacent); ++i)
	{
		struct node *adj = adjacent[i];
		if (adj->g < node->g)
		{
			adj->parent = node;
			adj->g = node->g + 1;
		}
	}

	if (arrlen(open_list) == 0)
		return NULL;

	int min_f = 9999999;
	struct node *min_f_node = NULL;
	for (int i = 0, len = arrlen(open_list); i < len; ++i)
	{
		struct node *open = open_list[i];
		if (node_f(open) < min_f)
		{
			min_f = node_f(open);
			min_f_node = open;
		}
	}

	// print_map_w_lists(open_list, closed_list);
	return process_node(min_f_node);
}

struct point *get_path()
{
	arrsetlen(open_list, 0);
	arrsetlen(closed_list, 0);
	arrsetlen(node_pool, 0);

	struct node *start_node = make_node(NULL, start, 0, 0);
	add_to_open(start_node);
	struct node *final_node = process_node(start_node);

	struct point *path = NULL;
	arrsetcap(path, 128);

	struct node *slider = final_node;
	while (slider)
	{
		arrput(path, slider->p);
		slider = slider->parent;
	}

	if (arrlen(path) == 0)
	{
		arrfree(path);
		return NULL;
	}

	return path;
}

int list_contains(struct node **list, int x, int y)
{
	for (int i = 0; i < arrlen(list); ++i)
	{
		if (list[i]->p.x == x && list[i]->p.y == y)
		{
			return 1;
		}
	}
	return 0;
}

void print_map_w_lists(struct node **open_list, struct node **closed_list)
{
	for (int y = 0; y < map_height; ++y)
	{
		for (int x = 0; x < map_width; ++x)
		{
			if (x == start.x && y == start.y)
			{
				printf("S");
			}
			else if (x == end.x && y == end.y)
			{
				printf("E");
			}
			else if (open_list && list_contains(open_list, x, y))
			{
				printf(".");
			}
			else if (closed_list && list_contains(closed_list, x, y))
			{
				printf("#");
			}
			else
			{
				printf("%c", map[x + y * map_width]);
			}
		}
		printf("\n");
	}
}

void print_map(struct point *path)
{
	for (int y = 0; y < map_height; ++y)
	{
		for (int x = 0; x < map_width; ++x)
		{
			if (x == start.x && y == start.y)
			{
				printf("S");
			}
			else if (x == end.x && y == end.y)
			{
				printf("E");
			}
			else if (path && contains(path, x, y))
			{
				printf(".");
			}
			else
			{
				printf("%c", map[x + y * map_width]);
			}
		}
		printf("\n");
	}
}

int main(void)
{
	const char *c = map;
	while (*c)
	{
		int i = c - map;
		if (*c == 'S')
		{
			start.x = i % map_width;
			start.y = i / map_width;
		}
		else if (*c == 'E')
		{
			end.x = i % map_width;
			end.y = i / map_width;
		}
		c++;
	}

	// part 1
	{
		// struct point *path = search(start, end);
		struct point *path = get_path();

		printf("Best path so far is %d steps long.\n", arrlen(path) - 1);

		arrfree(path);
	}

	// part 2
	if (false)
	{
		int min_len = 9999999;
		struct point min_len_start;
		for (int y = 0; y < map_height; ++y)
		{
			for (int x = 0; x < map_width; ++x)
			{
				start = (struct point){x, y};
				if (get_z(start) == 'a')
				{
					struct point *path = get_path();

					if (path)
					{
						int len = arrlen(path) - 1;
						if (len < min_len)
						{
							min_len = len;
							min_len_start = start;
						}
						arrfree(path);
					}
				}
			}
		}

		printf("Min start path starts at [%d,%d] and is %d steps long\n", min_len_start.x, min_len_start.y, min_len);
	}

	return 0;
}
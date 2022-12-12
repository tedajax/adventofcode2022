#include "util.h"

#if 1
enum
{
    map_width = 93,
    map_height = 41,
};

const char *map =
    "abacccaaaacccccccccccaaaaaacccccaaaaaaccccaaacccccccccccccccccccccccccccccccccccccccccccaaaaa"
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

int
valid_point(struct point p)
{
    return p.x >= 0 && p.y >= 0 && p.x < map_width && p.y < map_height;
}

int
get_id(int x, int y)
{
    if (valid_point((struct point){x, y}))
        return x + y * map_width;
    else
        return -1;
}

char
get_z(struct point p)
{
    if (!valid_point(p)) {
        return '\0';
    }

    char raw = map[p.x + p.y * map_width];
    if (raw == 'S')
        return 'a';
    else if (raw == 'E')
        return 'z';
    return raw;
}

int
can_move(struct point from, struct point to)
{
    int z1 = get_z(from);
    int z2 = get_z(to);

    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);
    return ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) && (z2 - z1 <= 1);
}

int
dist(struct point a, struct point b)
{
    return abs(b.x - a.x) + abs(b.y - a.y);
}

int
contains(struct point *p, int x, int y)
{
    for (int i = 0; i < arrlen(p); ++i) {
        if (p[i].x == x && p[i].y == y) {
            return 1;
        }
    }
    return 0;
}

struct node
{
    struct node *parent;
    struct point p;
    int g;
};

struct node *node_pool = NULL;
struct node **open_list = NULL;
struct node **closed_list = NULL;
bool in_open_list[map_width * map_height] = {0};
bool in_closed_list[map_width * map_height] = {0};
struct point start, end;

struct node *
make_node(struct node *parent, struct point p, int g, int h)
{
    if (node_pool == NULL) arrsetcap(node_pool, 16384);

    arrput(
        node_pool,
        ((struct node){
            .parent = parent,
            .p = p,
            .g = g,
        }));

    struct node *new_node = &node_pool[arrlen(node_pool) - 1];
    // printf("new node: [%d,%d]\n", p.x, p.y);

    return new_node;
}

int
indexof_node(struct node **list, const struct node *node)
{
    for (int i = 0; i < arrlen(list); ++i) {
        if (list[i]->p.x == node->p.x && list[i]->p.y == node->p.y) {
            return i;
        }
    }

    return -1;
}

void
add_to_open(struct node *node)
{
    int id = get_id(node->p.x, node->p.y);
    if (in_open_list[id] || in_closed_list[id]) {
        return;
    }
    in_open_list[id] = true;
    arrput(open_list, node);
}

void
add_to_closed(struct node *node)
{
    int id = get_id(node->p.x, node->p.y);
    if (in_closed_list[id]) {
        return;
    }

    int i = indexof_node(open_list, node);
    arrdel(open_list, i);
    in_open_list[id] = false;
    in_closed_list[id] = true;
    arrput(closed_list, node);
}

struct node *
process_node(struct node *node)
{
    if (node->p.x == end.x && node->p.y == end.y) return node;

    add_to_closed(node);

    const struct point dirs[4] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
    };

    for (int d = 0; d < 4; ++d) {
        struct point dir = dirs[d];
        struct point test = node->p;
        test.x += dir.x;
        test.y += dir.y;

        if (valid_point(test) && can_move(node->p, test)) {
            int d = dist(test, end);
            struct node *new_node = make_node(node, test, node->g + 1, dist(test, end));

            add_to_open(new_node);
        }
    }

    // find adjacent nodes in the open list
    for (int i = 0, len = arrlen(open_list); i < len; ++i) {
        struct node *adj = open_list[i];
        int id = get_id(adj->p.x, adj->p.y);
        if (id == get_id(node->p.x - 1, node->p.y) || id == get_id(node->p.x + 1, node->p.y)
            || id == get_id(node->p.x, node->p.y - 1) || id == get_id(node->p.x, node->p.y + 1))
        {
            if (adj->g < node->g) {
                adj->parent = node;
                adj->g = node->g + 1;
            }
            break;
        }
    }

    if (arrlen(open_list) == 0) return NULL;

    int min_g = 9999999;
    struct node *min_node = NULL;
    for (int i = 0, len = arrlen(open_list); i < len; ++i) {
        struct node *open = open_list[i];
        if (open->g < min_g) {
            min_g = open->g;
            min_node = open;
        }
    }

    return process_node(min_node);
}

int
get_path_len()
{
    arrsetlen(open_list, 0);
    arrsetlen(closed_list, 0);
    arrsetlen(node_pool, 0);
    memset(in_open_list, 0, sizeof(in_open_list));
    memset(in_closed_list, 0, sizeof(in_closed_list));

    struct node *start_node = make_node(NULL, start, 0, 0);
    add_to_open(start_node);
    struct node *final_node = process_node(start_node);

    struct point *path = NULL;
    arrsetcap(path, 128);

    struct node *slider = final_node;
    int len = 0;
    while (slider) {
        arrput(path, slider->p);
        slider = slider->parent;
        len++;
    }
    return len - 1;
}

int
main(void)
{
    const char *c = map;
    while (*c) {
        int i = c - map;
        if (*c == 'S') {
            start.x = i % map_width;
            start.y = i / map_width;
        } else if (*c == 'E') {
            end.x = i % map_width;
            end.y = i / map_width;
        }
        c++;
    }

    // part 1
    {
        int len = get_path_len();
        printf("Best path so far is %d steps long.\n", len);
    }

    // part 2
    {
        int min_len = 9999999;
        struct point min_len_start;
        for (int y = 0; y < map_height; ++y) {
            for (int x = 0; x < map_width; ++x) {
                start = (struct point){x, y};
                if (get_z(start) == 'a') {
                    int len = get_path_len();

                    if (len > 0 && len < min_len) {
                        min_len = len;
                        min_len_start = start;
                    }
                }
            }
        }

        printf(
            "Min start path starts at [%d,%d] and is %d steps long\n",
            min_len_start.x,
            min_len_start.y,
            min_len);
    }

    return 0;
}
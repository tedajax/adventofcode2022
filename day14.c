#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

uint32_t
point_hash(int x, int y)
{
    uint32_t px = (uint32_t)x;
    uint32_t py = (uint32_t)y;
    return ((px & 0xFFFF) << 16) | (py & 0xFFFF);
}

struct cell
{
    uint32_t key;
    char value;
};

struct map
{
    struct cell* cells;
    int bounds[4];
};

int drop_sand(struct map* map, int x, int y);
struct map parse_map(const char* input_string);
void print_map(struct map* map);

int
main(void)
{
#if 0
    const char* input_string = "498,4 -> 498,6 -> 496,6\n"
                               "503,4 -> 502,4 -> 502,9 -> 494,9\n";
#else
    FILE* fp = fopen("day14_input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long file_len = ftell(fp);
    rewind(fp);
    char* input_string = (char*)calloc(file_len + 1, 1);
    fread(input_string, 1, file_len, fp);
    fclose(fp);
#endif

    struct map map = parse_map(input_string);

    print_map(&map);

    int sum = 0;
    while (drop_sand(&map, 500, 0)) {
        // print_map(&map);
        sum++;
    }

    print_map(&map);
    printf("Part 1: %d\n", sum);

    return 0;
}

// returns 1 if stopped, 0 if infinite
int
drop_sand(struct map* map, int x, int y)
{
    int sx = x, sy = y;

    if (hmget(map->cells, point_hash(sx, sy))) return 0;

    while (1) {
        uint32_t down_id = point_hash(sx, sy + 1), downleft_id = point_hash(sx - 1, sy + 1),
                 downright_id = point_hash(sx + 1, sy + 1);
        if (!hmget(map->cells, down_id)) {
            sy++;
        } else if (!hmget(map->cells, downleft_id)) {
            sx--;
            sy++;
        } else if (!hmget(map->cells, downright_id)) {
            sx++;
            sy++;
        } else {
            break;
        }

        if (sy > map->bounds[3]) return 0;
    }

    hmput(map->cells, point_hash(sx, sy), 'o');

    return 1;
}

struct map
parse_map(const char* input_string)
{
    struct map map = {0};

    hmdefault(map.cells, '\0');

    memcpy(map.bounds, (int[4]){INT_MAX, INT_MIN, INT_MAX, INT_MIN}, sizeof(map.bounds));

    const char* curr = input_string;
    int lx = -1, ly = -1;
    int x, y;
    while (curr && *curr > 0 && sscanf(curr, "%d,%d -> ", &x, &y) == 2) {
        if (x < map.bounds[0]) map.bounds[0] = x;
        if (x > map.bounds[1]) map.bounds[1] = x;
        if (y < map.bounds[2]) map.bounds[2] = y;
        if (y > map.bounds[3]) map.bounds[3] = y;

        if (lx >= 0) {
            if (x == lx) {
                int sy = min(y, ly);
                int ey = max(y, ly);
                for (int yy = sy; yy <= ey; ++yy) {
                    hmput(map.cells, point_hash(x, yy), '#');
                }
            } else if (y == ly) {
                int sx = min(x, lx);
                int ex = max(x, lx);
                for (int xx = sx; xx <= ex; ++xx) {
                    hmput(map.cells, point_hash(xx, y), '#');
                }
            }
        }
        lx = x;
        ly = y;

        char* n1 = strstr(curr, " -> ");
        char* n2 = strstr(curr, "\n");

        if (n1 && n1 < n2) {
            curr = n1 + 4;
        } else if (n2) {
            lx = -1;
            ly = -1;
            curr = n2 + 1;
        } else
            break;
    }

    map.bounds[2] = -1;
    map.bounds[3] += 2;
    map.bounds[0] -= 5;
    map.bounds[1] += 5;

    for (int x = -4000; x < 6000; ++x) {
        hmput(map.cells, point_hash(x, map.bounds[3]), '#');
    }

    return map;
}

void
print_map(struct map* map)
{
    for (int y = map->bounds[2]; y <= map->bounds[3]; ++y) {
        for (int x = map->bounds[0]; x <= map->bounds[1]; ++x) {
            char c = hmget(map->cells, point_hash(x, y));
            printf("%c", (c) ? c : ' ');
        }
        printf("\n");
    }
}

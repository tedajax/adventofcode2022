#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#if 0
const char* input_string = "2,2,2\n"
                           "1,2,2\n"
                           "3,2,2\n"
                           "2,1,2\n"
                           "2,3,2\n"
                           "2,2,1\n"
                           "2,2,3\n"
                           "2,2,4\n"
                           "2,2,6\n"
                           "1,2,5\n"
                           "3,2,5\n"
                           "2,1,5\n"
                           "2,3,5\n";
#else
#include "day18.inl"
#endif

typedef uint32_t hash;
hash
hash_point(int p[3])
{
    return ((p[0] & 0xFF) << 16) | ((p[1] & 0xFF) << 8) | p[2];
}

void
get_point(hash h, int p[3])
{
    p[0] = h >> 16;
    p[1] = (h >> 8) & 0xFF;
    p[2] = h & 0xFF;
}

struct point_map
{
    hash key;
    int value;
};

struct point_map* map = NULL;
struct point_map* voids = NULL;

int
check_point(int x, int y, int z)
{
    int p[3] = {x, y, z};
    hash k = hash_point(p);
    return hmget(map, k);
}

int
open_no_void(int x, int y, int z)
{
    int p[3] = {x, y, z};
    hash k = hash_point(p);
    return !hmget(map, k) && !hmget(voids, k);
}

int
main(void)
{
    const char* curr = input_string;
    int minpos[3] = {INT_MAX, INT_MAX, INT_MAX}, maxpos[3] = {INT_MIN, INT_MIN, INT_MIN};
    int pos[3] = {0};
    while (*curr > 0 && sscanf(curr, "%d, %d, %d\n", pos, pos + 1, pos + 2) == 3) {
        hash h = hash_point(pos);
        hmput(map, h, 1);
        curr = strstr(curr, "\n") + 1;

        for (int i = 0; i < 3; ++i) {
            if (pos[i] < minpos[i]) minpos[i] = pos[i];
            if (pos[i] > maxpos[i]) maxpos[i] = pos[i];
        }
    }

    printf(
        "minpos: %d, %d, %d\nmaxpos: %d, %d, %d\n",
        minpos[0],
        minpos[1],
        minpos[2],
        maxpos[0],
        maxpos[1],
        maxpos[2]);

    int deltas[18] = {1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1};

    for (int x = minpos[0]; x <= maxpos[0]; x++) {
        for (int y = minpos[1]; y <= maxpos[1]; y++) {
            for (int z = minpos[2]; z <= maxpos[2]; z++) {
                if (!check_point(x, y, z)) {
                    int hit = 0;
                    for (int d = 0; d < 6; ++d) {
                        int dx = deltas[d * 3];
                        int dy = deltas[d * 3 + 1];
                        int dz = deltas[d * 3 + 2];

                        int cx = x, cy = y, cz = z;
                        while (cx >= minpos[0] && cx <= maxpos[0] && cy >= minpos[1]
                               && cy <= maxpos[1] && cz >= minpos[2] && cz <= maxpos[2])
                        {
                            cx += dx;
                            cy += dy;
                            cz += dz;

                            if (check_point(cx, cy, cz)) {
                                hit++;
                                break;
                            }
                        }
                    }

                    if (hit == 6) {
                        int p[3] = {x, y, z};
                        hmput(voids, hash_point(p), 1);
                    }
                }
            }
        }
    }

    for (int pz = minpos[2]; pz <= maxpos[2]; ++pz) {
        printf("Z: %d\n", pz);
        for (int py = minpos[1]; py <= maxpos[1]; ++py) {
            for (int px = minpos[0]; px <= maxpos[0]; ++px) {
                int p[3] = {px, py, pz};
                if (check_point(px, py, pz)) {
                    printf("#");
                } else {
                    hash h = hash_point(p);
                    if (hmget(voids, h)) {
                        printf("v");
                    } else {
                        printf(".");
                    }
                }
            }
            printf("\n");
        }
        printf("\n\n");
    }

    printf("Num void zones: %d\n", hmlen(voids));

    int sum = 0;
    int sum2 = 0;

    for (int i = 0, len = hmlen(map); i < len; ++i) {
        int pos[3];
        get_point(map[i].key, pos);

        int open = 0;
        if (!check_point(pos[0] + 1, pos[1], pos[2])) open++;
        if (!check_point(pos[0] - 1, pos[1], pos[2])) open++;
        if (!check_point(pos[0], pos[1] + 1, pos[2])) open++;
        if (!check_point(pos[0], pos[1] - 1, pos[2])) open++;
        if (!check_point(pos[0], pos[1], pos[2] + 1)) open++;
        if (!check_point(pos[0], pos[1], pos[2] - 1)) open++;
        sum += open;

        int open2 = 0;
        if (open_no_void(pos[0] + 1, pos[1], pos[2])) open2++;
        if (open_no_void(pos[0] - 1, pos[1], pos[2])) open2++;
        if (open_no_void(pos[0], pos[1] + 1, pos[2])) open2++;
        if (open_no_void(pos[0], pos[1] - 1, pos[2])) open2++;
        if (open_no_void(pos[0], pos[1], pos[2] + 1)) open2++;
        if (open_no_void(pos[0], pos[1], pos[2] - 1)) open2++;
        sum2 += open2;
    }

    printf("part 1: %d\n", sum);
    printf("part 2: %d\n", sum2);

    return 0;
}
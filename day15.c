#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define SOKOL_IMPL
#include "sokol_time.h"

struct sensor
{
    int id;
    int x, y;
    int r;
};

struct beacon_entry
{
    uint64_t key;
    int value;
};

int find_obj_id(int* objs, int x, int y);
int find_covers(int* sensors, int* radii, int x, int y);

int
man_dist(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

int
sensor_covers(int* sensors, int* radii, int id, int x, int y)
{
    int sx = sensors[id * 2];
    int sy = sensors[id * 2 + 1];
    int r = radii[id];
    return (man_dist(sx, sy, x, y) <= r);
}

int
sensor_overlap(struct sensor* sensors, int sensor_count, int x, int y)
{
    for (int i = 0; i < sensor_count; ++i) {
        struct sensor* s = sensors + i;
        if (man_dist(s->x, s->y, x, y) <= s->r) return s->id;
    }
    return -1;
}

int
soverlap(struct sensor* sensors, int sensor_count, int x, int y)
{
    for (int i = 0; i < sensor_count; ++i) {
        struct sensor* s = sensors + i;
        if (man_dist(x, y, s->x, s->y) <= s->r) {
            return s->id;
        }
    }

    return -1;
}

int
soverlap_chunk(struct sensor* sensors, int sensor_count, int cx, int cy, int csize)
{
    for (int i = 0; i < sensor_count; ++i) {
        struct sensor* s = sensors + i;
        int hrad = s->r / 2;
        int hl = s->x - hrad;
        int hr = s->x + hrad;
        int ht = s->y - hrad;
        int hb = s->y + hrad;

        int cl = cx, cr = cx + csize - 1, ct = cy, cb = cy + csize - 1;
        if (cl >= hl && cr <= hr && ct >= ht && cb <= hb) {
            return s->id;
        }
    }

    return -1;
}

void print_map(
    int* sensors,
    int* beacons,
    int* radii,
    int view_x,
    int view_y,
    int view_w,
    int view_h,
    int highlight_id);

uint64_t
beacon_hash(int bx, int by)
{
    uint64_t hi = ((uint64_t)bx) << 32;
    uint64_t lo = (uint64_t)by;
    return hi | lo;
}

int
sensors_in_aabb(
    struct sensor* sensors,
    int left,
    int right,
    int top,
    int bottom,
    struct sensor* buffer)
{
    int count = 0;
    for (int i = 0, len = arrlen(sensors); i < len; ++i) {
        struct sensor* s = sensors + i;

        int sl = s->x - s->r;
        int sr = s->x + s->r;
        int st = s->y - s->r;
        int sb = s->y + s->r;

        if (left <= sr && right >= sl && top <= sb && bottom >= st) {
            buffer[count++] = *s;
        }
    }
    return count;
}

int
main(void)
{
    stm_setup();

#if 0
    const char* input_string = "Sensor at x=2, y=18: closest beacon is at x=-2, y=15\n"
                               "Sensor at x=9, y=16: closest beacon is at x=10, y=16\n"
                               "Sensor at x=13, y=2: closest beacon is at x=15, y=3\n"
                               "Sensor at x=12, y=14: closest beacon is at x=10, y=16\n"
                               "Sensor at x=10, y=20: closest beacon is at x=10, y=16\n"
                               "Sensor at x=14, y=17: closest beacon is at x=10, y=16\n"
                               "Sensor at x=8, y=7: closest beacon is at x=2, y=10\n"
                               "Sensor at x=2, y=0: closest beacon is at x=2, y=10\n"
                               "Sensor at x=0, y=11: closest beacon is at x=2, y=10\n"
                               "Sensor at x=20, y=14: closest beacon is at x=25, y=17\n"
                               "Sensor at x=17, y=20: closest beacon is at x=21, y=22\n"
                               "Sensor at x=16, y=7: closest beacon is at x=15, y=3\n"
                               "Sensor at x=14, y=3: closest beacon is at x=15, y=3\n"
                               "Sensor at x=20, y=1: closest beacon is at x=15, y=3\n";
    const int search_row = 10;
    const int search_size = 20;
#else
    const char* input_string =
        "Sensor at x=1259754, y=1927417: closest beacon is at x=1174860, y=2000000\n"
        "Sensor at x=698360, y=2921616: closest beacon is at x=1174860, y=2000000\n"
        "Sensor at x=2800141, y=2204995: closest beacon is at x=3151616, y=2593677\n"
        "Sensor at x=3257632, y=2621890: closest beacon is at x=3336432, y=2638865\n"
        "Sensor at x=3162013, y=3094407: closest beacon is at x=3151616, y=2593677\n"
        "Sensor at x=748228, y=577603: closest beacon is at x=849414, y=-938539\n"
        "Sensor at x=3624150, y=2952930: closest beacon is at x=3336432, y=2638865\n"
        "Sensor at x=2961687, y=2430611: closest beacon is at x=3151616, y=2593677\n"
        "Sensor at x=142293, y=3387807: closest beacon is at x=45169, y=4226343\n"
        "Sensor at x=3309479, y=1598941: closest beacon is at x=3336432, y=2638865\n"
        "Sensor at x=1978235, y=3427616: closest beacon is at x=2381454, y=3683743\n"
        "Sensor at x=23389, y=1732536: closest beacon is at x=1174860, y=2000000\n"
        "Sensor at x=1223696, y=3954547: closest beacon is at x=2381454, y=3683743\n"
        "Sensor at x=3827517, y=3561118: closest beacon is at x=4094575, y=3915146\n"
        "Sensor at x=3027894, y=3644321: closest beacon is at x=2381454, y=3683743\n"
        "Sensor at x=3523333, y=3939956: closest beacon is at x=4094575, y=3915146\n"
        "Sensor at x=2661743, y=3988507: closest beacon is at x=2381454, y=3683743\n"
        "Sensor at x=2352285, y=2877820: closest beacon is at x=2381454, y=3683743\n"
        "Sensor at x=3214853, y=2572272: closest beacon is at x=3151616, y=2593677\n"
        "Sensor at x=3956852, y=2504216: closest beacon is at x=3336432, y=2638865\n"
        "Sensor at x=219724, y=3957089: closest beacon is at x=45169, y=4226343\n"
        "Sensor at x=1258233, y=2697879: closest beacon is at x=1174860, y=2000000\n"
        "Sensor at x=3091374, y=215069: closest beacon is at x=4240570, y=610698\n"
        "Sensor at x=3861053, y=889064: closest beacon is at x=4240570, y=610698\n"
        "Sensor at x=2085035, y=1733247: closest beacon is at x=1174860, y=2000000\n";
    const int search_row = 2000000;
    const int search_size = 4000000;
#endif

    struct sensor* sensor_objs = NULL;
    int* sensors = NULL;
    int* beacons = NULL;
    int* radii = NULL;
    struct beacon_entry* beacon_map = NULL;
    hmdefault(beacon_map, -1);

    const char* str = input_string;
    int sx, sy, bx, by;
    int id = 0;
    while (
        sscanf(str, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &sx, &sy, &bx, &by)
        == 4)
    {
        str = strstr(str, "\n") + 1;

        arrput(sensors, sx);
        arrput(sensors, sy);
        arrput(beacons, bx);
        arrput(beacons, by);

        hmput(beacon_map, beacon_hash(bx, by), id);

        int r = man_dist(sx, sy, bx, by);
        arrput(radii, r);
        arrput(
            sensor_objs,
            ((struct sensor){
                .id = id,
                .x = sx,
                .y = sy,
                .r = r,
            }));
        id++;
    }

    // printf("By Top\n-----------\n");
    // for (int i = 0; i < sensor_count; ++i) {
    //     struct sensor* s = sensors_top + i;
    //     printf("%d (%d,%d) - top %d, bot %d\n", s->id, s->x, s->y, s->top, s->bot);
    // }

    // printf("By Bot\n-----------\n");
    // for (int i = 0; i < sensor_count; ++i) {
    //     struct sensor* s = sensors_bot + i;
    //     printf("%d (%d,%d) - top %d, bot %d\n", s->id, s->x, s->y, s->top, s->bot);
    // }

    // printf("Sensors: %d\nBeacons: %d\n", arrlen(sensors) / 2, arrlen(beacons) / 2);

    for (int i = 0, len = arrlen(sensors) / 2; i < len; ++i) {
        printf("Sensor: %d, %d R: %d\n", sensors[i * 2], sensors[i * 2 + 1], radii[i]);
    }

    int highlight = find_obj_id(sensors, 8, 7);
    print_map(sensors, beacons, radii, -5, -5, 30, 30, -1);

    // int sum = 0;
    // int y = search_row;
    // int columns = 20000000;
    // for (int col = 0; col < columns; ++col) {
    //     int x = col - columns / 2;
    //     int find = find_covers(sensors, radii, x, y);
    //     uint64_t bh = beacon_hash(x, y);
    //     int find_bid = hmget(beacon_map, bh);
    //     if (find >= 0 && find_bid < 0) {
    //         sum++;
    //     }
    // }

    uint64_t start_clock = stm_now();
    printf("\n");

    int chunk_size = 10000;
    int chunk_num = search_size / chunk_size;
    chunk_num *= chunk_num;

    int chunk_id = 0;
    int find_x = -1, find_y = -1;
    for (int cy = 334 * chunk_size; cy < search_size; cy += chunk_size) {

        for (int cx = 0; cx < search_size; cx += chunk_size) {
            struct sensor in_chunk[64];
            int chunk_sensor_count = sensors_in_aabb(
                sensor_objs, cx, cx + chunk_size - 1, cy, cy + chunk_size - 1, in_chunk);

            uint64_t diff = stm_diff(stm_now(), start_clock);
            int seconds = (int)stm_sec(diff);
            int hours = seconds / 3600;
            int minutes = seconds / 60;
            seconds = seconds % 60;
            printf(
                "\rC:%d,%d SC:%d -- %d/%d %0.2f%% -- %02dh %02dm %02ds",
                cx / chunk_size,
                cy / chunk_size,
                chunk_sensor_count,
                chunk_id,
                chunk_num,
                (double)chunk_id / chunk_num * 100,
                hours,
                minutes,
                seconds);

            if (soverlap_chunk(in_chunk, chunk_sensor_count, cx, cy, chunk_size) < 0
                && chunk_sensor_count > 0)
            {
                for (int y = cy, ey = min(cy + chunk_size, search_size); y < ey; ++y) {
                    for (int x = cx, ex = min(cx + chunk_size, search_size); x < ex; ++x) {
                        int find = soverlap(in_chunk, chunk_sensor_count, x, y);
                        if (find < 0) {
                            uint64_t bh = beacon_hash(x, y);
                            int find_bid = hmget(beacon_map, bh);
                            if (find_bid < 0) {
                                find_x = x;
                                find_y = y;
                                goto found;
                            }
                        }
                    }
                }
            }

            chunk_id++;
        }
    }

found:

    int64_t fx = (int64_t)find_x;
    int64_t fy = (int64_t)find_y;
    int64_t freq = fx * 4000000 + fy;
    // printf("\nPart 1: %d\n", sum);
    printf("Part2: %d,%d %lld\n", find_x, find_y, freq);

    return 0;
}

int
find_obj_id(int* objs, int x, int y)
{

    for (int id = 0, len = arrlen(objs) / 2; id < len; ++id) {
        if (objs[id * 2] == x && objs[id * 2 + 1] == y) return id;
    }
    return -1;
}

int
find_covers(int* sensors, int* radii, int x, int y)
{
    for (int id = 0, len = arrlen(sensors) / 2; id < len; ++id) {
        if (sensor_covers(sensors, radii, id, x, y)) {
            return id;
        }
    }
    return -1;
}

void
print_map(
    int* sensors,
    int* beacons,
    int* radii,
    int view_x,
    int view_y,
    int view_w,
    int view_h,
    int highlight_id)
{
    for (int y = view_y; y < view_y + view_h; ++y) {

        for (int x = view_x; x < view_x + view_w; ++x) {
            int sensor_id = find_obj_id(sensors, x, y);
            int beacon_id = find_obj_id(beacons, x, y);

            char c = ' ';
            if (sensor_id >= 0) {
                c = 'S';
            } else if (beacon_id >= 0) {
                c = 'B';
            } else if (
                (highlight_id >= 0 && sensor_covers(sensors, radii, highlight_id, x, y))
                || (highlight_id < 0 && find_covers(sensors, radii, x, y) >= 0))
            {
                c = '#';
            }
            printf("%c", c);
        }
        printf("\n");
    }
}
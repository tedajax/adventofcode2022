#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

enum type
{
    type_value,
    type_list
};

struct packet
{
    enum type type;
    union
    {
        int value;
        struct packet* items;
    };
};

const char* parse_packet(const char* input_string, struct packet* packet);
int compare_packets(const struct packet* left, const struct packet* right);
int compare_packet_lists(const struct packet* left, const struct packet* right);

void print_packet(struct packet* item);
char* sprint_packet(char* dst, struct packet* item);

int
cmp_packet(const void* a, const void* b)
{
    return compare_packets((const struct packet*)a, (const struct packet*)b);
}

int
main(int argc, char* argv[])
{
// Example input
#if 0
    const char* input_string = "[1,1,3,1,1]\n"
                               "[1,1,5,1,1]\n"
                               "\n"
                               "[[1],[2,3,4]]\n"
                               "[[1],4]\n"
                               "\n"
                               "[9]\n"
                               "[[8,7,6]]\n"
                               "\n"
                               "[[4,4],4,4]\n"
                               "[[4,4],4,4,4]\n"
                               "\n"
                               "[7,7,7,7]\n"
                               "[7,7,7]\n"
                               "\n"
                               "[]\n"
                               "[3]\n"
                               "\n"
                               "[[[]]]\n"
                               "[[]]\n"
                               "\n"
                               "[1,[2,[3,[4,[5,6,7]]]],8,9]\n"
                               "[1,[2,[3,[4,[5,6,0]]]],8,9]\n";
#else
    FILE* fp = fopen("day13_input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long file_len = ftell(fp);
    rewind(fp);
    char* input_string = (char*)calloc(file_len + 1, 1);
    fread(input_string, 1, file_len, fp);
    fclose(fp);
#endif

    struct packet* packets = NULL;

    const char* next = input_string;
    // Parse the packets
    do {
        struct packet packet;
        next = parse_packet(next, &packet);
        arrput(packets, packet);
    } while (next && *next > 0);

    int sum = 0;
    int pair_index = 1;
    for (int i = 0, len = arrlen(packets); i < len; i += 2) {
        struct packet left = packets[i];
        struct packet right = packets[i + 1];

        if (compare_packets(&left, &right) <= 0) {
            sum += pair_index;
        }
        pair_index++;
    }
    printf("sum: %d\n", sum);

    {
        struct packet div1 = (struct packet){.type = type_list};
        struct packet div1sub = (struct packet){.type = type_list};
        arrput(div1sub.items, ((struct packet){.type = type_value, .value = 2}));
        arrput(div1.items, div1sub);
        arrput(packets, div1);
    }

    {
        struct packet div2 = (struct packet){.type = type_list};
        struct packet div2sub = (struct packet){.type = type_list};
        arrput(div2sub.items, ((struct packet){.type = type_value, .value = 6}));
        arrput(div2.items, div2sub);
        arrput(packets, div2);
    }

    qsort(packets, arrlen(packets), sizeof(struct packet), cmp_packet);

    int d1 = 0;
    int d2 = 0;
    for (int i = 0, len = arrlen(packets); i < len; ++i) {
        char packet_str[1024];
        sprint_packet(packet_str, packets + i);
        if (strcmp(packet_str, "[[2]]") == 0) {
            d1 = i + 1;
        } else if (strcmp(packet_str, "[[6]]") == 0) {
            d2 = i + 1;
        }
    }

    printf("part 2: %d\n", d1 * d2);

    // int len = arrlen(packets);
    // for (int i = 0; i < len; ++i) {
    //     printf("%d\n", arrlen(packets[i]));
    // }

    // int sum = 0;
    // for (int i = 0; i < num_packets; ++i) {
    //     if (compare_packetse(packets[i * 2 + 0], )) }
    // int num_in_order = reorder_packets(packets, num_packets);
    // printf("%d\n", num_in_order); // Output: 7

    // // Free memory
    // for (int i = 0; i < num_packets; i++) {
    //     free(packets[i]);
    // }
    // free(packets);

    return 0;
}

int
cmp_int(int a, int b)
{
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

int
compare_packets(const struct packet* left, const struct packet* right)
{
    int ret = 0;
    if (left->type == type_value && right->type == type_value) {
        ret = cmp_int(left->value, right->value);
    } else if (left->type == type_list && right->type == type_list) {
        ret = compare_packet_lists(left->items, right->items);
    } else if (left->type == type_value) {
        struct packet* list = NULL;
        arrput(list, ((struct packet){.type = type_value, .value = left->value}));
        ret = compare_packet_lists(list, right->items);
        arrfree(list);
    } else if (right->type == type_value) {
        struct packet* list = NULL;
        arrput(list, ((struct packet){.type = type_value, .value = right->value}));
        ret = compare_packet_lists(left->items, list);
        arrfree(list);
    }

    return ret;
}

int
compare_packet_lists(const struct packet* left, const struct packet* right)
{
    int left_size = arrlen(left);
    int right_size = arrlen(right);

    int index = 0;
    while (index < left_size && index < right_size) {
        int cmp_ret = compare_packets(&left[index], &right[index]);
        if (cmp_ret != 0) return cmp_ret;
        index++;
    }

    if (index >= left_size && index < right_size) {
        return -1;
    } else if (index < left_size && index >= right_size) {
        return 1;
    } else {
        return 0;
    }
}

char*
sprint_packet(char* dst, struct packet* item)
{
    if (item->type == type_value) {
        int num = sprintf(dst, "%d", item->value);
        dst += num;
    } else {
        dst += sprintf(dst, "[");
        for (int i = 0, len = arrlen(item->items); i < len; ++i) {
            dst = sprint_packet(dst, item->items + i);
            if (i < len - 1) {
                int num = sprintf(dst, ",");
                dst += num;
            }
        }
        int num = sprintf(dst, "]");
        dst += num;
    }
    return dst;
}

void
print_packet(struct packet* item)
{
    char buffer[1024];
    sprint_packet(buffer, item);
    printf("%s\n", buffer);
}

const char*
parse_packet(const char* input_string, struct packet* packet)
{
    struct packet result = {.type = type_list};
    arrsetcap(result.items, 256);

    char* head = (char*)input_string;

    while (*head == '\n')
        head++;

    assert(*head == '[');

    head++;
    char* tail = head;

    struct packet* list_stack[256] = {result.items};
    int list_stack_top = 1;

    while (head && *head > 0) {
        struct packet* list = list_stack[list_stack_top - 1];

        if (*head == '[') {
            struct packet* new_list = NULL;
            arrsetcap(new_list, 256);
            struct packet new_list_item = (struct packet){
                .type = type_list,
                .items = new_list,
            };
            arrput(list, new_list_item);
            list_stack[list_stack_top++] = new_list;
            head++;
        } else if (*head == ']') {
            list_stack_top--;
            head++;
        } else if (*head == ',') {
            head++;
        } else if (isdigit(*head)) {
            int value = (int)strtol(head, &tail, 10);
            struct packet new_item = (struct packet){
                .type = type_value,
                .value = value,
            };
            arrput(list, new_item);
            head = tail;
        } else if (*head == '\n') {
            head++;
            tail = head;
            break;
        }
        tail = head;
    }

    *packet = result;

    if (!head || *head <= 0) return NULL;

    return head;
}

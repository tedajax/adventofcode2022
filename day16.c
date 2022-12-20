#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#if 0
const char* input_string = "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB\n"
                           "Valve BB has flow rate=13; tunnels lead to valves CC, AA\n"
                           "Valve CC has flow rate=2; tunnels lead to valves DD, BB\n"
                           "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE\n"
                           "Valve EE has flow rate=3; tunnels lead to valves FF, DD\n"
                           "Valve FF has flow rate=0; tunnels lead to valves EE, GG\n"
                           "Valve GG has flow rate=0; tunnels lead to valves FF, HH\n"
                           "Valve HH has flow rate=22; tunnel leads to valve GG\n"
                           "Valve II has flow rate=0; tunnels lead to valves AA, JJ\n"
                           "Valve JJ has flow rate=21; tunnel leads to valve II\n";
#else
const char* input_string = "Valve XB has flow rate=0; tunnels lead to valves YV, RP\n"
                           "Valve VN has flow rate=0; tunnels lead to valves WL, ET\n"
                           "Valve NT has flow rate=0; tunnels lead to valves CU, MQ\n"
                           "Valve ON has flow rate=0; tunnels lead to valves AA, FP\n"
                           "Valve CW has flow rate=0; tunnels lead to valves UH, WY\n"
                           "Valve KN has flow rate=0; tunnels lead to valves JL, MQ\n"
                           "Valve VT has flow rate=0; tunnels lead to valves CU, UI\n"
                           "Valve CR has flow rate=0; tunnels lead to valves OA, QQ\n"
                           "Valve YX has flow rate=0; tunnels lead to valves YJ, CI\n"
                           "Valve WL has flow rate=7; tunnels lead to valves OQ, VN, PU, VF, UA\n"
                           "Valve HV has flow rate=0; tunnels lead to valves OQ, OK\n"
                           "Valve JM has flow rate=21; tunnels lead to valves RG, OH, JE\n"
                           "Valve XF has flow rate=24; tunnels lead to valves OL, TM\n"
                           "Valve VD has flow rate=0; tunnels lead to valves MY, OK\n"
                           "Valve AA has flow rate=0; tunnels lead to valves KO, ON, UI, QE, VF\n"
                           "Valve JE has flow rate=0; tunnels lead to valves JM, NZ\n"
                           "Valve UN has flow rate=0; tunnels lead to valves UA, WY\n"
                           "Valve CC has flow rate=0; tunnels lead to valves IV, CU\n"
                           "Valve PU has flow rate=0; tunnels lead to valves JL, WL\n"
                           "Valve UA has flow rate=0; tunnels lead to valves WL, UN\n"
                           "Valve OJ has flow rate=13; tunnels lead to valves AZ, FP, MY, OL, ET\n"
                           "Valve CJ has flow rate=0; tunnels lead to valves MQ, WS\n"
                           "Valve IV has flow rate=0; tunnels lead to valves NZ, CC\n"
                           "Valve NZ has flow rate=4; tunnels lead to valves WS, IV, IU, EQ, JE\n"
                           "Valve TM has flow rate=0; tunnels lead to valves HL, XF\n"
                           "Valve SG has flow rate=0; tunnels lead to valves MQ, OH\n"
                           "Valve QQ has flow rate=12; tunnel leads to valve CR\n"
                           "Valve WX has flow rate=15; tunnels lead to valves CI, SN\n"
                           "Valve VF has flow rate=0; tunnels lead to valves WL, AA\n"
                           "Valve RP has flow rate=0; tunnels lead to valves WY, XB\n"
                           "Valve SN has flow rate=0; tunnels lead to valves WX, OI\n"
                           "Valve HL has flow rate=0; tunnels lead to valves OK, TM\n"
                           "Valve ET has flow rate=0; tunnels lead to valves OJ, VN\n"
                           "Valve UI has flow rate=0; tunnels lead to valves AA, VT\n"
                           "Valve FP has flow rate=0; tunnels lead to valves ON, OJ\n"
                           "Valve IU has flow rate=0; tunnels lead to valves NZ, QE\n"
                           "Valve JQ has flow rate=0; tunnels lead to valves HR, CU\n"
                           "Valve CU has flow rate=5; tunnels lead to valves NT, VT, JQ, CC\n"
                           "Valve WY has flow rate=19; tunnels lead to valves CW, UN, RP\n"
                           "Valve YJ has flow rate=16; tunnel leads to valve YX\n"
                           "Valve HR has flow rate=0; tunnels lead to valves JQ, JL\n"
                           "Valve RM has flow rate=11; tunnels lead to valves OI, AZ\n"
                           "Valve RG has flow rate=0; tunnels lead to valves YV, JM\n"
                           "Valve MY has flow rate=0; tunnels lead to valves VD, OJ\n"
                           "Valve QE has flow rate=0; tunnels lead to valves AA, IU\n"
                           "Valve OK has flow rate=17; tunnels lead to valves HL, UH, VD, HV\n"
                           "Valve CI has flow rate=0; tunnels lead to valves WX, YX\n"
                           "Valve OL has flow rate=0; tunnels lead to valves XF, OJ\n"
                           "Valve WS has flow rate=0; tunnels lead to valves CJ, NZ\n"
                           "Valve OH has flow rate=0; tunnels lead to valves JM, SG\n"
                           "Valve OQ has flow rate=0; tunnels lead to valves WL, HV\n"
                           "Valve OA has flow rate=0; tunnels lead to valves CR, MQ\n"
                           "Valve OI has flow rate=0; tunnels lead to valves SN, RM\n"
                           "Valve YV has flow rate=25; tunnels lead to valves RG, XB\n"
                           "Valve JL has flow rate=3; tunnels lead to valves KO, HR, PU, KN, EQ\n"
                           "Valve AZ has flow rate=0; tunnels lead to valves OJ, RM\n"
                           "Valve UH has flow rate=0; tunnels lead to valves CW, OK\n"
                           "Valve KO has flow rate=0; tunnels lead to valves AA, JL\n"
                           "Valve EQ has flow rate=0; tunnels lead to valves NZ, JL\n"
                           "Valve MQ has flow rate=10; tunnels lead to valves CJ, OA, NT, SG, KN\n";
#endif

#define TEST(m, b) (((m) & (1 << (b))) != 0)

enum
{
    MAX_VALVES = 16,
    NAME_LEN = 3,
    MAX_ADJ_NAMES = 5,
};

typedef char name[NAME_LEN];

struct valve_name
{
    char name[NAME_LEN];
};

struct valve_adj
{
    struct valve_name names[MAX_ADJ_NAMES];
};

typedef uint64_t sim_state;

struct sim_state_node
{
    sim_state state;
    int total_pressure;
    int location_id;
    int min_remaining;
    uint16_t open_mask;
    struct sim_state_node* parent;
    struct sim_state_node* children[MAX_VALVES];
};

struct sim_state_cache
{
    sim_state key;
    struct sim_state_node* value;
};

struct valve_system
{
    struct valve_name* names;
    int* flows;
    int** adj_matrix;
    int count;
    struct sim_state_cache* state_cache;
};

struct valve_system parse_valve_system(const char* input_string);
void simplify_valve_system(struct valve_system* valves);
void free_valve_system(struct valve_system* valves);

void print_adj_matrix(struct valve_system valves, int** override);
int** copy_adj_matrix(struct valve_system valves);

sim_state pack_sim_state(
    int min_remaining,
    int location_id,
    uint16_t open_mask,
    int total_pressure);
void unpack_sim_state(
    sim_state state,
    int* min_remaining,
    int* location_id,
    uint16_t* open_mask,
    int* total_pressure);
int sim_state_total_pressure(sim_state state);
int sim_state_is_finished(sim_state state);
int sim_state_min_remaining(sim_state state);
int sim_state_location_id(sim_state state);
uint16_t sim_state_open_mask(sim_state state);
sim_state sim_n_minutes(struct valve_system* valves, sim_state start_state, int n_minutes);
sim_state sim_open_valve(struct valve_system* valves, sim_state start_state, int valve_id);

struct sim_state_node*
build_state_tree(struct valve_system* valves, sim_state state, struct sim_state_node* parent)
{
    struct sim_state_node* node = hmget(valves->state_cache, state);
    if (!node) {
        node = (struct sim_state_node*)calloc(1, sizeof(struct sim_state_node));
        node->state = state;
        node->parent = parent;
        unpack_sim_state(
            node->state,
            &node->min_remaining,
            &node->location_id,
            &node->open_mask,
            &node->total_pressure);

        hmput(valves->state_cache, state, node);
    }

    if (node->min_remaining > 0) {
        int found_child = 0;
        for (int i = 1; i < valves->count; ++i) {
            if (!TEST(node->open_mask, i)) {
                int min_to_open = valves->adj_matrix[node->location_id][i] + 1;

                // skip anything we wont be able to open in time
                if (min_to_open >= node->min_remaining) {
                    continue;
                }

                int child_index;
                for (child_index = 0; child_index < MAX_VALVES; ++child_index)
                    if (node->children[child_index] == NULL) break;
                sim_state child_state = sim_open_valve(valves, state, i);
                node->children[child_index] = build_state_tree(valves, child_state, node);
                found_child = 1;
            }
        }
        if (!found_child && node->min_remaining > 0) {
            sim_state final_state = sim_n_minutes(valves, state, node->min_remaining);
            node->children[0] = build_state_tree(valves, final_state, node);
        }
    }

    return node;
}

sim_state
find_largest_leaf(struct sim_state_node* root)
{
    if (root->children[0] == NULL) {
        return root->state;
    }

    sim_state max_state = 0;
    for (int i = 0; i < MAX_VALVES; ++i) {
        if (!root->children[i]) break;
        sim_state child_largest = find_largest_leaf(root->children[i]);
        if (child_largest > max_state) max_state = child_largest;
    }

    return max_state;
}

void
asdf(struct sim_state_node* root)
{
    if (!root) return;

    if (root->min_remaining == 0 && root->total_pressure >= 1900)
        printf("%d\n", root->total_pressure);
    for (int i = 0; i < MAX_VALVES; ++i)
        asdf(root->children[i]);
}

int
main(void)
{
    struct valve_system valves = parse_valve_system(input_string);
    simplify_valve_system(&valves);

    int min_remaining = 30;
    int location_id = 0;
    uint16_t opened = 0;
    int total_pressure = 0;

    sim_state start_state = pack_sim_state(30, 0, 0, 0);
    sim_state state = start_state;
    struct sim_state_node* root = build_state_tree(&valves, start_state, NULL);

    asdf(root);

    sim_state largest_state = find_largest_leaf(root);
    struct sim_state_node* largest_node = hmget(valves.state_cache, largest_state);
    struct sim_state_node* node_path[MAX_VALVES];
    int node_path_len = 0;
    struct sim_state_node* slider = largest_node;
    while (slider) {
        node_path[node_path_len++] = slider;
        slider = slider->parent;
    }
    int head = 0, tail = node_path_len - 1;
    while (head < tail) {
        struct sim_state_node* tmp = node_path[head];
        node_path[head] = node_path[tail];
        node_path[tail] = tmp;
        head++;
        tail--;
    }
    int largest_pressure = sim_state_total_pressure(largest_state);
    printf("Largest pressure: %d\n", largest_pressure);

    for (int i = 0; i < node_path_len; ++i) {
        struct sim_state_node* curr = node_path[i];
        printf("== Minute %d ==\n", (curr->min_remaining > 0) ? 30 - curr->min_remaining + 1 : 30);
        int ppm = 0;
        printf("[ ");
        for (int j = 0; j < valves.count; ++j) {
            if (TEST(curr->open_mask, j)) {
                printf("%s ", valves.names[j].name);
                ppm += valves.flows[j];
            }
        }
        printf("] %d\n", ppm);
    }

    free_valve_system(&valves);

    return 0;
}

int
find_valve_id(struct valve_name* names, char name[3])
{
    for (int i = 0, len = arrlen(names); i < len; ++i) {
        struct valve_name* n = names + i;
        if (strcmp(n->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void
print_adj_matrix(struct valve_system valves, int** override)
{
    int** matrix = (override) ? override : valves.adj_matrix;

    int valve_count = arrlen(valves.names);
    printf("   ");
    for (int r = 0; r < valve_count; ++r) {
        printf(" %s", valves.names[r]);
    }
    printf("\n");

    for (int r = 0; r < valve_count; ++r) {
        printf("%s ", valves.names[r]);
        for (int c = 0; c < valve_count; ++c) {
            printf(" %02d", matrix[r][c]);
        }
        printf("\n");
    }
}

struct bfs_queue
{
    int id;
    int cost;
};

int
cmp_bfs_queue(const void* a, const void* b)
{
    struct bfs_queue a_item = *(const struct bfs_queue*)a;
    struct bfs_queue b_item = *(const struct bfs_queue*)b;
    return a_item.cost - b_item.cost;
}

int*
get_path(struct valve_system valves, int from_id, int to_id)
{
    if (from_id == to_id) return NULL;

    int* visited = NULL;
    int* parents = NULL;

    arrsetlen(visited, valves.count);
    memset(visited, 0, arrlen(visited) * sizeof(int));
    for (int i = 0; i < valves.count; ++i)
        arrput(parents, -1);
    struct bfs_queue* queue = NULL;
    arrput(queue, ((struct bfs_queue){.id = from_id, .cost = 0}));
    visited[from_id] = 1;
    int found = 0;
    while (arrlen(queue) > 0) {
        struct bfs_queue top = queue[0];
        arrdel(queue, 0);

        if (top.id == to_id) {
            found = 1;
            break;
        }

        for (int i = 0; i < valves.count; ++i) {
            int cost = valves.adj_matrix[top.id][i];
            if (cost > 0 && !visited[i]) {
                parents[i] = top.id;
                visited[i] = 1;
                arrput(queue, ((struct bfs_queue){.id = i, .cost = cost}));
                qsort(queue, arrlen(queue), sizeof(struct bfs_queue), cmp_bfs_queue);
            }
        }
    }

    if (!found) return NULL;

    int id = to_id;
    int* path = NULL;
    do {
        arrput(path, id);
        id = parents[id];
    } while (id != from_id);
    arrput(path, id);
    int head = 0, tail = arrlen(path) - 1;
    while (head < tail) {
        int tmp = path[head];
        path[head] = path[tail];
        path[tail] = tmp;
        head++;
        tail--;
    }

    arrfree(visited);
    arrfree(parents);
    arrfree(queue);

    return path;
}

int
path_dist(struct valve_system valves, int* path)
{
    if (!path) return -1;

    int dist = 0;
    for (int i = 0, len = arrlen(path); i < len - 1; ++i) {
        int cost = valves.adj_matrix[path[i]][path[i + 1]];
        if (cost == 0) return -1;
        dist += cost;
    }
    return dist;
}

void
print_path(int* path)
{
    for (int i = 0, len = arrlen(path); i < len; ++i) {
        printf("%d%c", path[i], (i == len - 1) ? ' ' : ',');
    }
    printf("\n");
}

int**
copy_adj_matrix(struct valve_system valves)
{
    int** copy = NULL;
    arrsetcap(copy, valves.count);
    for (int i = 0; i < valves.count; ++i) {
        int* row = NULL;
        arrsetcap(row, valves.count);
        for (int j = 0; j < valves.count; ++j)
            arrput(row, valves.adj_matrix[i][j]);
        arrput(copy, row);
    }
    return copy;
}

struct valve_system
parse_valve_system(const char* input_string)
{
    struct valve_system valves = {0};
    struct valve_adj* valve_adjs = NULL;

    const char* curr = input_string;
    name curr_name = {0};
    name curr_adj[5] = {0};
    int curr_flow;
    while (sscanf(
               curr,
               "Valve %c%c has flow rate=%d; tunnels lead to valves %c%c, %c%c, %c%c, %c%c, %c%c\n",
               curr_name,
               curr_name + 1,
               &curr_flow,
               curr_adj[0],
               curr_adj[0] + 1,
               curr_adj[1],
               curr_adj[1] + 1,
               curr_adj[2],
               curr_adj[2] + 1,
               curr_adj[3],
               curr_adj[3] + 1,
               curr_adj[4],
               curr_adj[4] + 1)
               > 5
           || sscanf(
                  curr,
                  "Valve %c%c has flow rate=%d; tunnel leads to valve %c%c\n",
                  curr_name,
                  curr_name + 1,
                  &curr_flow,
                  curr_adj[0],
                  curr_adj[0] + 1)
                  > 0)
    {
        curr = strstr(curr, "\n") + 1;
        struct valve_name name = {0};
        memcpy(name.name, curr_name, 2);
        arrput(valves.names, name);
        arrput(valves.flows, curr_flow);

        struct valve_adj adj = {0};
        for (int i = 0; i < 5; ++i) {
            if (!curr_adj[i]) break;
            memcpy(adj.names[i].name, curr_adj[i], 2);
        }
        arrput(valve_adjs, adj);

        memset(curr_adj, 0, sizeof(curr_adj));
        valves.count++;
    }

    for (int i = 0; i < valves.count; ++i) {
        int* adj_arr = NULL;
        for (int j = 0; j < valves.count; ++j)
            arrput(adj_arr, 0);
        for (int j = 0; j < 5; ++j) {
            int adj_id = find_valve_id(valves.names, valve_adjs[i].names[j].name);
            if (adj_id < 0) break;
            adj_arr[adj_id] = 1;
        }
        arrput(valves.adj_matrix, adj_arr);
    }

    return valves;
}

void
simplify_valve_system(struct valve_system* valves)
{
    int** adj_matrix_copy = copy_adj_matrix(*valves);

    // simplify adjacency matrix by removing adjacency to zero-flow valves and replacing adjacency
    // to non-zero-flow valves with cost to get to them
    for (int i = 0; i < valves->count; ++i) {
        if (i == 0 || valves->flows[i] > 0) {
            for (int j = 0; j < valves->count; ++j) {
                if (i == j) continue;
                if (j == 0 || valves->flows[j] > 0) {
                    int* path = get_path(*valves, i, j);
                    // print_path(path);
                    if (path) {
                        int dist = path_dist(*valves, path);
                        if (dist > adj_matrix_copy[i][j]) {
                            adj_matrix_copy[i][j] = dist;
                        }
                    }
                    arrfree(path);
                }
            }
        }
    }

    for (int i = 0; i < valves->count; ++i) {
        if (i != 0 && valves->flows[i] == 0) {
            for (int j = 0; j < valves->count; ++j) {
                adj_matrix_copy[i][j] = 0;
                adj_matrix_copy[j][i] = 0;
            }
        }
    }

    for (int i = 0; i < valves->count; ++i) {
        for (int j = 0; j < valves->count; ++j) {
            valves->adj_matrix[i][j] = adj_matrix_copy[i][j];
        }
        arrfree(adj_matrix_copy[i]);
    }
    arrfree(adj_matrix_copy);

    int new_count = 1; // always includes first valve since it's the starting point
    for (int i = 1; i < valves->count; ++i) {
        if (valves->flows[i] > 0) new_count++;
    }

    printf("simplified had %d will have %d\n", valves->count, new_count);

    struct valve_system new_valves = {.count = new_count};
    arrsetcap(new_valves.names, new_count);
    arrsetcap(new_valves.flows, new_count);
    arrsetcap(new_valves.adj_matrix, new_count);

    for (int i = 0; i < valves->count; ++i) {
        if (i == 0 || valves->flows[i] > 0) {
            arrput(new_valves.names, valves->names[i]);
            arrput(new_valves.flows, valves->flows[i]);
            int* row = NULL;
            arrsetcap(row, new_count);
            for (int j = 0; j < valves->count; ++j) {
                if (i == j || valves->adj_matrix[i][j] > 0) {
                    arrput(row, valves->adj_matrix[i][j]);
                }
            }
            arrput(new_valves.adj_matrix, row);
        }
    }

    free_valve_system(valves);
    *valves = new_valves;

    print_adj_matrix(*valves, NULL);
}

void
free_valve_system(struct valve_system* valves)
{
    arrfree(valves->names);
    arrfree(valves->flows);
    for (int i = 0; i < arrlen(valves->adj_matrix); ++i) {
        arrfree(valves->adj_matrix[i]);
    }
    arrfree(valves->adj_matrix);
    hmfree(valves->state_cache);

    // zero the system
    memset(valves, 0, sizeof(struct valve_system));
}

sim_state
pack_sim_state(int min_remaining, int location_id, uint16_t open_mask, int total_pressure)
{
    return (((sim_state)total_pressure) << 32) | (((sim_state)location_id & 0xF) << 21)
           | (((sim_state)min_remaining & 0x1F) << 16) | (sim_state)open_mask;
}

void
unpack_sim_state(
    sim_state state,
    int* min_remaining,
    int* location_id,
    uint16_t* open_mask,
    int* total_pressure)
{
    *min_remaining = sim_state_min_remaining(state);
    *location_id = sim_state_location_id(state);
    *open_mask = sim_state_open_mask(state);
    *total_pressure = sim_state_total_pressure(state);
}

int
sim_state_total_pressure(sim_state state)
{
    return state >> 32;
}

int
sim_state_location_id(sim_state state)
{
    return (state >> 21) & 0xF;
}

int
sim_state_is_finished(sim_state state)
{
    return sim_state_min_remaining(state) == 0;
}

int
sim_state_min_remaining(sim_state state)
{
    return (state >> 16) & 0x1F;
}

uint16_t
sim_state_open_mask(sim_state state)
{
    return (uint16_t)(state & 0xFFFF);
}

sim_state
sim_n_minutes(struct valve_system* valves, sim_state start_state, int n_minutes)
{
    int min_remaining = 0;
    int location_id = 0;
    uint16_t open_mask = 0;
    int total_pressure = 0;
    unpack_sim_state(start_state, &min_remaining, &location_id, &open_mask, &total_pressure);

    n_minutes = (min_remaining < n_minutes) ? min_remaining : n_minutes;

    int ppm = 0;
    for (int i = 0; i < valves->count; ++i)
        if (TEST(open_mask, i)) ppm += valves->flows[i];

    int added_pressure = ppm * n_minutes;

    min_remaining -= n_minutes;
    total_pressure += added_pressure;
    sim_state result = pack_sim_state(min_remaining, location_id, open_mask, total_pressure);
    return result;
}

sim_state
sim_open_valve(struct valve_system* valves, sim_state start_state, int valve_id)
{
    int min_remaining = 0;
    int location_id = 0;
    uint16_t open_mask = 0;
    int total_pressure = 0;
    unpack_sim_state(start_state, &min_remaining, &location_id, &open_mask, &total_pressure);

    // if the valve is already open nothing to simulate
    if (TEST(open_mask, valve_id)) return start_state;

    // simulate cost of moving to valve rounds plus one extra round to open the valve
    int n_minutes = valves->adj_matrix[location_id][valve_id] + 1;
    sim_state new_state = sim_n_minutes(valves, start_state, n_minutes);
    {
        open_mask |= (1 << valve_id);
        new_state = pack_sim_state(
            sim_state_min_remaining(new_state),
            valve_id,
            open_mask,
            sim_state_total_pressure(new_state));
    }
    return new_state;
}

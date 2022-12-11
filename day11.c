#include "util.h"

uint64_t op0(uint64_t old) { return old * 17; }
uint64_t op1(uint64_t old) { return old + 2; }
uint64_t op2(uint64_t old) { return old + 1; }
uint64_t op3(uint64_t old) { return old + 7; }
uint64_t op4(uint64_t old) { return old * old; }
uint64_t op5(uint64_t old) { return old + 8; }
uint64_t op6(uint64_t old) { return old * 2; }
uint64_t op7(uint64_t old) { return old + 6; }

enum
{
	NUM_MONKEYS = 8,
	MAX_INV = 256,
};

struct monkey
{
	uint64_t *items;
	uint64_t test;
	int on_true;
	int on_false;
};

uint64_t starting_items[NUM_MONKEYS][10] = {
	{59, 65, 86, 56, 74, 57, 56},
	{63, 83, 50, 63, 56},
	{93, 79, 74, 55},
	{86, 61, 67, 88, 94, 69, 56, 91},
	{76, 50, 51},
	{77, 76},
	{74},
	{86, 85, 52, 86, 91, 95},
};

uint64_t (*operations[NUM_MONKEYS])(uint64_t) = {op0, op1, op2, op3, op4, op5, op6, op7};

struct monkey monkeys[NUM_MONKEYS] = {
	{
		.test = 3,
		.on_true = 3,
		.on_false = 6,
	},
	{
		.test = 13,
		.on_true = 3,
		.on_false = 0,
	},
	{
		.test = 2,
		.on_true = 0,
		.on_false = 1,
	},
	{
		.test = 11,
		.on_true = 6,
		.on_false = 7,
	},
	{
		.test = 19,
		.on_true = 2,
		.on_false = 5,
	},
	{
		.test = 17,
		.on_true = 2,
		.on_false = 1,
	},
	{
		.test = 5,
		.on_true = 4,
		.on_false = 7,
	},
	{
		.test = 7,
		.on_true = 4,
		.on_false = 5,
	},
};

uint64_t inspec_counts[NUM_MONKEYS] = {0};

void print_monkey(int monkey_id)
{
	struct monkey *m = &monkeys[monkey_id];

	printf("Monkey %d:\n", monkey_id);
	printf("  Items: ");
	ptrdiff_t len = arrlen(m->items);
	for (ptrdiff_t i = 0; i < len; ++i)
	{
		printf("%llu ", m->items[i]);
	}
	printf("\n  Test: divisible by %d\n    If true: throw to monkey %d\n    If false: throw to monkey %d\n\n", m->test, m->on_true, m->on_false);
}

int descending(const void *a, const void *b)
{
	return *(const int *)a < *(const int *)b;
}

int main(int argc, char *argv[])
{
	uint64_t product = 1;

	for (int i = 0; i < NUM_MONKEYS; ++i)
	{
		arrsetcap(monkeys[i].items, 256);
		for (int j = 0; j < 10; ++j)
		{
			if (starting_items[i][j] <= 0)
				break;
			arrput(monkeys[i].items, starting_items[i][j]);
		}
		product *= monkeys[i].test;
	}

	for (int round = 0; round < 10000; ++round)
	{
		for (int monkey_id = 0; monkey_id < NUM_MONKEYS; ++monkey_id)
		{
			struct monkey *active = &monkeys[monkey_id];

			ptrdiff_t len = arrlen(active->items);
			for (ptrdiff_t i = 0; i < len; ++i)
			{
				uint64_t worry = active->items[i];
				worry = operations[monkey_id](worry);
				// worry /= 3;
				int target_id = (worry % active->test == 0) ? active->on_true : active->on_false;
				worry %= product;
				arrput(monkeys[target_id].items, worry);
				inspec_counts[monkey_id]++;
			}
			arrsetlen(active->items, 0);
		}
	}

	for (int i = 0; i < NUM_MONKEYS; ++i)
		print_monkey(i);

	for (int i = 0; i < NUM_MONKEYS; ++i)
	{
		printf("Monkey %d inspected items %lld times.\n", i, inspec_counts[i]);
	}
	qsort(inspec_counts, NUM_MONKEYS, sizeof(uint64_t), descending);
	for (int i = 0; i < NUM_MONKEYS; ++i)
	{
		printf("%lld\n", inspec_counts[i]);
	}

	printf("%lld * %lld = %lld\n", inspec_counts[0], inspec_counts[1], inspec_counts[0] * inspec_counts[1]);
	return 0;
}
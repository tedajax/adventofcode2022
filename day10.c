#include "util.h"

enum Op
{
	Op_Noop,
	Op_Addx,
};

enum Op parse_op(const char *str, long *param, int *cycles)
{
	if (!str || str[0] == 'n')
	{
		*param = 0;
		*cycles = 1;
		return Op_Noop;
	}
	*cycles = 2;
	*param = strtol(str + 5, NULL, 10);
	return Op_Addx;
}

int main(int argc, char *argv[])
{
	char **instructions = read_file_lines("day10_input.txt");

	long reg_x = 1;
	enum Op active_op = Op_Noop;
	long active_op_param = 0;
	int op_cycles_rem = 0;
	int cycle = 1;
	ptrdiff_t instr = 0;

	active_op = parse_op(instructions[instr], &active_op_param, &op_cycles_rem);

	long sum = 0;

	ptrdiff_t instr_num = arrlen(instructions);
	while (instr < instr_num)
	{
		if (op_cycles_rem <= 0)
		{
			if (active_op == Op_Addx)
			{
				reg_x += active_op_param;
			}

			instr++;
			if (instr >= instr_num)
				break;
			active_op = parse_op(instructions[instr], &active_op_param, &op_cycles_rem);
		}

		long crt_x = (cycle - 1) % 40;
		long diff = reg_x - crt_x;
		char c = (diff >= -1 && diff <= 1) ? 'O' : ' ';
		printf("%c", c);

		if (cycle % 40 == 0)
		{
			printf("\n");
		}

		if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
		{
			sum += cycle * reg_x;
		}

		op_cycles_rem--;

		cycle++;
	}

	free_file_lines(instructions);

	printf("Part 1: %d\n", sum);

	return 0;
}

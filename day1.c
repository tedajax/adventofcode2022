#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
	return *(int64_t*)b - *(int64_t*)a;
}

int main(int argc, char* argv[])
{
	FILE* fp = fopen("day1_input1.txt", "r");
	if (!fp) exit(1);

	enum { LineMaxLen = 256 };
	char line[LineMaxLen];

	int64_t inventories[1024] = { 0 };
	int idx = 0;

	int64_t current = 0;
	int64_t greatest = -1;
	
	while (fgets(line, LineMaxLen, fp) != NULL)
	{
		if (line[0] == '\n')
		{
			if (current > greatest) {
				greatest = current;
			}
			inventories[idx++] = current;
			current = 0;
		}
		else
		{
			int64_t value = strtoll(line, NULL, 10);
			current += value;
		}
	}

	printf("%lld\n", greatest);

	qsort(inventories, idx, sizeof(inventories[0]), cmp); 

	for (int i = 0; i < idx; ++i) {
		printf("%d: %lld\n", i, inventories[i]);
	}

	printf("%lld\n", inventories[0] + inventories[1] + inventories[2]);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int run_intcode(const int *program_src, int n, int v);

int main(int argc, char *argv[])
{
	// part one
	int result = run_intcode(program_source, 12, 2);
	printf("%d\n\n", result);

	// part two
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (run_intcode(program_source, i, j) == 19690720)
			{
				printf("noun %d verb %d\n", i, j);
				printf("%d\n", 100 * i + j);
				return 0;
			}
		}
	}
}

int run_intcode(const int *program_src, int n, int v)
{
	int *program = malloc(program_len * sizeof(int));
	for (int i = 0; i < program_len; i++)
		program[i] = program_src[i];
	program[1] = n;
	program[2] = v;
	int i = 0;
	while (1)
	{
		if (program[i] == 1) // add
		{
			int sum = program[program[++i]] + program[program[++i]];
			program[program[++i]] = sum;
		}
		else if (program[i] == 2) // mult
		{
			int prod = program[program[++i]] * program[program[++i]];
			program[program[++i]] = prod;
		}
		else if (program[i] == 99)
			break;
		i++;
	}
	return program[0];
}

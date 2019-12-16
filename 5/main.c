#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTRUCTION_BUFSIZE 256
#define INSTRUCTION_LENGTH 6

int program_len;

int run_intcode(char **src, const int len, const int n);
void parse_instruction(const char *instruction, int *opcode, int *mode1, int *mode2, int *mode3);
int load_program(char ***instructions);
int _load_program(int **src);

int main(int argc, char *argv[])
{
	char **src;
	int *i_src;
	int n_instructions = _load_program(&i_src);
	for (int i = 0; i < n_instructions; i++)
	{
		printf("%d\n", i_src[i]);
	}
	printf("%d\n", n_instructions);
	return 0;

	run_intcode(src, n_instructions, 1);
	return 0;

	for (int i = 0; i < n_instructions; i++)
	{
		int opcode, mode1, mode2, mode3;
		parse_instruction(src[i], &opcode, &mode1, &mode2, &mode3);
		printf("%d: %s\n", i, src[i]);
		printf("opcode: %d\nmode1: %d\nmode2: %d\nmode3: %d\n\n", opcode, mode1, mode2, mode3);
	}

}

int run_intcode(char **src, const int len, const int input)
{
	int pos = 0;
	while (pos < len)
	{
		int opcode, mode1, mode2, mode3;
		parse_instruction(src[pos], &opcode, &mode1, &mode2, &mode3);
		printf("%d: %s: %d\n", pos, src[pos], opcode);
		switch (opcode)
		{
			case 1: ; // add
				int sum;
				sum += mode1 ? atoi(src[pos + 1]) : atoi(src[atoi(src[pos + 1])]);
				sum += mode2 ? atoi(src[pos + 2]) : atoi(src[atoi(src[pos + 2])]);
				sprintf(src[atoi(src[pos + 3])], "%d", sum);
				pos += 4;
				break;
			case 2: // multiply
				pos += 4;
				break;
			case 3: ; // write
				int addr = atoi(src[pos + 1]);
				sprintf(src[addr], "%d", input);
				pos += 2;
				break;
			case 4: // read
				pos += 2;
				break;
			case 99:
				pos = len; // to break out of our while loop
				break;
			default:
				pos++;
				break;
		}
	}
}

int load_program(char ***instructions)
{
	int bufsize = INSTRUCTION_BUFSIZE;
	*instructions = malloc(bufsize * sizeof(char*));
	char c = 0;
	int n_instructions = 0;
	while (c != EOF)
	{
		if (n_instructions > bufsize)
		{
			bufsize += INSTRUCTION_BUFSIZE;
			*instructions = realloc(*instructions, bufsize * sizeof(char*));
		}
		(*instructions)[n_instructions++] = malloc(6 * sizeof(char));
		int i = 0;
		while ((c = getchar()) != ',' && c != EOF)
			(*instructions)[n_instructions - 1][i++] = c;
		(*instructions)[n_instructions - 1][i] = '\0';
	}

	return n_instructions;
}

int _load_program(int **src)
{
	int bufsize = INSTRUCTION_BUFSIZE;
	*src = malloc(bufsize * sizeof(int));
	char c = 0;
	int src_len = 0;
	while (c != EOF)
	{
		if (src_len > bufsize)
		{
			bufsize += INSTRUCTION_BUFSIZE;
			*src = realloc(*src, bufsize * sizeof(int));
		}

		char buf[6];
		int i = 0;
		while ((c = getchar()) != ',' && c != EOF)
			buf[i++] = c;
		buf[i] = '\0';
		(*src)[src_len++] = atoi(buf);
	}
}

void parse_instruction(const char *instruction, int *opcode, int *mode1, int *mode2, int *mode3)
{
	int len = strlen(instruction);

	*opcode = *mode1 = *mode2 = *mode3 = 0;
	switch (len)
	{
		case 5: // ABCDE
			*mode3 = instruction[len - 5] - 48;
		case 4: // BCDE
			*mode2 = instruction[len - 4] - 48;
		case 3: // CDE
			*mode1 = instruction[len - 3] - 48;
		case 2: // DE
			*opcode += (instruction[len - 2] - 48) * 10;
		case 1: // E
			*opcode += instruction[len - 1] - 48;
	}
}

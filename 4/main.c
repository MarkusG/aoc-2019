#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char byte;
typedef char bool;

char valid(int password);
char valid_2(int password);

int main(int argc, char *argv[])
{
	int n_valid_passwords = 0;
	int n_valid_passwords_2 = 0;
	for (int i = 245318; i <= 765747; i++)
	{
		if (valid(i))
			n_valid_passwords++;
		if (valid_2(i))
		{
			printf("%d is valid\n", i);
			n_valid_passwords_2++;
		}
	}
	printf("Part 1: %d\nPart 2: %d\n", n_valid_passwords, n_valid_passwords_2);
	return 0;
}

bool valid(int password)
{
	byte digits[6];
	bool pair = FALSE;
	bool decreases = FALSE;
	for (int i = 6, j = 0; i > 0; i--)
	{
		digits[j] = password / (int)pow(10, i - 1);
		password -= digits[j] * (int)pow(10, i - 1);

		if (j > 0)
		{
			if (digits[j - 1] == digits[j])
				pair = TRUE;
			if (digits[j] < digits[j - 1])
				return FALSE;
		}
		j++;
	}
	return pair;
}

bool valid_2(int password)
{
	int orig_pass = password;
	byte digits[6];
	bool pair = FALSE;
	for (int i = 6, j = 0; i > 0; i--, j++)
	{
		digits[j] = password / (int)pow(10, i - 1);
		password -= digits[j] * (int)pow(10, i - 1);
	}
	for (int i = 1; i < 6; i++) // increase check
	{
		if (digits[i] < digits[i - 1])
			return FALSE;
	}
	for (int i = 0; i < 6; i++) // pair check
	{
		byte digit = digits[i];
		if (digit == digits[i + 1])
		{
			byte block_count = 0;
			for (; digits[i] == digit; i++, block_count++);
			if (block_count == 2)
				return pair = TRUE;
			else
				i--;
		}
	}
	return FALSE;
}

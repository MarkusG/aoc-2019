#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef char byte;
typedef char bool;

char valid(int password);
char valid_2(int password);

int main(int argc, char *argv[])
{
	/* valid_2(677888); */
	/* return 0; */
	int n_valid_passwords = 0;
	int n_valid_passwords_2 = 0;
	for (int i = 245318; i <= 765747; i++)
	{
		if (valid(i))
			n_valid_passwords++;
		if (valid_2(i))
			n_valid_passwords_2++;
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
	for (int i = 6, j = 0; i > 0; i--)
	{
		digits[j] = password / (int)pow(10, i - 1);
		password -= digits[j] * (int)pow(10, i - 1);

		if (j > 0)
		{
			if (digits[j - 1] == digits[j])
			{
				if (digits[j - 2] == digits[j])
				{
					printf("%d failed pair check\n", orig_pass);
					return FALSE;
				}
				else
				{
					if (digits[j] < digits[j - 1])
					{
						printf("%d failed increase check\n", orig_pass);
						return FALSE;
					}
					else
						return TRUE;
				}
			}
		}
		j++;
	}
}

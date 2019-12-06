#include <stdio.h>
#include "input.h"

int fuel_required(int mass);

int main(int argc, char *argv[])
{
	// part one
	int total = 0;
	for (int i = 0; i < n_modules; i++)
		total += fuel_required(modules[i]);
	printf("total: %d\n\n", total);

	// part two
	total = 0;
	for (int i = 0; i < n_modules; i++)
	{
		int fuel = fuel_required(modules[i]);
		while (fuel > 0)
		{
			total += fuel;
			fuel = fuel_required(fuel);
		}
	}
	printf("total: %d\n", total);
}

int fuel_required(int mass)
{
	return mass / 3 - 2;
}

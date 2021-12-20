#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double	map(uint16_t x, uint16_t y)
{
	uint32_t result = y % 2 ? (1 << 16) - 1 - x : x;//-1?
	// printf("1 : %d\n", result);
	// printf("1 : %d\n", ft_iterative_power(2, 16));
	// printf("1 : %d\n", x);
	result += y << 16;
	// printf("r : %lx\n", result);
	// printf("r : %lu\n", ((uint64_t)1 << 32) - 1);
	return ((double)((double)result/(double)(((uint64_t)1 << 32) - 1)));
}
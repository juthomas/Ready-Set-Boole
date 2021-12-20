#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double	map(uint16_t x, uint16_t y)
{
	uint32_t result = y % 2 ? (1 << 16) - 1 - x : x;//-1?
	result += y << 16;
	// printf("r : %x\n", result);
	return ((double)((double)result/(double)(((uint64_t)1 << 32) - 1)));
}
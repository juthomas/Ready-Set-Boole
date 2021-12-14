#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void printBits(size_t const size, void const * const ptr);

uint32_t adder(uint32_t a, uint32_t b);

uint32_t multiplier(uint32_t a, uint32_t b)
{
	uint32_t result = 0;
	uint32_t index = 0;

	while (index < 32)
	{
		if (a & (1 << index))
		{
			result = adder(result, (b) << index);
		}
		index++;
	}
	return (result);
}
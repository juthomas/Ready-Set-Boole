#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <stdexcept>

std::tuple<uint16_t, uint16_t>	reverse_map(double n)
{
	uint32_t result = (uint32_t)((double)n*(double)(((uint64_t)1 << 32) - 1));
	// printf("result : %x\n", result);
	uint16_t y = result >> 16; 
	uint16_t x = y % 2 ? (1 << 16) - 1 - (result & 0xFFFF)  : (result & 0xFFFF);
	return (std::tuple<uint16_t, uint16_t>{x, y});
}
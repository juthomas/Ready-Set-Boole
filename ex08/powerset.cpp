#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <array>
// using std;

void printBits(size_t const size, void const * const ptr)
{
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;
	
	for (i = size-1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

std::vector<std::vector<int32_t> > powerset(std::vector<int32_t> set)
{
	std::vector<std::vector<int32_t> > return_value;
	// uint32_t xor_result;
	// uint32_t and_result;

	// while (a & b)
	// {
	// 	xor_result = a ^ b;
	// 	and_result = (a & b) << 1;
	// 	a = xor_result;
	// 	b = and_result;
	// }
	uint64_t max_iterations = 1 << set.size();
	// printf("max iterations :%ld\n", max_iterations);

	for (uint64_t current_iteration = 0; current_iteration < max_iterations; current_iteration++)
	{
		std::vector<int32_t> new_row;
		for (uint64_t i = 0; i < set.size(); i++)
		{
				// printf("cc %d\n", 1 << i);
				// printf("cd %d\n", max_iterations);

			if (1 << i & current_iteration)
			{
				// printf("cc\n");
				new_row.push_back(set[i]);
			}
		}
		return_value.push_back(new_row);
	}

	// return_value.push_back(std::vector<int32_t>());



	return (return_value);
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

uint32_t adder(uint32_t a, uint32_t b)
{
	uint32_t xor_result;
	uint32_t and_result;

	while (a & b)
	{
		xor_result = a ^ b;
		and_result = (a & b) << 1;
		a = xor_result;
		b = and_result;
	}
	return (a | b);
}

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


int main(int argc, char **argv)
{
	uint32_t a = argc == 3 ? atoi(argv[1]) : 3 ;
	uint32_t b = argc == 3 ? atoi(argv[2]) : 13;
	uint32_t result = 0;
	printf("a : ");
	printBits(sizeof(uint32_t), &a);

	printf("b : ");
	printBits(sizeof(uint32_t), &b);

	result = a * b;
	printBits(sizeof(uint32_t), &result);
	result = multiplier(a, b);
	printBits(sizeof(uint32_t), &result);
}
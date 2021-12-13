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

uint32_t	ft_iterative_power(uint32_t nb, uint32_t power)
{
	uint32_t	banane;

	banane = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		banane *= nb;
		power--;
	}
	return (banane);
}

uint32_t gray_code(uint32_t n)
{
	uint32_t current_number = 0;
	uint32_t current_deep = 0;

	while (n >= 1 << current_deep)
	{
		current_number |= (n + ft_iterative_power(2, current_deep)) % ft_iterative_power(2, current_deep + 2) >= ft_iterative_power(2, current_deep + 1) ? 1 << current_deep : 0;
		current_deep++;
	}
	return(current_number);
}

int main(int argc, char **argv)
{
	uint32_t a = argc == 2 ? atoi(argv[1]) : 3 ;
	uint32_t result = 0;
	if (argc == 2 && atoi(argv[1]) == 42 )
	{
		for (int i = 0; i < 100; i++)
		{
			printf("%02d : ", i);
			result = gray_code(i);
			printBits(sizeof(uint32_t), &result);
		}
		return (0);
	}
	printf("a : ");
	printBits(sizeof(uint32_t), &a);
	result = gray_code(a);
	printf("result : ");
	printBits(sizeof(uint32_t), &result);
	return (0);
}

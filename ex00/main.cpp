#include <string>

uint32_t adder(uint32_t a, uint32_t b);
void printBits(size_t const size, void const * const ptr);

int main(int argc, char **argv)
{
	uint32_t a = argc == 3 ? atoi(argv[1]) : 3 ;
	uint32_t b = argc == 3 ? atoi(argv[2]) : 13;
	uint32_t result = 0;
	printf("a : ");
	printBits(sizeof(uint32_t), &a);

	printf("b : ");
	printBits(sizeof(uint32_t), &b);

	result = a + b;
	printBits(sizeof(uint32_t), &result);
	result = adder(a, b);
	printBits(sizeof(uint32_t), &result);
}
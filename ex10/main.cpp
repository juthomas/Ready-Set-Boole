#include <string>

double	map(uint16_t x, uint16_t y);


int main(int argc, char **argv)
{
	uint32_t x = argc == 3 ? atoi(argv[1]) : 3 ;
	uint32_t y = argc == 3 ? atoi(argv[2]) : 13;
	double result = 0;
	if (x >= 1 << 16 || y >= 1 << 16)
	{
		printf("input trop grand, noob\n");
		return (0);
	}
	
	printf("input : x=%d y=%d\n", x, y);
	result = map(x, y);
	printf("output : %.15f\n", result);
}
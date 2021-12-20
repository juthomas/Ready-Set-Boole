#include <string>
#include <tuple>
#include <stdexcept>
std::tuple<uint16_t, uint16_t>	reverse_map(double n);

int main(int argc, char **argv)
{
	double x = argc == 2 ? atof(argv[1]) : 0.5 ;
	// double result = 0;
	if (x < 0 || x > 1)
	{
		printf("input pas convenable, noob\n");
		return (0);
	}
	
	printf("input : %.20f\n", x);
	std::tuple<uint16_t, uint16_t> result = reverse_map(x);
	printf("output : x=%d y=%d\n", std::get<0>(result), std::get<1>(result));
	// result = reverse_map(x, y);
}
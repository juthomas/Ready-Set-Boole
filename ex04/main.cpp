#include <string>

void	print_truth_table(std::string formula);

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		print_truth_table(str);
	}
}
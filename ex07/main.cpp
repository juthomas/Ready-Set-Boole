#include <string>

bool	sat(std::string formula);

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		printf("%s\n", sat(str) ? "true" : "false");
	}
}
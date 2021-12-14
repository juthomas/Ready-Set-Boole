#include <string>

bool eval_formula(std::string formula);

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		printf("%s\n", eval_formula(str) ? "true" : "false");
	}
}
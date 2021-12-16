#include <string>

void	negation_normal_form(std::string formula);

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		negation_normal_form(str);
	}
}
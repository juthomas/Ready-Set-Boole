#include <string>
#include <algorithm>

bool	eval_formula(std::string formula);

std::string	print_alpha_association(std::string str, uint8_t current_iteration)
{
	std::string return_string = "";
	uint8_t letter_shift = 0;
	for (uint8_t letter = 'Z'; letter >= 'A'; letter--)
	{
		if (str.find(letter) != -1)
		{
			letter_shift += 1;
		}
	}
	for (uint8_t letter = 'Z'; letter >= 'A'; letter--)
	{
		if (str.find(letter) != -1)
		{
			letter_shift -= 1;
			return_string += "| ";
			return_string += (current_iteration & (1 << letter_shift)) ? "1" : "0";
			return_string += " ";
		}
	}
	return (return_string);
}

std::string replace_variables(std::string str, uint8_t current_iteration)
{
	uint8_t letter_shift = 0;
	std::string alpha_association_str = print_alpha_association(str, current_iteration);
	for (uint8_t letter = 'Z'; letter >= 'A'; letter--)
	{
		if (str.find(letter) != -1)
		{
			size_t pos;
			while ((pos = str.find(letter)) != -1) {
				str.replace(pos, 1, (current_iteration & (1 << letter_shift)) ? "1" : "0" );
			}
			letter_shift += 1;
		}
	}
	if (1 << letter_shift <= current_iteration)
		return ("");
	// printf("%s", alpha_association_str.c_str());
	return (str);
}

void print_header(std::string str)
{
	for (uint8_t letter = 'A'; letter < 'Z'; letter++)
	{
		if (str.find(letter) != -1)
		{
			printf("| %c ", letter);
		}
	}
	printf("| = |\n");
	for (uint8_t letter = 'A'; letter < 'Z'; letter++)
	{
		if (str.find(letter) != -1)
		{
			printf("|---");
		}
	}
	printf("|---|\n");
}

bool	sat(std::string formula)
{
	std::string str = "";
	uint32_t current_iteration = 0;
	while ((str = replace_variables(formula, current_iteration)) != "")
	{
		if (eval_formula(str))
			return (true);
		current_iteration++;
	}
	return (false);
}
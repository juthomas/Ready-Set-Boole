#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

typedef void(*t_operating)(std::vector<bool> *boolean_stack);

typedef struct	s_operators
{
	char		input_sign;
	char		output_sign;
	t_operating	f_prop;
}				t_operators;

void error_function(int32_t line, const char* function, const char* message)
{
	printf("[%03d] [%s] - %s\n", line, function, message);
	exit(0);
}

void negation_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 0)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	(*boolean_stack).back() = !(*boolean_stack).back();
}

void conjunction_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 1)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	bool a = (*boolean_stack).back();
	(*boolean_stack).pop_back();
	(*boolean_stack).back() = a & (*boolean_stack).back();
}

void disjunction_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 1)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	bool a = (*boolean_stack).back();
	(*boolean_stack).pop_back();
	(*boolean_stack).back() = a | (*boolean_stack).back();
}

void exclusive_disjunction_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 1)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	bool a = (*boolean_stack).back();
	(*boolean_stack).pop_back();
	(*boolean_stack).back() = a ^ (*boolean_stack).back();
}

void material_condition_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 1)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	bool a = (*boolean_stack).back();
	(*boolean_stack).pop_back();
	(*boolean_stack).back() = !((*boolean_stack).back() & !a) ;
}

void logical_equivalence_function(std::vector<bool> *boolean_stack)
{
	if ((*boolean_stack).size() <= 1)
		error_function(__LINE__, __FUNCTION__, (char*)"Stack size too small");
	bool a = (*boolean_stack).back();
	(*boolean_stack).pop_back();
	(*boolean_stack).back() = a == (*boolean_stack).back();
}

static const t_operators g_operators[] = {
	(t_operators){.input_sign = '!', .output_sign = '!', .f_prop = negation_function},
	(t_operators){.input_sign = '&', .output_sign = '&', .f_prop = conjunction_function},
	(t_operators){.input_sign = '|', .output_sign = '|', .f_prop = disjunction_function},
	(t_operators){.input_sign = '^', .output_sign = '^', .f_prop = exclusive_disjunction_function},
	(t_operators){.input_sign = '>', .output_sign = '>', .f_prop = material_condition_function},
	(t_operators){.input_sign = '=', .output_sign = '=', .f_prop = logical_equivalence_function},
};

void visualize_stack(std::vector<bool> boolean_stack)
{
	printf("---\n");
	for(int i=boolean_stack.size()-1; i >= 0; i--){
		printf("-%s\n", boolean_stack[i] ? "true" : "false");
	}
	printf("---\n");
}

bool apply_operations(std::vector<bool> boolean_stack, std::vector<t_operators> operators_stack)
{
	for(const auto& value: operators_stack) {
		value.f_prop(&boolean_stack);
	}
	return (boolean_stack.back());
}


void	view_operations(std::vector<bool> boolean_stack, std::vector<t_operators> operators_stack)
{
	for(const auto& value: operators_stack) {
		// std::cout << value << "\n";
		// g_operators[current_index].f_prop(&boolean_stack);
		// printf("v :%c", value.input_sign);
	}
}

bool eval_formula(std::string formula)
{
	std::vector<bool> boolean_stack;
	std::vector<t_operators> operators_stack;
	bool char_exist = false;

	for (std::string::size_type i = 0; i < formula.size(); i++) {
		char_exist = false;
		if (formula[i] == '0' || formula[i] == '1')
		{
			boolean_stack.push_back(formula[i] == '1' ? true : false);
			char_exist = true;
		}
		else for (uint8_t current_index = 0;
			current_index < sizeof(g_operators) / sizeof(t_operators);
			current_index++)
		{
			if (formula[i] == g_operators[current_index].input_sign)
			{
				// g_operators[current_index].f_prop(&boolean_stack);
				operators_stack.push_back(g_operators[current_index]);
				char_exist = true;
			}
		}
		if (!char_exist)
		{
			printf("This sign is not valid : '%c'\n", formula[i]);
			exit(0);
		}

	}
	// visualize_stack(boolean_stack);
	// apply_operations(boolean_stack, operators_stack);
	return (apply_operations(boolean_stack, operators_stack));
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		printf("%s\n", eval_formula(str) ? "true" : "false");
	}
}
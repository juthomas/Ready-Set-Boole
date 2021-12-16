#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

typedef uint8_t(*t_operating)(uint8_t a, uint8_t b);

typedef struct			s_tree_node
{
	uint8_t				operator_index;
	uint8_t				result;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	s_tree_node(uint8_t index)
	{
		operator_index = index;
		left = NULL;
		right = NULL;
		result = 0;
	}

}						t_tree_node;

typedef struct			s_operators
{
	char				input_sign;
	char				output_sign;
	t_operating			f_prop;
}						t_operators;

void error_function(int32_t line, const char* function, const char* message)
{
	printf("[%03d] [%s] - %s\n", line, function, message);
	exit(0);
}

uint8_t negation_function(uint8_t a, uint8_t b)
{
	return (!a);
}

uint8_t conjunction_function(uint8_t a, uint8_t b)
{
	return (a & b);
}

uint8_t disjunction_function(uint8_t a, uint8_t b)
{
	return (a | b);
}

uint8_t exclusive_disjunction_function(uint8_t a, uint8_t b)
{
	return (a ^ b);
}

uint8_t material_condition_function(uint8_t a, uint8_t b)
{
	return (!(!a & b));
}

uint8_t logical_equivalence_function(uint8_t a, uint8_t b)
{
	return (a == b);
}

static const t_operators g_operators[] = {
	(t_operators){.input_sign = '0', .output_sign = '0', .f_prop = NULL},
	(t_operators){.input_sign = '1', .output_sign = '1', .f_prop = NULL},
	(t_operators){.input_sign = '!', .output_sign = '!', .f_prop = negation_function},
	(t_operators){.input_sign = '&', .output_sign = '&', .f_prop = conjunction_function},
	(t_operators){.input_sign = '|', .output_sign = '|', .f_prop = disjunction_function},
	(t_operators){.input_sign = '^', .output_sign = '^', .f_prop = exclusive_disjunction_function},
	(t_operators){.input_sign = '>', .output_sign = '>', .f_prop = material_condition_function},
	(t_operators){.input_sign = '=', .output_sign = '=', .f_prop = logical_equivalence_function},
};




// void	visualize_tree(std::vector<t_tree_node*> boolean_stack)
// {
// 	printf("---\n");
// 	for(int i=boolean_stack.size()-1; i >= 0; i--){
// 		printf("-%c\n", g_operators[boolean_stack[i]->operator_index].input_sign );
// 	}
// 	printf("---\n");

// }

void printBT(const std::string& prefix, const t_tree_node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << g_operators[node->operator_index].input_sign << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

uint8_t		resolve_tree(t_tree_node* node, t_tree_node* parent, bool side)
{
	// if (node == NULL)
	// {
	// 	return 0;
	// }
	if (node->operator_index <= 1)
	{
		return (node->operator_index);
	}
	else
	{
		uint8_t a = resolve_tree(node->left, node, false);
		uint8_t b = resolve_tree(node->right, node, true);
		printf("%c [%c] %s -%d- -%d-\n",
			g_operators[node->operator_index].input_sign,
			parent ? g_operators[parent->operator_index].input_sign : ' ',
			side ? "right" : "left", a, b);

		 return (g_operators[node->operator_index].f_prop(a, b));
	}
}

// void	visualize_tree_iterative(t_tree_node* node)
// {
// 	if (node == NULL)
// 	{
// 		return;
// 	}
// 	else
// 	{
// 		printf("%c ", g_operators[node->operator_index].input_sign );
// 		visualize_tree(node->left);
// 		visualize_tree(node->right);
// 	}
// }


void visualize_stack(std::vector<uint8_t> boolean_stack)
{
	printf("---\n");
	for(int i=boolean_stack.size()-1; i >= 0; i--){
		printf("-%s\n", boolean_stack[i] ? "true" : "false");
	}
	printf("---\n");
}

bool apply_operations(std::vector<uint8_t> boolean_stack, std::vector<t_operators> operators_stack)
{
	for(const auto& value: operators_stack) {
		// value.f_prop(&boolean_stack);
	}
	return (boolean_stack.back());
}


void	view_operations(std::vector<uint8_t> boolean_stack, std::vector<t_operators> operators_stack)
{
	for(const auto& value: operators_stack) {
		// std::cout << value << "\n";
		// g_operators[current_index].f_prop(&boolean_stack);
		// printf("v :%c", value.input_sign);
	}
}

bool eval_formula(std::string formula)
{
	std::vector<t_tree_node*> boolean_stack;
	std::vector<t_operators> operators_stack;
	bool char_exist = false;
	t_tree_node	*tmp_left;
	t_tree_node	*tmp_right;
	t_tree_node	*tmp_node;
	// for (std::string::size_type i = 0; i < formula.size(); i++) {
	// 	char_exist = false;
	// 	if (formula[i] == '0' || formula[i] == '1')
	// 	{
	// 		boolean_stack.push_back(formula[i] == '1' ? true : false);
	// 		char_exist = true;
	// 	}
	// 	else for (uint8_t current_index = 0;
	// 		current_index < sizeof(g_operators) / sizeof(t_operators);
	// 		current_index++)
	// 	{
	// 		if (formula[i] == g_operators[current_index].input_sign)
	// 		{
	// 			// g_operators[current_index].f_prop(&boolean_stack);
	// 			operators_stack.push_back(g_operators[current_index]);
	// 			char_exist = true;
	// 		}
	// 	}
	// 	if (!char_exist)
	// 	{
	// 		printf("This sign is not valid : '%c'\n", formula[i]);
	// 		exit(0);
	// 	}
	// }


	for (std::string::size_type i = 0; i < formula.size(); i++) {
		// if (formula[i] == '0' || formula[i] == '1')
		// {
		// 	// boolean_stack.push_back(formula[i] == '1' ? true : false);
		// 	tmp_node = new t_tree_node(i);
		// 	char_exist = true;
		// }
		// else 
		for (uint8_t current_index = 0;
			current_index < sizeof(g_operators) / sizeof(t_operators);
			current_index++)
		{
			if (formula[i] == g_operators[current_index].input_sign
				&& (formula[i] == '0' || formula[i] == '1'))
			{
				tmp_node = new t_tree_node(current_index);
				boolean_stack.push_back(tmp_node);
				char_exist = true;
			}
			else if (formula[i] == g_operators[current_index].input_sign
				&& formula[i] == '!')
			{
				tmp_node = new t_tree_node(current_index);
				tmp_right = (boolean_stack).back();
				(boolean_stack).pop_back();
				// tmp_left = (boolean_stack).back();
				// (boolean_stack).pop_back();
				tmp_node->right = tmp_right;
				// tmp_node->left = tmp_left;
				boolean_stack.push_back(tmp_node);
			}
			else if (formula[i] == g_operators[current_index].input_sign)
			{
				tmp_node = new t_tree_node(current_index);
				tmp_right = (boolean_stack).back();
				(boolean_stack).pop_back();
				tmp_left = (boolean_stack).back();
				(boolean_stack).pop_back();
				tmp_node->left = tmp_left;
				tmp_node->right = tmp_right;
				boolean_stack.push_back(tmp_node);
				// // g_operators[current_index].f_prop(&boolean_stack);
				// operators_stack.push_back(g_operators[current_index]);
				// char_exist = true;
			}
		}
		if (!char_exist)
		{
			printf("This sign is not valid : '%c'\n", formula[i]);
			exit(0);
		}
	}

	// visualize_stack(boolean_stack);
	printf("---\n");
	printf("Tree result : %d", resolve_tree(boolean_stack[0], NULL, false));
	printf("---\n");
	printBT("", boolean_stack[0], false);
	// apply_operations(boolean_stack, operators_stack);
	// return (apply_operations(boolean_stack, operators_stack));
	return (true);
}
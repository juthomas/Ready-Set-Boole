#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

typedef std::vector<int32_t>(*t_operating)(std::vector<int32_t> a, std::vector<int32_t> b);

typedef struct			s_tree_node
{
	uint8_t				operator_index;
	std::vector<int32_t>	vector_set;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	s_tree_node(uint8_t index)
	{
		operator_index = index;
		left = NULL;
		right = NULL;
		// result = 0;
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

std::vector<int32_t> negation_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);
	return (std::vector<int32_t>());
}

std::vector<int32_t> conjunction_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);
	std::vector<int32_t> new_set;
	bool child_contain = false;

	for (size_t i = 0; i < a.size(); i++)
	{
		child_contain = false;
		for (size_t u = 0; u < b.size(); u++)
		{
			if (a[i] == b[u])
			{
				child_contain = true;
			}
		}
		if (child_contain)
		{
			new_set.push_back(a[i]);
		}
	}
	return (new_set);
}

std::vector<int32_t> disjunction_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);

	std::vector<int32_t> new_set;
	bool child_contain = false;

	for (size_t i = 0; i < a.size(); i++)
	{
		new_set.push_back(a[i]);
	}
	for (size_t u = 0; u < b.size(); u++)
	{
		bool child_contain = false;
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] == b[u])
			{
				child_contain = true;
			}
		}
		if (!child_contain)
		{
			new_set.push_back(b[u]);
		}
	}
	return (new_set);
}

std::vector<int32_t> exclusive_disjunction_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);

	std::vector<int32_t> new_set;
	bool child_contain = false;
	for (size_t i = 0; i < a.size(); i++)
	{
		child_contain = false;
		for (size_t u = 0; u < b.size(); u++)
		{
			if (a[i] == b[i])
			{
				child_contain = true;
			}
		}
		if (!child_contain)
		{
			new_set.push_back(a[i]);
		}
	}
	for (size_t i = 0; i < b.size(); i++)
	{
		child_contain = false;
		for (size_t u = 0; u < a.size(); u++)
		{
			if (a[i] == b[i])
			{
				child_contain = true;
			}
		}
		if (!child_contain)
		{
			new_set.push_back(b[i]);
		}
	}
	return (new_set);
}

std::vector<int32_t> material_condition_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);
	std::vector<int32_t> new_set;
	bool equation_ok = false;
	for (size_t i = 0; i < a.size(); i++)
	{
		equation_ok = true;
		for (size_t u = 0; u < b.size(); u++)
		{
			if (a[i] >= b[i])
			{
				equation_ok = false;
			}
		}
		if (equation_ok)
		{
			new_set.push_back(a[i]);
		}
	}
	return (new_set);
}

std::vector<int32_t> logical_equivalence_function(std::vector<int32_t> a, std::vector<int32_t> b)
{
	// return (a);
	std::vector<int32_t> new_set;
	bool equation_ok = false;
	for (size_t i = 0; i < a.size(); i++)
	{
		equation_ok = true;
		for (size_t u = 0; u < b.size(); u++)
		{
			if (a[i] != b[i])
			{
				equation_ok = false;
			}
		}
		if (equation_ok)
		{
			new_set.push_back(a[i]);
		}
	}
	return (new_set);
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
		if (node->operator_index == 0)
		{
			printf("[");
			for (int32_t &s: (std::vector<int32_t>)node->vector_set) {
				printf("%d, ", s);
    		}
			printf("]\n");
		}
		else
	        std::cout << g_operators[node->operator_index].input_sign << std::endl;


        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

std::vector<int32_t> 		resolve_tree(t_tree_node* node, bool side)
{
	if (node == NULL)
	{
		// printf("null\n");
		return (std::vector<int32_t>());
	}
	if (node->operator_index <= 1)
	{
		// printf("last item\n");
		return (node->vector_set);
	}
	else
	{
		// printf("ope\n");
		std::vector<int32_t> b = resolve_tree(node->left, false);
		std::vector<int32_t> a = resolve_tree(node->right, true);
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

std::vector<int32_t> eval_set(std::string formula, std::vector<std::vector<int32_t> > sets)
{
	std::vector<t_tree_node*> boolean_stack;
	std::vector<t_operators> operators_stack;
	bool char_exist = false;
	t_tree_node	*tmp_left;
	t_tree_node	*tmp_right;
	t_tree_node	*tmp_node;

	// printf("formula : %s\n", formula.c_str());

	for (std::string::size_type i = 0; i < formula.size(); i++) {
		for (uint8_t current_index = 0;
			current_index < sizeof(g_operators) / sizeof(t_operators);
			current_index++)
		{

			if (formula[i] == g_operators[current_index].input_sign
				&& formula[i] == '!')
			{
				tmp_node = new t_tree_node(current_index);
				tmp_right = (boolean_stack).back();
				(boolean_stack).pop_back();
				tmp_node->right = tmp_right;
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
			}
		}
		if (formula[i] >= 'A' && formula[i] <= 'Z')
		{
			tmp_node = new t_tree_node(0);// comme si c'etait un 0 ou 1
			tmp_node->vector_set = sets[formula[i] - 'A'];
			// printf("index of a : %d", (int)(formula[i] - 'A'));
			// tmp_node->vector_set = std::vector<int32_t>(sets[1]);
			boolean_stack.push_back(tmp_node);
			char_exist = true;
		}
		if (!char_exist)
		{
			printf("This sign is not valid : '%c'\n", formula[i]);
			exit(0);
		}
	}
	// printf("\n");
	// printBT("", boolean_stack[0], false);
	// printf("\n");
	return (resolve_tree(boolean_stack[0], false));
	// return (std::vector<int32_t>());
}
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

typedef uint8_t(*t_operating)(uint8_t a, uint8_t b);




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
	return (!(a & !b));
}

uint8_t logical_equivalence_function(uint8_t a, uint8_t b)
{
	return (a == b);
}

typedef struct			s_operators
{
	char				input_sign;
	char				output_sign;
	t_operating			f_prop;
}						t_operators;

static const t_operators g_operators[] = {
	(t_operators){.input_sign = '0', .output_sign = '0', .f_prop = NULL},
	(t_operators){.input_sign = '1', .output_sign = '1', .f_prop = NULL},
	(t_operators){.input_sign = '~', .output_sign = '~', .f_prop = NULL},
	(t_operators){.input_sign = '!', .output_sign = '!', .f_prop = negation_function},
	(t_operators){.input_sign = '&', .output_sign = '&', .f_prop = conjunction_function},
	(t_operators){.input_sign = '|', .output_sign = '|', .f_prop = disjunction_function},
	(t_operators){.input_sign = '^', .output_sign = '^', .f_prop = exclusive_disjunction_function},
	(t_operators){.input_sign = '>', .output_sign = '>', .f_prop = material_condition_function},
	(t_operators){.input_sign = '=', .output_sign = '=', .f_prop = logical_equivalence_function},
};

typedef struct			s_tree_node
{
	uint8_t				operator_index;
	uint8_t				result;
	char				character;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	s_tree_node(uint8_t index)
	{
		operator_index = index;
		left = NULL;
		right = NULL;
		character = g_operators[index].input_sign;
		result = 0;
	}

}						t_tree_node;


uint8_t		resolve_tree(t_tree_node* node, bool side)
{
	if (node == NULL)
	{
		// printf("node is null\n");
		return (0);
	}
	// printf("w->%c\n", node->character);
	if (node->character == '>')
	{
		t_tree_node *tmp_right = node->right;
		t_tree_node *new_node = new t_tree_node(3);
		new_node->right = tmp_right;
		new_node->left = NULL;
		node->right = new_node;
		node->character = '|';
	}
	else if (node->character == '!' && node->right && node->right->character == '|' )
	{

		t_tree_node *tmp_left = node->right->left;
		t_tree_node *tmp_right = node->right->right;
		t_tree_node *new_left = new t_tree_node(3);
		t_tree_node *new_right = new t_tree_node(3);
		new_left->right = tmp_left;
		new_right->right = tmp_right;
		node->left = new_left;
		node->right = new_right;
		node->character = '&';
	}
	else if (node->character == '!' && node->right && node->right->character == '!' )
	{
		t_tree_node *tmp_right = node->right->right;
		node->character = tmp_right->character;
		node->left = tmp_right->left;
		node->right = tmp_right->right;
		node->operator_index = tmp_right->operator_index;
	}
	else if (node->character == '!' && node->right && node->right->character == '&' )
	{

		t_tree_node *tmp_left = node->right->left;
		t_tree_node *tmp_right = node->right->right;
		t_tree_node *new_left = new t_tree_node(3);
		t_tree_node *new_right = new t_tree_node(3);
		new_left->right = tmp_left;
		new_right->right = tmp_right;
		node->left = new_left;
		node->right = new_right;
		node->character = '|';
	}
	else if (node->character == '=')
	{

		t_tree_node *tmp_left = node->left;
		t_tree_node *tmp_right = node->right;
		node->left = new t_tree_node(5);
		node->right = new t_tree_node(5);
		node->right->right = new t_tree_node(3);
		node->left->left = new t_tree_node(3);
		node->right->right->right = tmp_right;
		node->left->left->right = tmp_left;

		node->right->left = tmp_left;
		node->left->right = tmp_right;
		node->character = '&';
	}
	else if (node->character == '^')
	{

		t_tree_node *tmp_left = node->left;
		t_tree_node *tmp_right = node->right;
		node->left = new t_tree_node(4);
		node->right = new t_tree_node(4);
		node->right->right = new t_tree_node(3);
		node->left->left = new t_tree_node(3);
		node->right->right->right = tmp_right;
		node->left->left->right = tmp_left;

		node->right->left = tmp_left;
		node->left->right = tmp_right;
		node->character = '|';
	}
	else if (node->character == '|' && node->right && node->right->character == '&')
	{

		t_tree_node *tmp_a = node->left;
		t_tree_node *tmp_b = node->right->left;
		t_tree_node *tmp_c = node->right->right;
		t_tree_node *new_left = new t_tree_node(5);
		t_tree_node *new_right = new t_tree_node(5);
		new_left->left = tmp_a;
		new_left->right = tmp_b;
		new_right->left = tmp_a;
		new_right->right = tmp_c;
		node->left = new_left;
		node->right = new_right;
		node->character = '&';
	}
	else if (node->character == '|' && node->left && node->left->character == '&')
	{

		t_tree_node *tmp_a = node->left->left;
		t_tree_node *tmp_b = node->left->right;
		t_tree_node *tmp_c = node->right;
		t_tree_node *new_left = new t_tree_node(5);
		t_tree_node *new_right = new t_tree_node(5);
		new_left->left = tmp_a;
		new_left->right = tmp_c;
		new_right->left = tmp_b;
		new_right->right = tmp_c;
		node->left = new_left;
		node->right = new_right;
		node->character = '&';
	}




	if (node->operator_index <= 2)
	{
		// printf("{%c}\n", node->character);
		// return (1);
		return (node->operator_index);
	}
	else
	{
		// printf("[%c]\n", node->character);
		resolve_tree(node->left, false);
		resolve_tree(node->right, true);
		return (0);
	}
}

void printBT(const std::string& prefix, const t_tree_node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->character << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}


void	visualize_tree(t_tree_node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		visualize_tree(node->left);
		visualize_tree(node->right);
		printf("%c", node->character );
	}
}

t_tree_node* create_tree_from_formula(std::string formula)
{
	std::vector<t_tree_node*> boolean_stack;
	std::vector<t_operators> operators_stack;
	bool char_exist = false;
	t_tree_node	*tmp_left;
	t_tree_node	*tmp_right;
	t_tree_node	*tmp_node;

	for (std::string::size_type i = 0; i < formula.size(); i++) {
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
			tmp_node = new t_tree_node(2);
			tmp_node->character = formula[i];
			boolean_stack.push_back(tmp_node);
			char_exist = true;
		}
		if (!char_exist)
		{
			printf("This sign is not valid : '%c'\n", formula[i]);
			exit(0);
		}
	}
	return (boolean_stack[0]);
}


void	conjunctive_normal_form(std::string formula)
{
	// printf("formula : %s\n", formula.c_str());
	t_tree_node* node = create_tree_from_formula(formula);
	// printBT("", node, false);
	resolve_tree(node, false);
	// printBT("", node, false);
	visualize_tree(node);
	printf("\n");

}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>


void visualize_stack(std::vector<bool> boolean_stack)
{
	printf("---\n");
	for(int i=boolean_stack.size()-1; i >= 0; i--){
		printf("-%s\n", boolean_stack[i] ? "true" : "false");
	}
	printf("---\n");
}


bool eval_formula(std::string formula)
{
	printf("%s\n",formula.c_str());
	std::vector<bool> boolean_stack;
    
	for (std::string::size_type i = 0; i < formula.size(); i++) {
        if (formula[i] == '0' || formula[i] == '1')
		{
			boolean_stack.push_back(formula[i] == '1' ? true : false);
		}
    }
	visualize_stack(boolean_stack);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
		eval_formula(str);
	}
}
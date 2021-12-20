#include <string>
#include <vector>


std::vector<int32_t> eval_set(std::string formula, std::vector<std::vector<int32_t> >);

int main(int argc, char **argv)
{


	if (argc == 2)
	{
		std::vector<std::vector<int32_t> > in;
	    std::vector<int32_t> out;

		// powerset_output = powerset(out);
		printf("input : \n");
		printf("[\n");


	    std::vector<int32_t> in_1;
		// in_1.push_back(0);
		in_1.push_back(2);
		// in_1.push_back(4);
		in.push_back(in_1);
	    std::vector<int32_t> in_2;
		// in_2.push_back(1);
		in_2.push_back(2);
		in.push_back(in_2);
	    std::vector<int32_t> in_3;
		in_3.push_back(0);
		in_3.push_back(5);
		in_3.push_back(6);
		in.push_back(in_3);

		char letter = 'A';
		for (std::vector<int32_t> &setofnu: in) {
				printf(" (%c)[", letter);
				for (int32_t &nu: setofnu) {
				printf("%d,", nu);
			}
			letter++;
			printf("]\n");
		}
		printf("]\n");
		std::string str(argv[1]);
		out = eval_set(str, in);


		printf("output : \n");
		printf("[");
		for (int32_t &s: out) {
			printf("%d, ", s);
    	}
		printf("]\n\n");
	}
	else
	{
		printf("Need at least one argument\n");
	}
	return (0);


	// if (argc == 2)
	// {
	// 	std::string str(argv[1]);
	// 	printf("%s\n", eval_formula(str) ? "true" : "false");
	// }
}
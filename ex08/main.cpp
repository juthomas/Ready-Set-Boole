#include <string>
#include <vector>
#include <array>

std::vector<std::vector<int32_t> > powerset(std::vector<int32_t> set);

// void printBits(size_t const size, void const * const ptr);

void tokenize(std::string const &str, const char delim,
            std::vector<int32_t> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back( atoi(str.substr(start, end - start).c_str()));
    }
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string str(argv[1]);
	    std::vector<int32_t> out;
		tokenize(str, ' ', out);

		printf("input : \n");
		printf("[");
		for (int32_t &s: out) {
			printf("%d, ", s);
    	}
		printf("]\n\n");


		std::vector<std::vector<int32_t> > powerset_output;
		powerset_output = powerset(out);
		printf("output : \n");
		printf("[\n");

		for (std::vector<int32_t> &setofnu: powerset_output) {
				printf(" [");
				for (int32_t &nu: setofnu) {
				printf("%d,", nu);
			}
			printf("]\n");
		}
		printf("]\n");


	}
}
#include <iostream>
#include "cTrie.h"

int main(void)
{
	cTrie dictionary;
	int distFromTrie = 0; //Number of symbols in request which was entered after "no hits"
	std::string request = "";

	dictionary.add("a");
	dictionary.add("aa");
	dictionary.add("aaa");
	dictionary.add("aaaa");

	char c;
	std::cin >> c;
	while(c != '$') //enter
	{
		bool backSpace = false;
		if (c == '-') //backspace
			backSpace = true;
		//if (c == '_') //space

		dictionary.processChar(c, backSpace, request, distFromTrie);
		std::cout << "\n";
		std::cin >> c;
	}
	return 0;
}
#include<iostream>

#include "trie.h"

int main() {
	Trie t;

	t.insertNgrams("3_gramhi", 2);

	int n = 2;
	int i = 0;
	while(i<5) {
		std::string str;
		std::getline(std::cin, str);
		if(str[str.length() - 1] == ' ') {
			str = str.substr(0, str.length() - 1);
		}

		std::set<std::string> suggestions = t.suggest(str);
		
		std::cout << "-----------------------------------SUGGESTIONS-------------------------------------\n";
	
		for(std::string str : suggestions) {
			std::cout << str << "   ";
		}
		std::cout << "\n-----------------------------------------------------------------------------------\n";
		
		i++;
	}

	return 0;
}

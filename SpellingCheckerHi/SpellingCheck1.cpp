#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <wchar.h>
#include <locale>

bool notValid(char c);
bool validWord(char c);
bool validAtVowel(char c);
void mapping(char *map, std::vector<char>& store);
void skipVowel(std::vector<char> str, std::wstring& temp);
void replaceWords(const std::wstring inp_word, const std::vector<wchar_t> map_file, const std::vector<wchar_t> dict ,std::vector<std::wstring>& container);
void searchInDict(std::wstring word, std::vector<wchar_t> dict, std::vector<std::wstring>& container);

int mystrcmp(std::wstring a, std::wstring b)
{

	int result=0, i=0;
	
//	std::wcout << b.size() << "\n" << std::endl;
//	std::wcout << a.size() << std::endl;
	if(a.length() == b.length())
	{
	while(i<a.length())
	{
	if(a[i]!=b[i])
		result = 1;
	i++;
	}
	}
	else
		result=1;
	

//	std::cout << result << std::endl;
	return result;
}


// Function to skip delimiter
bool notValid(wchar_t c)
{
	bool j = false;
	if(c == ' ' || c == '\n' || c == '\t')
		j = true;

	return j;
}

// Function to check if a character is a valid vowel
bool validWord(wchar_t c)
{
	bool j = false;
	int a = c;
	if(c >= 0x0900 && c<=0x097F || a == 45 || a == 46)
		j = true;

	return j;
}

// Function to check if a character is a valid vowel
bool validAtVowel(wchar_t c)
{
	bool j = false;
	if(c>=0x093A && c<=0x0956)
		j=true;

	return j;
}

/*
 * skip vowels and compare with base forms of the words in the dict.
 * while comparing with the words in the dict. start comparing only if first word & size of the base forms are same.
 */

// Function for Skipping Vowel from a word
void skipVowel(std::vector<wchar_t> str, std::wstring& temp)
{

	size_t i = 0;

	while (str[i] != L'\0')
	{
		if(validWord(str[i]))
		{
			if(validAtVowel(str[i]))
				i++;
			else
			{
				temp.push_back(str[i]);
				i++;
			}
		}
		else
		{
//			for(wchar_t c : str)
//				std::wcout << c ;
				
//			std::cout << std::endl;

			throw std::invalid_argument("Error: input word is not valid. Please input a valid bolnagari word.");
		}
	}

}


void replaceWords(const std::wstring inp_word, const std::vector<wchar_t> map_file, const std::vector<wchar_t> dict ,std::vector<std::wstring>& container)
{
	int i=0, map_file_index = 138;
	std::wstring temp;

	while(i<inp_word.length())
	{
		map_file_index = 138;
		temp = inp_word;
		wchar_t initial_letter = temp[i];

		while(map_file[map_file_index] != L'<')
		{
		if(validWord(map_file[map_file_index]) && map_file[map_file_index]!=initial_letter)
		{
			temp[i] = map_file[map_file_index];
			searchInDict(temp, dict, container);
		}
		map_file_index++;
		}
	i++;
	}
}


void searchInDict(const std::wstring word, const std::vector<wchar_t> dict, std::vector<std::wstring>& container)
{
	

	std::vector<wchar_t> tword;
//	tword.reserve(dict.size()); // Reserve space to avoid reallocations

	int i = 0;
//	int s = 0;

	while (dict[i]!=L'>')
	{
		tword.clear();
		while(dict[i]!=L';' && dict[i]!=L'>')
		{
			tword.push_back(dict[i]);
			i++;
		}
		
//		std::cout << s;
//		s++;

		tword.push_back(L'\0'); // Add null terminator

		std::wstring str(tword.begin(), tword.end());
		std::wstring temp;
		skipVowel(tword, temp);

		if (mystrcmp(word,temp)==0)
		{
			container.push_back(str);
			container.push_back(L"\n");
		}
		i++;
	}
//	container.push_back(L"\0");


}

// Function to store the file contents in a buffer
void mapping(const char* map, std::vector<wchar_t>& store)
{
	std::wifstream file(map); // Open file
	if(!file.is_open()) {
		std::cerr << "Unable to open file" << std::endl;
		throw std::runtime_error("Unable to open file"); // Throw an exception
	}

	wchar_t ch;
	while (file.get(ch))
	{ // Read characters from file
		if (!notValid(ch))
		{
			store.push_back(ch);
		}
	}

	if (file.bad())
	{ // Check for any errors during reading
		std::cerr << "Error reading file" << std::endl;
		throw std::runtime_error("Error reading file"); // Throw an exception
	}

	file.close();
}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("C.UTF-8"));
	// Check if the correct number of command-line arguments are provided
	if (argc < 4)
	{
		std::cerr << "input file not provided" << std::endl;
		return 1;
	}
	if(argc < 3)
	{
		std::cerr << "dict file not provided" << std::endl;
		return 1;
	}
	if (argc < 2)
	{
	std::cerr << "mapping file not provided" << std::endl;
	return 1;
	}
	
	std::vector<wchar_t> map_file;
	std::vector<wchar_t> dict;
	std::vector<wchar_t> input;
	std::vector<std::wstring> container;
	std::wstring inp_word;


	mapping(argv[1], map_file);
/*	int i=0;
	for(wchar_t c : map_file)
	{
		std::wcout << i << " : " << c << " | ";
		i++;
	}
	std::wcout << std::endl;
*/
	mapping(argv[2], dict);
	mapping(argv[3], input);
	
	
	if(dict.empty())
	{
		std::cout << "error : The dictionary file is empty" << std::endl;
		exit(-1);
	}


	if(input.empty())
	{
		std::cout << "error : The input file is empty" << std::endl;
		exit(-1);
	}
	

	for(wchar_t c : input)
		inp_word.push_back(c);

	std::vector<wchar_t> tword;
	int p=0,flag=0;
	while(dict[p]!=L'>' && flag!=1)
	{
		tword.clear();
		while(dict[p]!=L';' && dict[p]!=L'>')
		{
			tword.push_back(dict[p]);
			p++;
		}

		std::wstring dict_word(tword.begin(), tword.end());
		
		if(mystrcmp(inp_word,dict_word)==0)
		{
			flag=1;
		}
		p++;
	}

	if(flag==1)
		std::cout << "input word is correct" << std::endl;
	else
	{
		std::wcout << "input word is incorrect" << std::endl;
		inp_word.clear();
		skipVowel(input, inp_word);
		searchInDict(inp_word,dict,container);
		replaceWords(inp_word,map_file,dict,container);
	}	
	
	if(container.empty())
		std::wcout << "There were no suggestions" << std::endl;
	else
	{
		std::wcout << "Do you mean : " << std::endl;
		for(std::wstring c : container)
		{
			std::wcout << c ;
		}
		std::cout << std::endl;
	}


	return 0;
}

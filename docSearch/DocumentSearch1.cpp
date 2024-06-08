#include<iostream>
#include<vector>
#include<tuple>
#include<locale>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_set>
#include<algorithm>
#include<wchar.h>

int mystrcmp(std::wstring a, std::wstring b);
void mapping(const char* map, std::vector<std::wstring>& store);
bool stop_word(std::wstring word, std::vector<std::wstring> stopwords);
void tokenize(std::wstring ip, std::vector<std::wstring> stopwords, std::vector<std::wstring>& op);
void search_tokentable(std::wstring input, std::vector<std::wstring> tokens, std::vector<std::vector<int>> doc_freq, std::vector<int>& op);
int binary_search(int x, std::vector<int> set);
void intersection(std::vector<int> set1, std::vector<int> set2, std::vector<int> &intersec);

/*
bool invalid(wchar_t c)
{
        bool j = false;
        if(c == ' ' || c == '\n' || c == '\t')
                j = true;

        return j;
}


bool valid(wchar_t c)
{
        bool j = false;
        int a = c;
        if(c >= 0x0900 && c<=0x097F)
                j = true;

        return j;
}
*/

int mystrcmp(std::wstring a, std::wstring b)
{

        int result=0 , i=0 , flag=0;

        if(a.length() == b.length())
        {
        	while(i<a.length() && flag != 1)
        	{
        		if(a[i]!=b[i])
			{
                	result = 1;
			flag = 1;
			}
			i++;
        	}
        }
        else
                result=1;

        return result;
}


/*
// Function to store the file contents in a buffer
void mapping(const char* map, std::vector<std::wstring>& store)
{
        std::wifstream file(map); // Open file
        
	if(!file.is_open()) {
                std::cerr << "Unable to open file" << std::endl;
                throw std::runtime_error("Unable to open file"); // Throw an exception
        }

	wchar_t ch;
	std::wstring temp_word;
        
	while(file.get(ch))
	

	{ // Read characters from file

		while(ch!='\n' && ch!=WEOF)
		{
			if(!invalid(ch) && valid(ch))
			{
				temp_word.push_back(ch);
			}
			file.get(ch);
		}
		store.push_back(temp_word);
		temp_word.clear();

	}

	file.close();
}
*/

/*
bool stop_word(std::wstring word, std::vector<std::wstring> stopwords)
{
	bool op = false;

	for(std::wstring s : stopwords)
	{
		if(mystrcmp(word,s))
		{
			op = true;
			break;
		}
	}

	return op;
}
*/

void tokenize(std::wstring ip, std::vector<std::wstring> stopwords, std::vector<std::wstring>& op)
{
	int iter = 0;
	std::wstring temp;
	
	while(iter<ip.length())
//	for(wchar_t c : ip)
	{
		while( ip[iter]!= '\n' && ip[iter] != L' ' && ip[iter] != L';')
		{
			temp.push_back(ip[iter]);
			iter++;
		}
		
		for(std::wstring st : stopwords)
		{
			if(mystrcmp(temp,st)!=0)
			{
				op.push_back(temp);
			}
		}
		temp.clear();
		iter++;
	}
}


void search_tokentable(std::wstring input, std::vector<std::wstring> tokens, std::vector<std::vector<int>> doc_freq, std::vector<int>& op)
{
	int count=0;
	for(std::wstring t : tokens)
	{
		if(mystrcmp(input,t)==0)
			op = doc_freq[count];

		count++;
	}
}


int binary_search(int x, std::vector<int> set)
{
	int max = set.size()-1;
	int min = 0,flag = 0,mid;
	
	while(max>=min && flag!=1)
	{
		mid = (max+min)/2;

		if(x>set[mid])
			min = mid+1;
		else if(x<set[mid])
			max = mid-1;
		else
			flag = 1;
	}
	
	return flag;
}


void intersection(std::vector<int> set1, std::vector<int> set2, std::vector<int> &intersec)
{
	std::vector<int> big = set2;
	std::vector<int> small = set1;

	if(set1.size()>=set2.size())
	{
		big = set1;
		small = set2;
	}
	
	for(int ele : big)
	{
		int res = binary_search(ele,small);

//		std::wcout << "binary_search value for " << ele << " is " << res << std::endl;
		
		if(res==1)
		{
			intersec.push_back(ele);
		}
	}
}


int main()
{
	std::locale::global(std::locale("C.UTF-8"));

	std::vector<std::wstring> stopwords = {L"और",L"का",L"के",L"की",L"है",L"एक",L"में",L"हो",L"होता",L"था",L"या",L"इस",L"हैं",L"होते",L"तो",L"थे",L"जो",L"वह",L"यह",L"कि",L"इसके",L"उनके",L"उसके",L"अपने",L"होने",L"अगर",L"कब",L"कहाँ",L"कैसे",L"क्या",L"क्यों",L"कौन",L"जैसे",L"जहाँ",L"जितना",L"जितनी",L"जिसे",L"जिसके",L"जिसको",L"तब "};
//	mapping(argv[1],stopwords);

	std::wstring str = L"कारति";
	bool res = false;
	
	for(std::wstring st : stopwords)
	{
		if(mystrcmp(str,st)==0)
			res = true;
	}
	
	std::wcout << "stop word value is : " << res << std::endl;

	std::vector<std::wstring> docs = {L"भूषन भूषन हाे खिलाड़ी काला;",L"दीपक काला खिलाड़ी;" ,L"बिल्ली खिलाड़ी भूषन;"};

	std::wstring temp_word;

	std::vector<std::wstring> tokens;
	std::vector<std::vector<int>> doc_freq;
	int doc_index = 0;

	for(std::wstring c : docs)
	{
		temp_word.clear();
		int j=0;

		while(j<c.length())
		{
			if(c[j] == L' ' || c[j] == '\n' || c[j] == '\t' || c[j] == '\0' || c[j] == L';')
			{
				//			std::wcout << temp_word << std::endl;

				// flag for checking word present in tokens or not
				int index = 0, flag = 0;

				while(index<tokens.size())
				{ // If word already present in the tokens, only add the current document index to its doc_freq list
					if(mystrcmp(tokens[index],temp_word)==0)
					{
						int doc_flag = 0;
						for(int doc_no : doc_freq[index])
						{
							if(doc_no == doc_index)
							{
								doc_flag = 1;
								break;
							}
						}

						if(doc_flag == 0)
						{
							doc_freq[index].push_back(doc_index);
						}

						flag = 1;

					}
					index++;
				}


				if(index==tokens.size() && flag != 1)
				{ // otherwise add the word in the tokens with the currect index

	std::wcout << stop_word(temp_word,stopwords) << std::endl;
					if(!stop_word(temp_word,stopwords))
					{
	std::wcout << "here1" << std::endl;
						tokens.push_back(temp_word);
						std::vector<int> freq_list;
						freq_list.push_back(doc_index);
						doc_freq.push_back(freq_list);
					}
				}
				temp_word.clear();
			}
			else
			{
				temp_word.push_back(c[j]);
			}
			j++;
		}
		doc_index++;
	}

	int token_iter = 0;
	for(const auto& inner_vec : doc_freq)
	{
		std::wcout << L"freq of token " << tokens[token_iter] << " : ";
		for(int val : inner_vec)
		{
			std::wcout << val << " " << std::endl;
		}
		std::cout << std::endl;
		token_iter++;
	}



	std::wstring input = L"भूषन हाे खिलाड़ी;";
	std::vector<std::wstring> ip;

	tokenize(input,stopwords,ip);

	int i = 0;
	std::vector<int> set1;

	//	std::wcout << ip.size()  << std::endl;

	if(ip.size()>=2)
	{
		search_tokentable(ip[i], tokens, doc_freq, set1);
		i++;
		std::vector<int> set2;
		std::vector<int> intersec;

		//	for(std::wstring ele : ip)
		while(i<ip.size())
		{
			if(!set1.empty() || !set2.empty())
			{
				search_tokentable(ip[i], tokens, doc_freq, set2);

				intersection(set1,set2,intersec);

				set1 = intersec;

				i++;
			}
			else
			{
				std::wcout << "no documents found" << std::endl;
			}
		}
		for(int iter : intersec)
			std::wcout << "document no. : "  << iter <<  std::endl;

	}

	else
	{
		search_tokentable(ip[i],tokens,doc_freq,set1);
		for(int iter : set1)
			std::wcout << "document no. : " << iter << std::endl;
	}
}

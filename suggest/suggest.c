#include<stdio.h>
#include<locale.h>
#include<wchar.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

int mystrcmp(wchar_t *a,wchar_t *b);
int findbound(wchar_t *ch);
int isValidAtVowel(wchar_t *ca, wchar_t *itrans);
void skipVowel(wchar_t *itrans,wchar_t *str, wchar_t *temp);
void mapping(char *map, wchar_t *itrans);
int isnotvalid(wchar_t ch);


int mystrcmp(wchar_t *a,wchar_t *b)
{
	int i=0;
	int f=0;
	while(a[i]!= '\0' && f==0)
	{
		if(a[i]!=b[i])
		{
			f=1;
		}
		i++;
	}
	return f;
}

int findbound(wchar_t *ch)
{
	int i=0;
	
	while(ch[i]!='@')
	{
		i++;
	}

	while(ch[i]!='>')
	{
		i++;
	}

	return i;
}

int isValidWord(wchar_t x)
{
	int op = 1;
	if( x>=0x0900 && x<=0x097F )
		op = 0;

	return op;
}

int isValidAtVowel(wchar_t *ca, wchar_t *itrans)
{
	int bound=findbound(itrans);
	int i=bound+1;
	int j=0;
	int f=0;
	int cmp=-1;
	int count=0;
	wchar_t charr[20];
	
	while(count!=1 && f==0)
	{
		if(itrans[i]==L'<')
		{
			count++;
		}

		if(itrans[i]>128)
		{
			j=0;
			
			charr[j] = itrans[i];
			j++;
			i++;
			charr[j]=L'\0';
			cmp=mystrcmp(ca,charr);
			if(cmp==0)
			{
				f=1;
			}
		}
		i++;
	}

	return f;
}

int isnotvalid(wchar_t ch)
{
	int i=0;
	if(ch == ' ' || ch == '\t' || ch == '\n')
	{
		i=1;
	}
	
	return i;
}

/*
 * itrans : mapping buffer.
 * str : input string to skip vowel from.
 * temp : temp string to store the word after vowel skip.
*/
void skipVowel(wchar_t *itrans, wchar_t *str, wchar_t *temp)
{
	int i=0,j=0,k=0;
	char ch;
	wchar_t te[2];
	
	while(str[i]!='\0')
	{
	if(isValidWord(str[i])==0)
	{
		j=0;
		te[j] = str[i];

		j++;
		te[j] = '\0';

		if(isValidAtVowel(te,itrans))
		{
			i++;
		}
		else
		{
			temp[k] = str[i];
			i++;
			k++;
		}
	}
	else
	{
		printf("Error : input word is not Valid. Please input a valid bolnagari word.\n");
		exit(1);
	}
	}
	temp[k] = L'\0';
}

void mapping(char *map, wchar_t *itrans)
{
	FILE *file = fopen(map,"r");
	int errno=0;

	if(file==NULL)
	{
		errno=1;
		fprintf(stderr,"%s file does not exits. Ensure that given mapping file is made correctly.\n",map);
	}

	wchar_t ch;
	int i=0;

	while((ch = fgetwc(file))!=WEOF && errno==0)
	{
		if(!isnotvalid(ch))
		{	
			itrans[i]=ch;
			i++;
		}
	}

	itrans[i]=L'\0';
	fclose(file);
}

// This function takes input word with skipped vowels
// takes dictionary, 
// takes one word at a time, 
// skips its vowels and 
// compares each word of the dictionary with the target word.  

void searchInDict(wchar_t *word, wchar_t *dict, wchar_t *itrans)
{
	wchar_t temp[20];
	int j, i=0;

	while(dict[i]!=L'\0')
	{
		j=0;
		while(dict[i]!=L';')
		{
			temp[j] = dict[i];
			i++;
			j++;
		}
		temp[j] = L'\0';

		wchar_t ret[40];

		skipVowel(itrans,temp,ret);


		int k=0;
		int cmp = mystrcmp(word, ret);
/*		if(cmp==0)
		{
			while(temp[k]!=L'\0')
			{
				printf(" %lc ",temp[k]);
				k++;
			}
			printf("\n");
		}
*/		
		if(cmp==0)
		{
			printf(" %ls ",temp);
			printf("\n");
		}

		i++;
	}	
}

int main(int argc, char *argv[])
{

	setlocale(LC_ALL,"");
	
	if(argc<4)
	{
		fprintf(stderr,"input not provided");
	}
	if(argc<3)
	{
		fprintf(stderr,"dictionary not provided");
	}

	if(argc<2)
	{
		fprintf(stderr,"map file not provided");
	}

	wchar_t itrans[800];
	wchar_t str[20];
	wchar_t temp[40];
	wchar_t dict[1000];

	mapping(argv[1],itrans);
	mapping(argv[3],str);
	mapping(argv[2],dict);


	skipVowel(itrans,str,temp);
	searchInDict(temp,dict,itrans);

}

#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>

int isnotvalid(wchar_t ch)
{
	int i=0;
	if(ch == ' ' || ch == '\t' || ch == '\n')
	{
		i=1;
	}
	
	return i;
}

//void mapping(char *map, wchar_t *itrans,int *count)
void mapping(char *map, wchar_t *itrans)
{
	setlocale(LC_ALL,"");
	FILE *file = fopen(map,"r");
	int errno=0;
//	(*count) = 0;

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
//			(*count)++;
			i++;
		}
	}

	itrans[i]=L'\0';
	fclose(file);
}

int main(int argc, char *argv[])
{
//	setlocale(LC_ALL,"");
	wchar_t ar[800];
	int count;
//	mapping (argv[1], ar, &count);
	mapping (argv[1], ar);

	int i=0;
	while(ar[i]!=L'\0')
	{
		printf(" %lc ,",ar[i]);
		i++;
	}

	int a = L'अ';
	printf("\n%d\n",a);
}

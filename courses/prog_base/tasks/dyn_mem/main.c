#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	char * str = NULL;
	str = (char*)malloc(sizeof(char) * 100);
	if (NULL == str)
		return 1;
	int * p = NULL;
	p = (int*)malloc(sizeof(int));
	if (NULL == p)
		return 1;
	int * i = NULL;
	i = (int*)malloc(sizeof(int));
	if (NULL == i)
		return 1;
	*p = 0;
	puts("enter string");
	gets(str);
	
	for (*i = 0; *i < strlen(str); (*i)++)
		if(str[*i] != ' ' && str[*i] != '\t'){
			*p = (int)str[*i];
			break;
		}
	for (*i = strlen(str) - 1; *i > 0; (*i)--)
		if(str[*i] != ' ' && str[*i] != '\t')
		{
			(*p) += (int)str[*i];
			break;
		}
	printf("sum = %i", *p);
	free(str);
	free(p);
	free(i);
	return 0;
}

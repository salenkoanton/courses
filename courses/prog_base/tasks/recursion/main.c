#include <stdio.h>
#include <string.h>
int rec(char * str, int i, int stPos);
int main(void)
{
	char str[100];
	printf("enter string\n");
	gets(str);
	if (rec(str, 0, 0) == -1)
		printf("wrong string, there is no any number");
	else
		printf("%i", rec(str, 0, 0) - rec(str, strlen(str), 1));
	return 0;
}

int rec(char * str, int i, int stPos)
{
	int a;
	if (stPos == 0)
		if (str[i] > 47 && str[i] < 58)
			return (int)str[i];
		else
			if (i == strlen(str))
				return -1;
			else
				a = rec(str, i + 1, 0);
	else
		if (str[i] > 47 && str[i] < 58)
			return (int)str[i];
		else 
			if (i == 0)
				return -1;
			else
				a = rec(str, i - 1, 1);
	return a;
}
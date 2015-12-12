#include <stdio.h>
#include <conio.h>
void strMake(char * str_in, char * str_out);
int main(int argc, char ** args)
{
	char str[120] = "";
	//printf("enter input file name\n");
	//gets(str);
	FILE * fr = NULL;
	FILE * fp = NULL;
	fr = fopen(args[1], "r");
	fp = fopen(args[2], "w");
	if (NULL == fr)
		return 1;
	if (NULL == fp)
		return 1;
	while (feof(fr) == 0)
	{
	char str1[20] = " ";
	strMake(str, str1);
	fgets(str, 120, fr);
	
	//printf("enter input file name\n");
	//gets(str1);
	
	while (str1[0] != '\0' || str[0] != '\0')
	{
		strMake(str, str1);
		fprintf(fp, "%s\n", str1);
	}
	fprintf(fp, "\n");
	}
	fclose(fp);
	
	fclose(fr);
	return 0;
}

void strMake(char * str_in, char * str_out)
{
	int i = 0;
	while ((str_in[0] <= 'Z' && str_in[0] >= 'A') || (str_in[0] <= 'z' && str_in[0] >= 'a')){
		str_out[i++] = str_in[0];
		for (int j = 0; str_in[j] != '\0'; j++)
			str_in[j] = str_in[j + 1];
	}
	for (int j = 0; str_in[j] != '\0'; j++)
			str_in[j] = str_in[j + 1];
	str_out[i] = '\0';
}
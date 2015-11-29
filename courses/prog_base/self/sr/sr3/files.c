#include <stdlib.h>
#include <stdio.h>
int main (void)
{
	size_t size;
	unsigned len;
	printf("enter number of files");
	if (!scanf("%u", &size))
		return 1;
	FILE * fp[size];
	char nameFiles[size][30];
	char textFiles[size][1000];
	unsigned lenMas[size];
	printf("enter files names");
	for (unsigned i = 0; i < size; i++)
		scanf("%s", &nameFiles[i]);
	for (unsigned i = 0; i < size; i++)
	{
		fp[i] = fopen(nameFiles[i], "r");
		if (fp != NULL)
		{
			len = 0;
			//fgets(textFiles[i], 1000, fp[i]);
			while (feof(fp[i]) != 1 && /*textFiles[i][len] != EOF &&*/  len < 1000)
			{
				fscanf(fp[i], "%c", &textFiles[i][len]);
				len++;
			}
			lenMas[i] = len;
			puts(textFiles[i]);
			
			//while (textFiles[i][len] != '\0')
				//len++;
			printf("len of %u file = %u\n", i, len);
		}
		fclose (fp[i]);
	}
	
	unsigned maxLen = 0;
	unsigned minLen = 1000;
	unsigned indmin, indmax;
	for (unsigned i = 0; i < size; i++)
	{
		if (minLen > lenMas[i])
		{
			indmin = i;
			minLen = lenMas[i];
		}
		if (maxLen < lenMas[i])
		{
			indmax = i;
			maxLen = lenMas[i];
		}
	}
	for (unsigned i = 0; i < size; i++)
	{
		if (i == indmax)
			i = indmin;
		else
		if (i == indmin)
			i = indmax;
		
		fp[i] = fopen(nameFiles[i], "r");
		if (fp != NULL)
		{
			len = 0;
			while (feof(fp[i]) != 1 && /*textFiles[i][len] != EOF &&*/  len < 1000)
			{
				fscanf(fp[i], "%c", &textFiles[i][len]);
				len++;
			}
			lenMas[i] = len;
			puts(textFiles[i]);
			
			//while (textFiles[i][len] != '\0')
				//len++;
			printf("len of %u file = %u\n", i, len);
		}
		fclose (fp[i]);
		if (i == indmax)
			i = indmin;
		else
		if (i == indmin)
			i = indmax;
	}
	
	
	
	
	
	
	return EXIT_SUCCESS;
}

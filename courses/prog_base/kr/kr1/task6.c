#include <stdio.h>
#include <string.h>
int _value(char * str);
int _name(char * str);
int main (void)
{
	char str[14];
	gets(str);
	int i = 0;
	int err = 0;
	char * str1 = strtok(str, " ");
	while (str1 != NULL)
	{
		switch (i)
		{
			case 0: if (str1 == "int" || str1 == "long" || str1 == "double" || str1 == "float")
				err = 0;
			else 
				err = 1;
			break;
			case 1: if (strchr(str1, '=') != NULL) 
			{
				err = _name(strtok(str1, "="));
				str1 = strchr(str1, '=');
				err = _value(str1);
			}
			else 
				err = _name(str1);
			break;
			case 2: break; 
			case 3: break;
			default : err = 1; break;
		}
		i++;
	}
	
	return 0;
}
int _name(char * str)
{
	int i, err = 0, flag = 1, flag1 = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ' && flag == 1)
		{
			continue;
		}
		if (str[i] == ' ' && flag1 == 1)
		{
			continue;
		}
		if (flag == 1)
			if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')) && flag1 == 0)
				flag = 0;
			else 
				err = 1;
		else 
			if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')) && flag1 == 0)
				flag = 0;
			else 
				if (str[i] == ' ')
					flag = 1;
				else
					err = 1;
	}
	return err;	
}
int _value(char * str)
{
	int i, err;
	for (i = 1; str[i] != '\0'; i++)
		if (str[i] > 9 || str [i] < 0)
			err = 0;
	return err;		
}
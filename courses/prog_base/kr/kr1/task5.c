#include <stdio.h>
int main(void)
{
	char str[20] = "  _OvrInitEms  ";
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

	if (err == 0)
		puts(str);
	else 
		puts("error");
	return 0;	
}
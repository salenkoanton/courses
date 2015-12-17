#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
	int l = 0;
	int i = 0;
	int j = 0;
	int bool = 0;
	l = strlen(number);
	if (strcmp(number, "0") == 0)
		return number;
	while (i < l){
		if (number[i] == '.') 
			bool = 1;
		if (number[i] > 47  && number[i] < 58) {
			if (number[i] - 47 > sourceBase) return "\0";
		}
		else {
			if (number[i] > 64 && number[i] < 91) {
				if (number[i] - 55 > sourceBase) return "\0";
			}
			else {
				if (number[i] != '.') return "\0";
			}
		}
		i++;
	}
	i = 0;
	double a = 0;
	if (bool == 1){
		while (number[j] != '.'){
			j++;
		}
	}
	else {
		j = l;
	}
	while (l >= i){		
		if ((number[i]) > 47 && (number[i]) < 58) a+= ((number[i] - 48) * pow(sourceBase, j - i - 1));
		if ((number[i]) > 64 && (number[i]) < 91) a+= ((number[i] - 55) * pow(sourceBase, j - i - 1));
		if (number[i] == 46) j++;
		i++;	
	}
	i= -1;
	int b;
	long v = 0;
	while (a >= v){
		v++;
	}
	v--;
	a-= v; 
	while (v >= 1){
		i++;
		b = v % destBase;
		if (b < 10) {number[i] = b + 48;}
		else {number[i] = b + 55;}
		v = (v - b) / destBase;	
		number[i+1] = '\0';
	}
	l = 0; 
	char c;
	while(l <= (i / 2)){
		c = number[l];
		number[l] = number[i - l];
		number[i - l] = c;
		l++;
	}
	i++;
	if (bool == 1){
		number[i] = '.';
	j = 0;
	while (a > 0 && j < 50){
		j++;
		i++;
		v = 0;
		a*= destBase;
		do {
			v++;
		} while (a - v > -pow(2, -12));
		v--;
		if (v < 10) {number[i] = v + 48;}
		else {number[i] = v + 55;}
		a-= v;
	}
	}
	number[i + 1]='\0';
	return number;
}
/*int main(void)
{
	unsigned int c;
	char* a;
	a = malloc(sizeof(char)*256);
	unsigned int b;
	scanf("%s",a);
	scanf("%d",&b);
	scanf("%d",&c);
	a=ns_convert(a,b,c);
	printf("%s \n",a);
	free(a);
	return 0;
}*/
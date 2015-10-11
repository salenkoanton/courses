#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double long2double(long long);
int main (void)
{
	long long a =  pow (2, 63) - 1;
	double b = long2double(a);
	printf("%lf", b);
	getchar();
	return 0;
	
}
double long2double(long long a)
{
	int i, e = 0, arr[64];
	double b = 1;
	
	for (i = 0; i < 64 ; i++)
	{
		arr[i] = ((1LL << i) & a) >> i;
	}
	for (i = 51; i > -1; i--)
	{
		if (arr[i] == 1)
			b += pow(2, i - 52);
	}
	if (arr[63] == -1) 
		b = -b;
	a = 0;
	for (i = 0; i < 64 ; i++)
		if (arr[i] == 1) 
			e == 1;
	if ((e == 0) && (arr[63] == 0))
		return 0;
	if ((e == 0) && (arr[63] == -1))
		
	for (i = 52; i < 63; i++)
		if (arr[i] == 1)
			a += pow(2, i - 52);
	if (a == 0)
		return b - 1;
	printf(" %li ", a);
	b *= pow(2, (a - 1023));
	if (a == 2047)
	{
		if (b == 0)
			if (arr[63] == -1)
				return -INFINITY;
			else 
				return INFINITY;
		else 
			return NAN;
				
	}
	return b;
}
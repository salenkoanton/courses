#include <stdio.h>
#include <math.h>
/*double calc(int n, int m);
int main(void)
{
	int i, j;
	scanf ("%d", &i);
	scanf ("%d", &j);
	double d = calc(i, j);
	printf("%lf", d);
	return 0;
}*/
double calc(int n, int m)
{
	int i, j;
	double d = 0, g = 0;
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < m + 1; j++)
			g += 1 + i / pow(2.1, j);
		d += g;
	}
	return d;
}
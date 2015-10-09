#include <math.h>
double calc (double x, double y, double z)
{
	double a = 0;
	if ((x <= y) || (z == 0) || ( x <= 0 ) || (sin(x) == 0) || (x - y == 0)) 
		return NAN;
	else 
	{
		a = pow(x, y + 1) / (pow(x - y, 1 / z)) + y / (3 * fabs(x + y)) + sqrt(fabs(cos(y) / sin(x) + 1));
		return a;
	}
}
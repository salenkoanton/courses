#include <math.h>
int satisfies(int a, int b, int c)
{
	int modmin, max, min, sum2;
	if (a < 0 && b < 0 && c < 0){
		if (b <= a && b <= c){ 
			modmin = abs(b);
			sum2 = a + c;
		}
		if (c <= b && c <= a){
			modmin = abs(c);
			sum2 = a + b;
		}
		if (a <= b && a <= c){
			modmin = abs(a);
			sum2 = b + c;
		}
		if (sum2 < -256 && modmin < 256 && (modmin == 1 || modmin == 2 || modmin == 4 || modmin == 8 || modmin == 16 || modmin == 32 || modmin == 64 || modmin == 128)) 
			return 1;
		else{
			if (abs(sum2) - modmin < 16 || abs(sum2) < 16) 
				return 1;
			else 
				return 0;
		}
	}
	else 
	{
		if(a >= 0 && b >= 0 && c >= 0){
			if (a > c){
			min = c;
			max = a;
			if (max < b)
				max = b;
			else if (b < min)
				min = b;
			}
			else{
				min = a; 
				max = c;
				if (max < b)
					max = b;
				else if (min > b)
					min = b;
			
			}
			if (min * max < 256) //return (min * max < 256);
				return 1;
			else 
				return 0;
		}
		else
		{
			if (a >= 0 && b >= 0) {
				if (c > -256) 
					return 1;
				else 
					return 0;
			} 
			else{
			if (a >= 0 && c >= 0){
				if (b > -256) 
					return 1;
				else 
					return 0;
			}
			else{
			if (b >= 0 && c >= 0){
				if (a > -256) 
					return 1;
				else 
					return 0;
			
			}
			else{
				if (a >= 0) {
					if ((b + c) * 3 > -256)
						return 1;
					else
						return 0;
				}
				if (b >= 0) {
					if ((a + c) * 3 > -256)
						return 1;
					else
						return 0;
				}
				if (c >= 0) {
					if ((b + a) * 3 > -256)
						return 1;
					else
						return 0;
				}
				
			}
			}
			}
			
			
		}
	
	//min = (a < c)?a:c;

}
}
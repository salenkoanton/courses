#include <math.h>
#define PI 3.141592654
int exec(int op, int a, int b){
	int result;
	if (op < 0) {
		op = -op;
		result = a;
		a = b;
		b = result;
	}
	switch (op) {
		case 0: result = -a; break;
		case 1: result = a + b; break;
		case 2: result = a - b; break;
		case 3: result = a * b; break;
		case 4: result = a / b; break;
		case 5: result = abs(a); break;
		case 6: result = pow(a, b); break;
		case 7: case 13: case 77: result = a % b; break;
		case 8: if (a > b) result = a; else result = b; break;
		case 9: if (a < b) result = a; else result = b; break;
		case 10: switch (abs(b) % 8){
			case 1: result = 1; break;
			case 2: result = 2; break;
			case 3: result = 4; break;
			case 4: result = 8; break;
			case 5: result = 16; break;
			case 6: result = 4; break;
			case 7: result = 8; break;
			case 0: result = 1; break;
		} result *= abs(a); break;
		case 11: result = 3 * PI * cos(2 * a * b) / a; break;
		default : if (op < 100) result = (op % abs(a + 1)) + (op % abs(b + 1)); else result = -1; break;
	}
	return result;
}
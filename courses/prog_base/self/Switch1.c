#include <stdio.h>
int main(){
	int code,h,m;
	float b;
	scanf ("%d %d %d", &h, &m, &code);
	switch (code){
		case 32: {b=(h*60+m)*0.95; break;}
		case 44: {b=(h*60+m)*0.77; break;}
		
		case 62: {b=(h*60+m)*0.8; break;}
		case 692: {b=(h*60+m)*1.5; break;}
		case 697: {b=(h*60+m)*1.5; break;}
		default: {if (code<1000 && code>9)
				b=(h*60+m);
			else 
				return 1;
			break;

			}
	}
	printf ("%f", b);
	return 0;
}
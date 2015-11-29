#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float a[1000][1000];
 //= { 5,4,3,2,1,7,6,5,8,7,5,4,6,5,6,4,4,4,4,4,3,5,4,6,5 };
float b[1000][1000]; // масиви розміром 1000*1000 тому що не знаю як безрозмірний зробити (варіант зробити вказівник вказівкика), а практично >200 нікому не потрібно
float c[1000][1000];
void inverse_matrix();
void fillArr(float arr[],int n);
int main()
{
	srand(time(NULL));
	//fillArr(a, n);
	inverse_matrix();
	return 0;
}
void inverse_matrix()
{
	int i, j, k, n, v; // i - номер рядка, j - номер стовпця, k - потрібно щоб обнулити всі значення у початковій матриці, n - розмір квадратної матриці
	float d, det = 1; // d - число яке буде рівне відношенню значення елемента що ми обнулямо до значення елемента що стоїть на діагоналі
	printf("Enter name of file with matrix\n");
	char txt[100];
	gets(txt);
	printf("Rang of input matrix = ");
	scanf("%i", &n); 
	FILE * fr = NULL;
	fr = fopen(txt, "r");
	if (fr == NULL)
		return;
	FILE * fw = NULL;
	fw = fopen("rezMat.txt", "w");
	if (fw == NULL)
		return;
	float got[1000];
	//for(i = 0; i < n; i++)
	//	for (j = 0; j < n; j++)
	//		a[i][j] = rand() % 4000 - 2000;
	for (i = 0; i < n; i++){
		//printf("row %d :\n", i + 1);
		for (j = 0; j < n; j++)
		{
			//printf("A[%d,%d] = ", i + 1, j + 1);
			fscanf(fr, "%f", &a[i][j]);
			c[i][j] = a[i][j];
		}
		fscanf(fr, "%f", &got[i]);
	}
	
	/*for (i = 0; i < n; i++){
		printf("B[%d] = ", i + 1);
		
	}*/
	fprintf(fw, "Input matrix :");
	for (i = 0; i < n; i++){
		fprintf(fw, "\n");
		for (j = 0; j < n; j++)
			if (j < n - 1)
				fprintf(fw, " %11.4f * x%d +", a[i][j], j + 1); // це виведення початкової матриці, лише для оформлення
			else 
				fprintf(fw, " %11.4f * x%d ", a[i][j], j + 1); 
		fprintf(fw, "= %f", got[i]);
	}
		fprintf(fw, "\n---------------------------------------------------------------------------\n");
	for (i = 0; i < n; i++)
		b[i][i] = 1; // робимо одиничну матрицю
	for (i = 1; i < n; i++){
		fputs("\n------------------------------\n", fw);
		for (j = 0; j < i; j++)
			{
				for (v = 0; v < n; v++)
					fprintf(fw, "%11.4f", a[j][v]);
				fprintf (fw, " | %11.4f", got[j]);
				fputs("\n", fw);
			}
		for (k = 0; k < n - i; k++){
			d = a[i + k][i - 1] / a[i - 1][i - 1];
			for (j = 0; j < n; j++){
				a[i + k][j] -= a[i - 1][j] * d; // віднімаємо від рядка [i + k] рядок [i - 1]
				b[i + k][j] -= b[i - 1][j] * d; // аналогічно із одиничною матрицею	
				if (j < i)
					a[i + k][j] = 0;
				fprintf(fw, "%11.4f", a[i + k][j]);
			}

			got[i + k] -= got[i - 1] * d;
			fprintf (fw, " | %11.4f", got[i + k]);
			if (d > 0)
				fprintf (fw, " | (a[%i] - %f * a[%i])\n", k + i + 1, d, i);
			else
				fprintf (fw, " | (a[%i] + %f * a[%i])\n", k + i + 1, -d, i);
			
		}		
	}	// після цього блоку початкова матриця уже перетворилася на нижню трикутну
	//знайдемо детермінант матриці
	for (i = 0; i < n; i++)
		det *= a[i][i];
	fprintf(fw, "\nDeterminant of input matrix = %f", det);
	fprintf(fw, "\n---------------------------------------------------------------------------");
	for (i = n - 2; i >= 0; i--){
		fputs("\n------------------------------\n", fw);
		
		for (k = i; k >= 0; k--){
			d = a[i - k][i + 1] / a[i + 1][i + 1];
			for (j = 0; j < n; j++){
				a[i - k][j] -= a[i + 1][j] * d;
				b[i - k][j] -= b[i + 1][j] * d;
				if (j > i)
					a[i - k][j] = 0;
				fprintf(fw, "%11.4f", a[i - k][j]);
			}
			got[i - k] -= got[i + 1] * d;
			fprintf (fw, " | %11.4f", got[i - k]);
			if (d > 0)
				fprintf (fw, " | (a[%i] - %f * a[%i])\n", i - k + 1, d, i + 2);
			else 
				fprintf (fw, " | (a[%i] + %f * a[%i])\n", i - k + 1, -d, i + 2);
		}
		for (j = i + 1; j < n; j++)
			{
				for (v = 0; v < n; v++)
					fprintf(fw, "%11.4f", a[j][v]);
				fprintf (fw, " | %11.4f", got[j]);
				fputs("\n", fw);
			}
	} // а після цього на діагональну
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			b[i][j] /= a[i][i]; // оскільки в нас початкова матриця діагональна але не одинична то ми кожен рядок матриці b ділимо на значення що стоїть на діаоналі в матриці а
		got[i] /= a[i][i];
	}
	fprintf(fw, "\nDiagonal matrix :");
	for (i = 0; i < n; i++){
		fprintf(fw, "\n");
		for (j = 0; j < n; j++)
			fprintf(fw, " %11.4f ", a[i][j]); // це виведення початкової матриці, якщо у ній діагональне значення == 0 або == INF то ця матриця вироджена і оберненої не існує
	}
	fprintf(fw, "\n---------------------------------------------------------------------------");
	fprintf(fw, "\nInversed matrix :");
	for (i = 0; i < n; i++){
		fprintf(fw, "\n");
		for (j = 0; j < n; j++)
			fprintf(fw, " %11.4f ", b[i][j]);
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++){
			a[i][j] = 0;
			for (k = 0; k < n; k++)
				a[i][j] += (b[i][k] * c[k][j]);
		}
	fprintf(fw, "\n---------------------------------------------------------------------------");
	fprintf(fw, "\nChecking:");	
	for (i = 0; i < n; i++){
		fprintf(fw, "\n");
		for (j = 0; j < n; j++)
			fprintf(fw, " %11.4f ", a[i][j]);
	}
	fprintf(fw, "\n-----------------------------------------");
	for (i = 0; i < n; i++){
		fprintf(fw, "\nx%d = %11.4f ", i + 1, got[i]);
	}
	printf("\nYou will find results in file rezMat.txt");
	getchar();
	fclose(fw);
	fclose(fr);
}

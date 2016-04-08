#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*void rotateCW270(int mat[4][4]);	
void flipV(int mat[4][4]);	
void transposMain(int mat[4][4]);
void printMatrix(int mat[4][4]);
void ret_arr(int mat[4][4], int mat1[4][4]);
void fillRand(int mat[4][4], int mat1[4][4]);
int main (void)
{
	
	int arr[4][4];
	int brr[4][4];
	
	fillRand(arr, brr);
	printMatrix(arr);
	rotateCW270(arr);
	printMatrix(arr);
	ret_arr(arr, brr);
	flipV(arr);
	printMatrix(arr);
	ret_arr(arr, brr);
	transposMain(arr);
	printMatrix(arr);
	return 0;
}
*/
void rotateCW270(int mat[4][4])
{
	int c, i, j, n = 4;
	for (i = 0; i < (n + 1) / 2; i++)
		for (j = 0; j < (n + 1) / 2; j++)
		{
			c = mat[i][j];
			mat [i][j] = mat [j][n - 1 - i];
			mat [j][n - 1 - i] = mat [n - 1 - i][n - 1 - j];
			mat [n - 1 - i][n - 1 - j] = mat[n - 1 - j][i];
			mat[n - 1 - j][i] = c;
		}
}

void flipV(int mat[4][4])
{
	int i, j, c, n = 4;
	for (i = 0; i < (n + 1) / 2; i++)
		for (j = 0; j < n; j++)
		{
			c = mat[i][j];
			mat[i][j] = mat[n - 1 - i][j];
			mat[n - 1 - i][j] = c;
		}
}

void transposMain(int mat[4][4])
{
	rotateCW270(mat);
	flipV(mat);
}
/*void printMatrix(int mat[4][4]) {
    int i, j;
    int n = 4;
    printf("{ ");
    for (i = 0; i < n; i++) {
        printf("{");
        for (j = 0; j < n; j++) {
            printf("%5i, ", mat[i][j]);
        }
        printf("}");
        if ( i < n - 1)
            printf("\n  ");
    }
    printf(" };\n");
	printf("-----------------------------------------------\n");
}*/
void fillRand(int mat[4][4]/*, int mat1[4][4]*/)
{
	srand (time(NULL));
	int i, j, n = 4;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			mat[i][j] = ((int)rand() % 1999) - 999;
			/*mat1[i][j] = mat[i][j];*/
		}
}/*
void ret_arr(int mat[4][4], int mat1[4][4])
{
	int i, j, n = 4;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			mat[i][j] = mat1[i][j];
}
*/
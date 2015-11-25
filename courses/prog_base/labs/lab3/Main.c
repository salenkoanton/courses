#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
void rotateCW270(size_t n, int mat[n][n]);
void nullMatrix(size_t size, int mat[size][size]);
void fillRand(size_t size, int mat[size][size], int min, int max);
int changeElem(size_t size, int mat[size][size], unsigned row, unsigned colone, int elem);
long long sumRow (size_t size, int mat[size][size], unsigned row, int * status);
void flipV(size_t size, int mat[size][size]);
long long sumDiagUp (size_t size, int mat[size][size]);
void moveMaxToMinFirst (size_t size, int mat[size][size]);
void moveMaxToMinLast (size_t size, int mat[size][size]);
void transpArr(size_t size, int arr[size][size]);
void moveMaxRowToMin (size_t size, int mat[size][size]);
double meanValue(size_t size, int mat[size][size]);
void buildInterfase(HANDLE hConsole, char Interface[12][80]);
void cleenScreen(HANDLE hConsole, COORD pos);
void move(HANDLE hConsole, char Interface[12][80], size_t size, int mat[size][size]);
void func(int a, size_t size, int mat[size][size], HANDLE hConsole);
void printArr(HANDLE hConsole, size_t size, int arr[size][size]);
void cleenWorkspace(HANDLE hConsole, COORD pos);
void buildLine(HANDLE hConsole);

int main (void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand((unsigned)time(NULL));
	char ch;
	size_t size;
	char Interface[12][80] = {"1. Clear all elements of the matrix",
		"2. Fill random numbers in a range you will enter",
		"3. Replace the element of the array by entering the index to the entered value",
		"4. Flip array vertically",
		"5. Transpose array",
		"6. Return matrix 270 degrees clockwise",
		"7. Calculate the arithmetic average of array",
		"8. Calculate the sum of the elements of a given line",
		"9. Calculate the sum of the elements above the main diagonal",
		"10. Change the first minimum and first maximum matrix elements in places",
		"11. Change the last minimum and last maximum matrix elements in places",
		"12. Swap lines with max amount of items with min amount of elements"};
	
	printf("\nenter array size, less then 10 \n");
	int status = 0;
	status = scanf("%u", &size);
	if ( status == 0 || size > 9)
	{
		printf("you enter wrong value\n");
		return -1;
	}
	COORD pos;
	int arr[size][size];
	nullMatrix(size, arr);
	//while (TRUE)
	cleenScreen(hConsole, pos);
	buildInterfase(hConsole, Interface);
	printArr(hConsole, size, arr); 
	move(hConsole, Interface, size, arr);
	cleenScreen(hConsole, pos);
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(hConsole, pos);
	puts(" ");
	return EXIT_SUCCESS;
}

void move(HANDLE hConsole, char Interface[12][80], size_t size, int mat[size][size])
{
	int a = 0;
	int b;
	int k = 0;
	char ch;
	COORD pos;
	while (a != -1)
	{
		int color = FOREGROUND_BLUE | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color);
		k = 0;
		pos.Y = 5 + a;
		pos.X = 0;
		while(!kbhit())
		{
			SetConsoleCursorPosition(hConsole, pos);
			for (unsigned j = k; j < 30 + k; j++)
			{
				printf("%c", Interface[a][j]);
				if (Interface[a][j + 1] == '\0')
				{
					for(; j - k < 30; j++)
						printf(" ");
					k = -1;
					break;
				}
			}
			if (k == 0 || k == -1)
				for(unsigned i = 0; !kbhit() && i < 100; i++)
					Sleep(10);
			else
				Sleep(100);
			k++;
			
			
		}
		
		ch = getch();
		//cleenWorkspace(hConsole, pos);
		switch (ch)
		{
			case 72: b = a; a--; if (a < 0) a = 11; break;
			case 80: b = a; a++; if (a > 11) a = 0; break;
			case 'x': b = a; a = -1; break;
			case 13: func(a, size, mat, hConsole);
				printArr(hConsole, size, mat);
				buildLine(hConsole);
				break;
		}
	
		SetConsoleCursorPosition(hConsole, pos);
		color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color);
		for (unsigned j = 0; j < 30 && Interface[b][j] != '\0'; j++)
				printf("%c", Interface[b][j]);
		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(hConsole, pos);
	}
	
}
void cleenWorkspace(HANDLE hConsole, COORD pos)
{
	int i, j;
	for (i = 18; i < 25; i++)
		for (j = 0; j < 80; j++)
		{
			pos.X = j; 
			pos.Y = i;
			SetConsoleCursorPosition(hConsole, pos);
			if (j < 33)
				putchar(' ');
					
		}
}
void func(int a, size_t size, int arr[size][size], HANDLE hConsole)
{
	COORD pos;
	cleenWorkspace(hConsole, pos);
	pos.X = 0;
	pos.Y = 18;
	int status = 1;
	SetConsoleCursorPosition(hConsole, pos);
	switch (a)
	{
		case 0: nullMatrix(size, arr); break;
		case 1:	printf("Enter min and max random value\nless than 10000\n");
			int min, max;
			printf("min = ");
			status = 1;
			status = scanf("%i", &min);
			if(status == 0)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			printf("max = ");
			status = 1;
			status = scanf("%u", &max);
			if(status == 0)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			if (min > 9999 || max > 9999 || min < -9999 || max < -9999)
			{
				printf("error");
				break;
			}
			fillRand(size, arr, min, max); break;
		case 2: printf("Enter position of element\n you want change\nrow = ");
			unsigned row, col;
			int elem;
			status = 1;
			status = scanf("%u", &row);
			if(status == 0)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			printf("colone = ");
			status = 1;
			status = scanf("%u", &col);
			if(status == 0)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			printf("new value, less then 10000 = ");
			status = 1;
			status = scanf("%u", &elem);
			if(status == 0)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			if (elem > 9999)
			{
				printf("error");
				break;
			}
			if (changeElem(size, arr, row - 1, col - 1, elem) == 0)
				printf("error");
			break;
		case 3: flipV(size, arr); break;
		case 4: transpArr(size,arr); break;
		case 5: rotateCW270(size,arr); break;
		case 6: printf("Mean value is \n%.10lf", meanValue(size, arr)); break;
		case 7: printf("Enter number of the line\n");
			unsigned row1;
			status = 1;
			status = scanf("%u", &row1);
			if(0 == status)
			{
				printf("error");
				fflush(stdin);
				break;
			}
			long long sum = sumRow(size, arr, row1 - 1, &status);
			if (status == 0)
				printf("ERROR");
			else
				printf("Sum of elements of %u line \n%lld", row1, sum); break;
		case 8: printf("Sum of elements above diagonal\n%lld", sumDiagUp(size, arr)); break; break;
		case 9: moveMaxToMinFirst(size, arr); break;
		case 10: moveMaxToMinLast(size, arr); break;
		case 11: moveMaxRowToMin(size, arr); break;
		
	}
}

void printArr(HANDLE hConsole, size_t size, int arr[size][size])
{
	COORD pos;
	pos.X = 35;
	pos.Y = 6;
	unsigned i, j;
	if (size < 11)
	for (i = 0; i < size; i++)
	{
		pos.X = 35;
		SetConsoleCursorPosition(hConsole, pos);
		for (j = 0; j < size; j++)
			printf ("%5i", arr[i][j]);
		pos.Y ++;
		for (pos.X = 35; pos.X < 80; pos.X++)
		{
			SetConsoleCursorPosition(hConsole, pos);
			putchar(' ');
		}
		pos.Y ++;
	}
	while(pos.Y < 24)
	{
		for (pos.X = 35; pos.X < 80; pos.X++)
		{
			SetConsoleCursorPosition(hConsole, pos);
			putchar(' ');
		}
		pos.Y ++;
	}
}

void buildLine(HANDLE hConsole)
{
	COORD pos;
	int color = FOREGROUND_RED;
	SetConsoleTextAttribute(hConsole, color);
	pos.X = 33;
	for (pos.Y = 5; pos.Y < 25; pos.Y++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		printf("||");
	}
	color = FOREGROUND_BLUE | FOREGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, color);
}

void buildInterfase(HANDLE hConsole, char Interface[12][80])
{
	
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(hConsole, pos);
	printf("---------------------------------Welcome USER!---------------------------------\nPush 'x' to exit, to move up push '%c', to move down push '%c'\nTo use chosen action push Enter\nIf program don't work check CAPS, it should be off, and language - English/n", 24, 25);
	
	pos.Y = 4;
	int color = FOREGROUND_RED;
	SetConsoleTextAttribute(hConsole, color);
	for (pos.X = 0; pos.X < 80; pos.X++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		printf("-");
	}
	pos.X = 33;
	for (pos.Y = 5; pos.Y < 25; pos.Y++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		printf("||");
	}
	pos.Y = 17;
	for (pos.X = 0; pos.X < 33; pos.X++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		printf("-");
	}
	
	pos.X = 0;
	pos.Y = 5;
	color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, color);
	SetConsoleCursorPosition(hConsole, pos);
	for (unsigned i = 0; i < 12; i++)
	{
		for (unsigned j = 0; j < 30 && Interface[i][j] != '\0'; j++)
			printf("%c", Interface[i][j]);
		printf("\n");
	}
	
}

void cleenScreen(HANDLE hConsole, COORD pos)
{
	int i, j;
	for (i = 0; i < 25; i++)
		for (j = 0; j < 80; j++)
		{
			pos.X = j; 
			pos.Y = i;
			SetConsoleCursorPosition(hConsole, pos);
				putchar(' ');
		}
}

void transpArr(size_t size, int arr[size][size])
{
	unsigned i, j;
	int temp;
	for(i = 0; i < size; i++)
		for(j = i; j < size; j++)
		{
			temp = arr[i][j];
			arr[i][j] = arr[j][i];
			arr[j][i] = temp;
		}	
}

void rotateCW270(size_t n, int mat[n][n])
{
	int c;
	unsigned i, j;
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

void nullMatrix(size_t size, int mat[size][size])
{
	unsigned i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			mat[i][j] = 0;
}

void fillRand(size_t size, int mat[size][size], int min, int max)
{
	unsigned i, j;
	if (min > max)
	{
		int temp = max;
		max = min;
		min = temp;
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			mat[i][j] = rand() % (max - min + 1) + min;
}

int changeElem(size_t size, int mat[size][size], unsigned row, unsigned colone, int elem)
{
	if(size <= row || size <= colone)
		return 0;
	mat[row][colone] = elem;
	return 1;
}

void flipV(size_t size, int mat[size][size])
{
	int c;
	unsigned i, j;
	for (i = 0; i < (size + 1) / 2; i++)
		for (j = 0; j < size; j++)
		{
			c = mat[i][j];
			mat[i][j] = mat[size - 1 - i][j];
			mat[size - 1 - i][j] = c;
		}
}

long long sumRow (size_t size, int mat[size][size], unsigned row, int * status)
{
	if (row > size - 1)
	{
		*status = 0;
		return 0;
	}
	*status = 1;
	long long sum = 0;
	unsigned i;
	for (i = 0; i < size; i++)
		sum += mat[row][i];
	return sum;
}

long long sumDiagUp (size_t size, int mat[size][size])
{
	long long sum = 0;
	unsigned i, j;
	for (i = 0; i < size; i++)
		for (j = i; j < size; j++)
			sum += mat[i][j];
	return sum;
}

void moveMaxToMinFirst (size_t size, int mat[size][size])
{
	unsigned i, j, rowMax = 0, rowMin = 0, colMax = 0, colMin = 0;
	int min = mat[0][0], max = mat[0][0], temp;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			if (min > mat[i][j])
			{
				colMin = j;
				rowMin = i;
				min = mat[i][j];
			}
			if (max < mat[i][j])
			{
				colMax = j;
				rowMax = i;
				max = mat[i][j];
			}
		}
	temp = mat[rowMin][colMin];
	mat[rowMin][colMin] = mat[rowMax][colMax];
	mat[rowMax][colMax] = temp;
}

void moveMaxToMinLast (size_t size, int mat[size][size])
{
	unsigned i, j, rowMax = 0, rowMin = 0, colMax = 0, colMin = 0;
	int min = mat[0][0], max = mat[0][0], temp;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			if (min >= mat[i][j])
			{
				colMin = j;
				rowMin = i;
				min = mat[i][j];
			}
			if (max <= mat[i][j])
			{
				colMax = j;
				rowMax = i;
				max = mat[i][j];
			}
		}
	temp = mat[rowMin][colMin];
	mat[rowMin][colMin] = mat[rowMax][colMax];
	mat[rowMax][colMax] = temp;
}

void moveMaxRowToMin (size_t size, int mat[size][size])
{
	unsigned i, rowMax = 0, rowMin = 0;
	int temp;
	int sum, sumMax = sumRow(size, mat, 0, &temp), sumMin = sumRow(size, mat, 0, &temp);
	for (i = 0; i < size; i++)
	{
		sum = sumRow(size, mat, i, &temp);
		if (sum < sumMin)
		{
			sumMin = sum;
			rowMin = i;
		}
		if (sum > sumMax)
		{
			sumMax = sum;
			rowMax = i;
		}
	}
	for (i = 0; i < size; i++)
	{
		temp = mat[rowMin][i];
		mat[rowMin][i] = mat[rowMax][i];
		mat[rowMax][i] = temp;
	}
}

double meanValue(size_t size, int mat[size][size])
{
	unsigned i, j;
	long long sum = 0;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			sum += (long long)mat[i][j];
	return (double)sum / (double)(size * size);
}
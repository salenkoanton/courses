#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void fillRand3(int arr[], int size);
int checkRand3(int arr[], int size);
int maxValue(int arr[], int size);
int maxIndex(int arr[], int size);
int maxOccurance(int arr[], int size);
int diff(int arr1[], int arr2[], int res[], int size);
void mult(int arr1[], int arr2[], int res[], int size);
int gt(int arr1[], int arr2[], int size);
void lor(int arr1[], int arr2[], int res[], int size);
int main(void)
{
	int arr1[100], arr2[100];
	int n = 5;
	fillRand3(arr1, n);
	fillRand3(arr2, n);
	printf("%d", maxIndex(arr1, n));
	
}
void fillRand3(int arr[], int size)
{
	srand(time(NULL));
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rand() % 2;
}
int checkRand3(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		if (arr [i] != 0 && arr [i] != 1)
			return 0;
	return 1;
}
int maxValue(int arr[], int size)
{
	int i, max = arr[0];
	for (i = 0; i < size; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
int maxIndex(int arr[], int size)
{
	int i;
	int o = maxValue(arr, size);
	for (i = 0; i < size; i++)
		if (arr[i] == o)
			return i;
}
int maxOccurance(int arr[], int size)
{
	int i ,j;
	int q = 1, p = 1;
	int max = arr[0];
	for (i = 0; i < size; i++){
		for (j = i + 1; j < size; j++)
			if (arr[j] == arr[i])
				p++;
		if (p >= q && arr[i] > max)
		{
			q = p;
			max = arr[i];
		}
		p = 1;
	}
	return max;
}
int diff(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++){
		res[i] = arr1[i] - arr2[i];
		if (arr1[i] != arr2[i])
			return 0;
	}
	return 1;
}
void mult(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		res[i] = arr1[i] * arr2[i];
}
int gt(int arr1[], int arr2[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		if (arr1[i] <= arr2[i])
			return 0;
	return 1;		
}
void lor(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		res[i] = arr1[i] || arr2[i];
}

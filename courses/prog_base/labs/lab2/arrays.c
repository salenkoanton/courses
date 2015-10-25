#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void fillRand3(int arr[], int size)
{
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
float meanValue(int arr[], int size)
{
	int i;
	float sum = 0;
	for(i = 0; i < size; i++)
		sum += arr[i];
	sum /= size;
	return sum;
	
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
		if (p >= q)
		{
			q = p;
			max = arr[i];
		}
		if(p == q && arr[i] > max)
			max = arr[i];

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

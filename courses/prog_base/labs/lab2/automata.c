#include <stdio.h>
/*int run(int moves[], int movesLen, int res[], int resLen);
int main(void)
{
	int arr[6] = {22, 12, 202, 22, 22, 4};
	int brr[6] = {-10, -10, -10, -10, -10, -10};
	int a = 6, b = 6;
	int c = run(arr, a, brr, b);
	for (a = 0; a < b; a++)
		printf(" %d ", brr[a]);
	printf("\n %d ", c);
	return 0;
}*/
int run(int moves[], int movesLen, int res[], int resLen)
{
	
	enum pos{
		Q0_pos = -4,
		Q1_pos,
		Q2_pos,
		Q3_pos
	} initial_pos;

	enum State { INIT_STATE = -10,
		BREAK_STATE,
		POP_STATE,
		CONTINUE_STATE,
		REPEAT_STATE,
		STOP_STATE
	};
	enum State initialState = INIT_STATE;
	enum State currentState = initialState;
	initial_pos = Q0_pos;
	enum pos current_pos = initial_pos;
	int i, j = 0, f;
	int arr[4][4] = {1, POP_STATE, 5, BREAK_STATE, STOP_STATE, 21, CONTINUE_STATE, 625, BREAK_STATE, STOP_STATE, REPEAT_STATE, POP_STATE, 25, 6, 7, 627};
	int brr[4][4] = {Q0_pos, Q1_pos, Q1_pos, 0, 0, Q2_pos, Q2_pos, Q3_pos, 0, 0, Q3_pos, Q3_pos, Q2_pos, Q1_pos, Q0_pos, Q3_pos};
	for (i = 0; i < movesLen; i++)
	{
		currentState = initialState;
		switch (moves[i]) {
				case 4: f = 0; break;
				case 12: f = 1; break;
				case 22: f = 2; break;
				case 202: f = 3; break;
				default: f = 4; currentState = STOP_STATE; break;
			};
		if (f != 4 && arr[current_pos + 4][f] > 0)
		{
			res[j] = arr[current_pos + 4][f];
			j++;
		}
		else 
			currentState = arr[current_pos + 4][f];
		if (currentState == STOP_STATE)
		{
			i = movesLen;
			int a = j;
			for (j = a + 1; j < resLen; j++)
				res[j] = 0;
		}
		if (currentState == POP_STATE && j != 0)
		{
			j--;
			res[j] = 0;
		}
		if (currentState == REPEAT_STATE)
			i--;
		if (currentState == BREAK_STATE)
		{
			i = movesLen;
			int a = j;
			for (j = a + 1; j < resLen; j++)
				res[j] = 0;
		}
		if (j == resLen)
			i = movesLen;
		current_pos = brr[current_pos + 4][f];
	}
	int c = j;
	while (j++ < resLen && (currentState != STOP_STATE))
	{
		res[j - 1] = 0;
	}
	return c;
	
}



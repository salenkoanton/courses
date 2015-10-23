#include <stdio.h>
/*int run(int moves[], int movesLen, int res[], int resLen);
int main(void)
{
	int arr[6] = {12, 12, 202, 22, 22, 4};
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
	int i, j = 0;
	
	for (i = 0; i < movesLen; i++)
	{
		currentState = initialState;
		switch (current_pos) {
			case Q0_pos: switch (moves[i]) {
				case 4: res[j] = 1; j++; break;
				case 12: currentState = POP_STATE; current_pos = Q1_pos; break;
				case 22: res[j] = 5; j++; current_pos = Q1_pos; break;
				case 202: currentState = BREAK_STATE; break;
				default: currentState = STOP_STATE; break;
			}; break;
			case Q1_pos: switch (moves[i]) {
				case 4: currentState = STOP_STATE; break;
				case 12: res[j] = 21; j++; current_pos = Q2_pos; break;
				case 22: currentState = CONTINUE_STATE; current_pos = Q2_pos; break;
				case 202: res[j] = 625; j++; current_pos = Q3_pos; break;
				default: currentState = STOP_STATE; break;
			}; break;
			case Q2_pos: switch (moves[i]) {
				case 4: currentState = BREAK_STATE; break;
				case 12: currentState = STOP_STATE; break;
				case 22: currentState = REPEAT_STATE; current_pos = Q3_pos; break;
				case 202: currentState = POP_STATE; current_pos = Q3_pos; break;
				default: currentState = STOP_STATE; break;
			}; break;
			case Q3_pos: switch (moves[i]) {
				case 4: res[j] = 25; j++; current_pos = Q2_pos; break;
				case 12: res[j] = 6; j++; current_pos = Q1_pos; break;
				case 22: res[j] = 7; j++; current_pos = Q0_pos; break;
				case 202: res[j] = 627; j++; break;
				default: currentState = STOP_STATE; break;
			}; break;
		}
		if (currentState == STOP_STATE)
		{
			i = movesLen;
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
					
	}
	int c = j;
	while (j++ < resLen && (currentState != STOP_STATE))
	{
		res[j - 1] = 0;
	}
	return c;
	
}


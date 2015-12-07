#include <stdio.h>
#define CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
char check(COORD posJopa, int l);
int main()
{
	COORD posHead;
	COORD posJopa;
	posJopa.X = 0;
	posJopa.Y = 1;
	posHead.X = 5;
	posHead.Y = 1;
	COORD vert;
	vert.X = 1;
	vert.Y = 0;
	DWORD a = 0;
	char chr = 0;
	char chl = 0;
	char chu = 0;
	char chd = 0;
	char ch = 0;
	char rnd = 0;
	int flag = 1;
	int l = 6;
	char checking; 
	COORD randomPos;
	system("cls");
	srand(time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, posJopa);
	puts("######");
	while (1){
		for(int i = 0; i < 10; i++){
			Sleep(10);
			if (kbhit() != 0)
				ch = getch();
		}
		checking = 0;
		chl = 0;
		chr = 0;
		chu = 0;
		chd = 0;
		while (flag)
		{
			randomPos.X = rand() % 80;
			randomPos.Y = rand() % 25;
			ReadConsoleOutputCharacter(hConsole, &rnd, 1, randomPos, &a);
			if (rnd != '#'){
				flag = 0;
				SetConsoleCursorPosition(hConsole, randomPos);
				putchar('@');
			}
		}
		switch (ch){
			case 'w': if (vert.Y != 1) {vert.Y = -1; vert.X = 0;} break;
			case 's': if (vert.Y != -1) {vert.Y = 1; vert.X = 0;} break;
			case 'd': if (vert.X != -1) {vert.Y = 0; vert.X = 1;} break;
			case 'a': if (vert.X != 1) {vert.Y = 0; vert.X = -1;} break;
			default: break;
		}
		posHead.X += vert.X;
		if (posHead.X == 80)
			posHead.X = 0;
		else if (posHead.X == -1)
			posHead.X = 79;
		posHead.Y += vert.Y;
		if (posHead.Y == 25)
			posHead.Y = 0;
		else if (posHead.Y == -1)
			posHead.Y = 24;
		ReadConsoleOutputCharacter(hConsole, &rnd, 1, posHead, &a);
		if (rnd == '@'){
			l++;
			flag = 1;
		}
		if (rnd == '#'){
			SetConsoleCursorPosition(hConsole, posHead);
			printf("game over");
			Sleep(1000);
			return 0;
		}
		
		SetConsoleCursorPosition(hConsole, posHead);
		putchar('#');
		if (flag == 0)
		{
			if(posJopa.X == 79)
				posJopa.X = 0;
			else
				posJopa.X++;
			ReadConsoleOutputCharacter(hConsole, &chr, 1, posJopa, &a);
			if (posJopa.X == 0)
				posJopa.X = 78;
			else if (posJopa.X == 1)
					posJopa.X = 79;
				else
					posJopa.X -= 2;
			ReadConsoleOutputCharacter(hConsole, &chl, 1, posJopa, &a);
			if(posJopa.X == 79)
				posJopa.X = 0;
			else
				posJopa.X++;
			if(posJopa.Y == 24)
				posJopa.Y = 0;
			else
				posJopa.Y++;
			ReadConsoleOutputCharacter(hConsole, &chu, 1, posJopa, &a);
			if(posJopa.Y == 0)
				posJopa.Y = 23;
			else if(posJopa.Y == 1)
					posJopa.Y = 24;
				else
					posJopa.Y -= 2;
			ReadConsoleOutputCharacter(hConsole, &chd, 1, posJopa, &a);
			if(posJopa.Y == 24)
				posJopa.Y = 0;
			else
				posJopa.Y++;
			if (chu + chd + chl + chr > '#')
				checking = check(posJopa, l);
			switch (checking){
				case 'l' : chu = 0; chd = 0; chr = 0; break;
				case 'r' : chu = 0; chd = 0; chl = 0; break;
				case 'u' : chl = 0; chd = 0; chr = 0; break;
				case 'd' : chu = 0; chl = 0; chr = 0; break;
				default : break;
			}
			SetConsoleCursorPosition(hConsole, posJopa);
			putchar(' ');
			
			if(chu == '#')
				if(posJopa.Y == 24)
					posJopa.Y = 0;
				else
					posJopa.Y++;
			if(chd == '#')
				if(posJopa.Y == 0)
					posJopa.Y = 24;
				else
					posJopa.Y--;
			if(chl == '#')
				if (posJopa.X == 0)
					posJopa.X = 79;
				else
					posJopa.X--;
			if(chr == '#')
				if(posJopa.X == 79)
					posJopa.X = 0;
				else
					posJopa.X++;
		}
	}
	return 0;

}

char check(COORD posJopa, int l)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD a = 0;
	char chr = 0;
	char chl = 0;
	char chu = 0;
	char chd = 0;
	char ch = 0;
	if (l == 0)
		return 1;
	SetConsoleCursorPosition(hConsole, posJopa);
	putchar(' ');
			if(posJopa.X == 79)
				posJopa.X = 0;
			else
				posJopa.X++;
			ReadConsoleOutputCharacter(hConsole, &chr, 1, posJopa, &a);
			if (posJopa.X == 0)
				posJopa.X = 78;
			else if (posJopa.X == 1)
					posJopa.X = 79;
				else
					posJopa.X -= 2;
			ReadConsoleOutputCharacter(hConsole, &chl, 1, posJopa, &a);
			if(posJopa.X == 79)
				posJopa.X = 0;
			else
				posJopa.X++;
			if(posJopa.Y == 24)
				posJopa.Y = 0;
			else
				posJopa.Y++;
			ReadConsoleOutputCharacter(hConsole, &chu, 1, posJopa, &a);
			if(posJopa.Y == 0)
				posJopa.Y = 23;
			else if(posJopa.Y == 1)
					posJopa.Y = 24;
				else
					posJopa.Y -= 2;
			ReadConsoleOutputCharacter(hConsole, &chd, 1, posJopa, &a);
			if(posJopa.Y == 24)
				posJopa.Y = 0;
			else
				posJopa.Y++;
			
			if(chu == '#'){
				if(posJopa.Y == 24)
					posJopa.Y = 0;
				else
					posJopa.Y++;
				if (check(posJopa, l - 1))
					ch =  'u';
				if(posJopa.Y == 0)
					posJopa.Y = 24;
				else
					posJopa.Y--;
			}
			if(chd == '#'){
				if(posJopa.Y == 0)
					posJopa.Y = 24;
				else
					posJopa.Y--;
				if (check(posJopa, l - 1))
					ch = 'd';
				if(posJopa.Y == 24)
					posJopa.Y = 0;
				else
					posJopa.Y++;
			}
			if(chl == '#'){
				if (posJopa.X == 0)
					posJopa.X = 79;
				else
					posJopa.X--;
				if (check(posJopa, l - 1))
					ch = 'l';
				if(posJopa.X == 79)
					posJopa.X = 0;
				else
					posJopa.X++;
			}
			if(chr == '#'){
				if(posJopa.X == 79)
					posJopa.X = 0;
				else
					posJopa.X++;
				if (check(posJopa, l - 1))
					ch = 'r';
				if (posJopa.X == 0)
					posJopa.X = 79;
				else
					posJopa.X--;
			}
			SetConsoleCursorPosition(hConsole, posJopa);
				putchar('#');
			return ch;
			
}
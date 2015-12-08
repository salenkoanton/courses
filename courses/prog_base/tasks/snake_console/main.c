#include <stdio.h>
#define CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>

struct Moves{
	char move;
	int count;
};
void printRec();
int move(HANDLE hConsole, size_t n, const char * Interface[n]);
int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Moves moves[200];
	for (int i = 1; i < 200; i++)
		moves[i].count = 0;
	moves[0].count = 5;
	moves[0].move = 'r';
	COORD posHead;
	COORD posJopa;
	posJopa.X = 0;
	posJopa.Y = 1;
	posHead.X = 5;
	posHead.Y = 1;
	DWORD a;
	COORD res;
	res.X = 0;
	res.Y = 0;
	COORD vert;
	vert.X = 1;
	vert.Y = 0;
	int spd = 0;
	char ch = 0;
	char rnd = 0;
	int flag = 1;
	int l = 6;
	int p = 0;
	int true = 1;
	int speed = 0;
	const char * Interface[3] = {
		"New game",
		"Records",
		"Exit"
	};
	const char * Speed[8] = {
		"\t1",
		"\t2",
		"\t3",
		"\t4",
		"\t5",
		"\t6",
		"\t7",
		"\t8"
	};
	
	COORD randomPos;
	while(speed == 0){
	system("cls");
	int status = move(hConsole, 3, Interface);
	system("cls");
	if (status == 0)
		speed = move(hConsole, 8, Speed) + 1;
	if (status == 1) 
		printRec();
	if (status == 2)
	{
		return 0;
	}
	}
	system("cls");
	srand(time(NULL));
	SetConsoleCursorPosition(hConsole, posJopa);
	puts("######");
	while (true){
		
		ch = 0;
		switch (l){
		case 10 : if (speed + spd < 11 && spd != 1) spd++; break;
		case 20 : if (speed + spd < 11 && spd != 2) spd++; break;
		case 30 : if (speed + spd < 11 && spd != 3) spd++; break;
		case 40 : if (speed + spd < 11 && spd != 4) spd++; break;
		case 50 : if (speed + spd < 11 && spd != 5) spd++; break;
		case 60 : if (speed + spd < 11 && spd != 6) spd++; break;
		case 70 : if (speed + spd < 11 && spd != 7) spd++; break;
		case 80 : if (speed + spd < 11 && spd != 8) spd++; break;
		case 90 : if (speed + spd < 11) spd++; break;
		default : break;
		}
		for(int i = 0; i < 13 - speed - spd; i++){
			Sleep(10);
			if (kbhit() != 0)
				ch = getch();
		}
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
			case 'w': if (abs(vert.Y) != 1) {vert.Y = -1; vert.X = 0; p++; moves[p].move = 'u'; moves[p].count = 1;} else moves[p].count++; break;
			case 's': if (abs(vert.Y) != 1) {vert.Y = 1; vert.X = 0; p++; moves[p].move = 'd'; moves[p].count = 1;} else moves[p].count++; break;
			case 'd': if (abs(vert.X) != 1) {vert.Y = 0; vert.X = 1; p++; moves[p].move = 'r'; moves[p].count = 1;} else moves[p].count++; break;
			case 'a': if (abs(vert.X) != 1) {vert.Y = 0; vert.X = -1; p++; moves[p].move = 'l'; moves[p].count = 1;} else moves[p].count++; break;
			default: moves[p].count++; break;
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
			SetConsoleCursorPosition(hConsole, res);
			printf("Result: %i", (l - 6) * speed);
		}
		if (rnd == '#'){
			SetConsoleCursorPosition(hConsole, posHead);
			true = 0;
			Sleep(1000);
		}
		
		SetConsoleCursorPosition(hConsole, posHead);
		putchar('#');
		
		if (flag == 0)
		{
			SetConsoleCursorPosition(hConsole, posJopa);
			putchar(' ');
			switch (moves[0].move){
				case 'l' :
					if (posJopa.X == 0)
						posJopa.X = 79;
					else
						posJopa.X--;
					break;
				case 'r' :
					if(posJopa.X == 79)
						posJopa.X = 0;
					else
						posJopa.X++; 
					break;
				case 'u' :
					
					if(posJopa.Y == 0)
						posJopa.Y = 24;
					else
						posJopa.Y--;
					break;
				case 'd' : 
					if(posJopa.Y == 24)
						posJopa.Y = 0;
					else
						posJopa.Y++;
					break;
				default : break;
			}
			moves[0].count--;
			if (moves[0].count == 0){
				for (int i = 0; i < 199; i++)
				{
					moves[i].count = moves[i + 1].count;
					moves[i].move = moves[i + 1].move;
				}
				p--;
			}
			
		}
	}
	system("cls");
	posHead.X = 34;
	posHead.Y = 10;
	SetConsoleCursorPosition(hConsole, posHead);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	puts("GAME OVER");
	posHead.Y = 11;
	SetConsoleCursorPosition(hConsole, posHead);
	printf("your result is %i", (l - 6) * speed);
	posHead.Y++;
	SetConsoleCursorPosition(hConsole, posHead);
	printf("enter your nickname\n");
	char nick[20];
	posHead.Y++;
	SetConsoleCursorPosition(hConsole, posHead);
	gets(nick);
	int record[10];
	char temp[10][20];
	FILE * fp = NULL;
	fp = fopen("rec.txt", "r");
	if (NULL == fp)
		return 0;
	for (int i = 0; i < 10; i++){
		fscanf(fp, "%i %s", &record[i], temp[i]);
		//printf("%i. %8i  %s\n", i + 1, record, nick);
		if (record[i] > (l - 6) * speed)
			p = i;
	}
	fclose(fp);
	fp = fopen("rec.txt", "w");
	for (int i = 0; i < 10; i++){
		if (p == i - 1)
			fprintf(fp, "%i %s\n",(l - 6) * speed, nick);
		fprintf(fp, "%i %s\n", record[i], temp[i]);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	getchar();
	fclose(fp);
	return 0;

}
int move(HANDLE hConsole, size_t n, const char * Interface[n])
{
	unsigned a = 0;
	unsigned b;
	int k = 0;
	char ch;
	int color;
	COORD pos;
	pos.Y = 5 + a;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	for (unsigned i = 0; i < n; i++){
		for (unsigned j = 0; j < 30; j++)
		{
			printf("%c", Interface[i][j]);
			if (Interface[i][j + 1] == '\0')
				break;
		}pos.Y++;
		SetConsoleCursorPosition(hConsole, pos);
	}
	while (a != 100){
		color = FOREGROUND_BLUE | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color);
		k = 0;
		pos.Y = 5 + a;
		pos.X = 0;	
		SetConsoleCursorPosition(hConsole, pos);
		for (unsigned j = 0; j < 30; j++)
		{
			printf("%c", Interface[a][j]);
			if (Interface[a][j + 1] == '\0')
				break;
		}
		fflush(stdin);
		ch = getch();
		switch (ch)
		{
			case 'w': b = a; if (a == 0) a = n;  a--; break;
			case 's': b = a; a++; if (a > n - 1) a = 0; break;
			case 13: color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
				SetConsoleTextAttribute(hConsole, color);
				return a; 
				break;
			default : b = a; break;
		}
		SetConsoleCursorPosition(hConsole, pos);
		color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color);
		if (a != b)
			for (unsigned j = 0; j < 30 && Interface[b][j] != '\0'; j++)
				printf("%c", Interface[b][j]);

	}
	
	
}

void printRec()
{
	system("cls");
	int record;
	char nick[20];
	FILE * fp = NULL;
	fp = fopen("rec.txt", "r");
	if (NULL == fp)
		return;
	for (int i = 0; i < 10; i++){
		fscanf(fp, "%i %s", &record, nick);
		printf("%i. %8i  %s\n", i + 1, record, nick);
	}
	getchar();
	fclose(fp);
	system("cls");
}
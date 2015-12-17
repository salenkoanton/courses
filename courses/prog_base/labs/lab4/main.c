#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
enum type{
	MAGE = 0,
	WARRIOR,
	THIEF,
	ANY
};
struct Hero {
	char name[20];
	enum type class;
	float health;
	float damage;
	float mag_damage;
	float mana;
	float magic_protect;
	float armor;
	float attack_speed;
	float critical_damage;
	int critical_chanse;
	int gold;
	const struct Weapon * Weapon;
	const struct Weapon * Armor;
	int Weapon_type;
	int Armor_type;
	float curent_health;
	float curent_mana;
};

struct Weapon {
	int type;
	enum type class;
	float health;
	float damage;
	float mag_damage;
	float mana;
	float magic_protect;
	float armor;
	float attack_speed;
	float critical_damage;
	int critical_chanse;
	int cost;
};

const struct Weapon steel_sword = {
	0,
	WARRIOR,
	0,
	30,
	0,
	0,
	0,
	0,
	1,
	1.5,
	10,
	300
};
 


const struct Weapon steel_dagger = {
	2,
	THIEF,
	0,
	5,
	0,
	0,
	0,
	0,
	0.6,
	1.5,
	15,
	300
};

const struct Weapon great_sword = {
	4,
	WARRIOR,
	0,
	70,
	0,
	0,
	0,
	0,
	1.5,
	1.7,
	14,
	800
};

const struct Weapon magic_stick = {
	1,
	MAGE,
	0,
	0,
	10,
	200,
	0,
	0,
	0.8,
	1.4,
	10,
	250
};

const struct Weapon wood_scepter = {
	4,
	MAGE,
	0,
	0,
	30,
	400,
	0,
	0,
	0.9,
	1.8,
	10,
	750
};

const struct Weapon thief_dagger = {
	5,
	THIEF,
	0,
	15,
	0,
	0,
	0,
	0,
	0.6,
	2,
	20,
	800
};

const struct Weapon mage_robe = {
	7,
	MAGE,
	50,
	0,
	5,
	100,
	5,
	5,
	1,
	1,
	0,
	300
};
const struct Weapon arcgmage_robe = {
	10,
	MAGE,
	200,
	0,
	10,
	300,
	10,
	10,
	1,
	1,
	0,
	800
};
const struct Weapon lether_armor = {
	8,
	THIEF,
	100,
	0,
	0,
	0,
	10,
	10,
	1,
	1,
	0,
	350
};
const struct Weapon elven_armor = {
	11,
	THIEF,
	200,
	20,
	0,
	0,
	15,
	20,
	1,
	1,
	0,
	870
};
const struct Weapon steel_armor = {
	6,
	WARRIOR,
	100,
	0,
	0,
	0,
	10,
	10,
	1,
	1,
	0,
	360
};
const struct Weapon dragon_armor = {
	9,
	WARRIOR,
	200,
	0,
	0,
	0,
	20,
	20,
	1,
	1,
	0,
	900
};
void weapons(struct Hero * hero);
void printRec();
int move(HANDLE hConsole, size_t n, const char * Interface[n], int flag, struct Hero * hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief);
void armor(struct Hero * hero);
int battle(struct Hero * hero, struct Hero * bot1, struct Hero * bot2, struct Hero * bot3);
void printBot (int a, struct Hero bot1, struct Hero bot2, struct Hero bot3);
void createHero (struct Hero ** hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief);
void printHero (int a, struct Hero * mage, struct Hero * warrior, struct Hero * thief);
void shop(struct Hero * hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief);
void printHeroShop (struct Weapon weap, struct Hero * hero);
void save(struct Hero * hero);
int main(void)
{
	struct Hero mage = {
		"",
		MAGE,
		450,
		0,
		50,
		200,
		30,
		10,
		1,
		1,
		0,
		0, 
		NULL,
		NULL
	};
	struct Hero warrior = {
		"",
		WARRIOR,
		550,
		60,
		0,
		0,
		5,
		25,
		1.3,
		1,
		0,
		0, 
		NULL,
		NULL
	};
	struct Hero thief = {
		"",
		THIEF,
		400,
		60,
		0,
		0,
		10,
		15,
		1,
		1.2,
		5,
		0, 
		NULL,
		NULL
	};
	struct Hero bot1 = {
		"Mage",
		ANY,
		500,
		0,
		45,
		0,
		15,
		15,
		1.4,
		1.5,
		10,
		0, 
		NULL,
		NULL
	};
	struct Hero bot2 = {
		"Guard",
		ANY,
		400,
		65,
		0,
		0,
		15,
		35,
		1.8,
		1,
		0,
		0, 
		NULL,
		NULL
	};
	struct Hero bot3 = {
		"Black knight",
		ANY,
		700,
		100,
		0,
		0,
		25,
		25,
		1,
		1.2,
		5,
		0, 
		NULL,
		NULL
	};
	struct Hero * hero;
	struct Hero * bot = &(bot3);
	COORD posHead;
	int a;
	int b;
	int p = 0;
	int status = 0;
	int true = 0;
	const char * Interface[3] = {
		"New game",
		"Load",
		"Records"
	};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	metka: a = move (hConsole, 3, Interface, 7, hero, &(mage), &(warrior), &(thief));
	switch (a){
		case 0 : createHero(&(hero), &(mage), &(warrior), &(thief)); true = 1; break;
		case 1 :
			system("cls");
			FILE * fp = NULL;
			printf("enter full name of file what you will open to load\n");
			char str[30];
			gets(str);
			fp = fopen(str, "r");
			if (NULL == fp)
				status = 1;
			if (status == 0)
			{
				fscanf(fp, "%i", &(b));
				switch (b)
				{
					case MAGE: hero = &(mage); break;
					case WARRIOR: hero = &(warrior); break;
					case THIEF: hero = &(thief); break;
				}
				int Weapon_type;
				int Armor_type;
				fscanf(fp, "%i %i %i", &(Weapon_type), &(Armor_type), &(hero->gold));
				switch (Armor_type)
				{
					case -1: status = 1; break;
					case 6: hero->Armor = &(steel_armor); break;
					case 7: hero->Armor = &(mage_robe); break;
					case 8: hero->Armor = &(lether_armor); break;
					case 9: hero->Armor = &(dragon_armor); break;
					case 10: hero->Armor = &(arcgmage_robe); break;
					case 11: hero->Armor = &(elven_armor); break;
				}
				if (status != 1){
					hero->health += hero->Armor->health;
					hero->damage += hero->Armor->damage;
					hero->mag_damage += hero->Armor->mag_damage;
					hero->mana += hero->Armor->mana;
					hero->magic_protect += hero->Armor->magic_protect;
					hero->armor += hero->Armor->armor;
					hero->critical_damage += hero->Armor->critical_damage - 1;
					hero->critical_chanse += hero->Armor->critical_chanse;
				}
				switch (Weapon_type)
				{
					case -1: status = -1; break;
					case 0: hero->Weapon = &(steel_sword); break;
					case 1: hero->Weapon = &(magic_stick); break;
					case 2: hero->Weapon = &(steel_dagger); break;
					case 3: hero->Weapon = &(great_sword); break;
					case 4: hero->Weapon = &(wood_scepter); break;
					case 5: hero->Weapon = &(thief_dagger); break;
				}
				if (status != -1){
					hero->health += hero->Weapon->health;
					hero->damage += hero->Weapon->damage;
					hero->mag_damage += hero->Weapon->mag_damage;
					hero->mana += hero->Weapon->mana;
					hero->magic_protect += hero->Weapon->magic_protect;
					hero->armor += hero->Weapon->armor;
					hero->attack_speed = hero->Weapon->attack_speed;
					hero->critical_damage += hero->Weapon->critical_damage - 1;
					hero->critical_chanse += hero->Weapon->critical_chanse;
				}
				true = 1;
				
			}
			else 
				printf("error input");
			fclose(fp);	
			break;
		case 2 : printRec(); goto metka;break;
		
	}
	
	
	while (true)
	{
		shop(hero, &(mage), &(warrior), &(thief));
		true = battle(hero, &(bot1), &(bot2), &(bot3));
		if (true == 2)
			;
		else if (true)
			printf("WIN\n");
		else
			printf("LOSE\n");
		getchar();
	}
	system("cls");
	posHead.X = 34;
	posHead.Y = 10;
	SetConsoleCursorPosition(hConsole, posHead);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	puts("GAME OVER");
	posHead.Y = 11;
	SetConsoleCursorPosition(hConsole, posHead);
	printf("your result is %i", hero->gold);
	posHead.Y++;
	SetConsoleCursorPosition(hConsole, posHead);
	printf("enter your nickname\n");
	char nick[20];
	posHead.Y++;
	SetConsoleCursorPosition(hConsole, posHead);
	gets(nick);
	if (nick[0] == '\0')
		strcpy(nick, "noName");
	int record[10];
	char temp[10][20];
	FILE * fp = NULL;
	fp = fopen("reclab4.txt", "r");
	if (NULL == fp)
		return 0;
	for (int i = 0; i < 10; i++){
		fscanf(fp, "%i %s", &record[i], temp[i]);
		//printf("%i. %8i  %s\n", i + 1, record, nick);
		if (record[i] > hero->gold)
			p = i;
	}
	fclose(fp);
	fp = fopen("reclab4.txt", "w");
	for (int i = 0; i < 10; i++){
		if (p == i - 1)
			fprintf(fp, "%i %s\n", hero->gold, nick);
		fprintf(fp, "%i %s\n", record[i], temp[i]);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	getchar();
	fclose(fp);
	return EXIT_SUCCESS;
}
void shop(struct Hero * hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief)
{
	int true = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char * Interface[4] = {
		"Weapons ",
		"Armor   ",
		"Battle  ",
		"Save    "
	};
	while(true){
	int a = move (hConsole, 4, Interface, 4, hero, mage, warrior, thief);
	if (a == 0)
		 weapons(hero);
	if (a == 1)
		 armor(hero);
	if (a == 2)
		 true = 0;
	if (a == 3)
		save(hero);
	}
	
}
void weapons(struct Hero * hero)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const struct Weapon * bWeapon = hero->Weapon;
	const char * Interface[6] = {
		"Steel sword",
		"Magic stick",
		"Steel dagger",
		"Great sword",
		"Wood scepter", 
		"Thief dagger"
	};
	int a = move (hConsole, 6, Interface, 1, hero, NULL, NULL, NULL);
	switch (a) {
		case 0: hero->Weapon = &(steel_sword); break;
		case 1: hero->Weapon = &(magic_stick); break;
		case 2: hero->Weapon = &(steel_dagger); break;
		case 3: hero->Weapon = &(great_sword); break;
		case 4: hero->Weapon = &(wood_scepter); break;
		case 5: hero->Weapon = &(thief_dagger); break;
	}
	if(a == 100)
		;
	else if (bWeapon == hero->Weapon){
		system("cls");
		printf("You can't buy it, you already have it");
		getchar();
		}
	else if (hero->Weapon->class != hero->class){
		system("cls");
		hero->Weapon = bWeapon;
		printf("You can't buy it, it is not for you");
		getchar();
		}
	else if (hero->Weapon->cost > hero->gold){
		system("cls");
		printf("You have no enought money to buy it");
		hero->Weapon = bWeapon;
		getchar();
		}
	else 
	{
		hero->gold-= hero->Weapon->cost;
		hero->health += hero->Weapon->health;
		hero->damage += hero->Weapon->damage;
		hero->mag_damage += hero->Weapon->mag_damage;
		hero->mana += hero->Weapon->mana;
		hero->magic_protect += hero->Weapon->magic_protect;
		hero->armor += hero->Weapon->armor;
		hero->attack_speed = hero->Weapon->attack_speed;
		hero->critical_damage += hero->Weapon->critical_damage - 1;
		hero->critical_chanse += hero->Weapon->critical_chanse;
		if(NULL != bWeapon){
			hero->health -= bWeapon->health;
			hero->damage -= bWeapon->damage;
			hero->mag_damage -= bWeapon->mag_damage;
			hero->mana -= bWeapon->mana;
			hero->magic_protect -= bWeapon->magic_protect;
			hero->armor -= bWeapon->armor;
			hero->critical_damage -= bWeapon->critical_damage - 1;
			hero->critical_chanse -= bWeapon->critical_chanse;
		}
	}
	
}
void armor(struct Hero * hero)
{
	const struct Weapon * bWeapon = hero->Armor;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char * Interface[6] = {
		"Steel armor",
		"Mage robe",
		"Lether armor",
		"Dragon scales armor",
		"Archimage robe",
		"Elven armor"
	};
	
	switch (move (hConsole, 6, Interface, 2, hero, NULL, NULL, NULL)) {
		case 0: hero->Armor = &(steel_armor); break;
		case 1: hero->Armor = &(mage_robe); break;
		case 2: hero->Armor = &(lether_armor); break;
		case 3: hero->Armor = &(dragon_armor); break;
		case 4: hero->Armor = &(arcgmage_robe); break;
		case 5: hero->Armor = &(elven_armor); break;
		case 100: return;
	}
	if (bWeapon == hero->Armor){
		system("cls");
		printf("You can't buy it, you already have it");
		getchar();
		}
	else if (hero->Armor->class != hero->class){
		system("cls");
		hero->Armor = bWeapon;
		printf("You can't buy it, it is not for you");
		getchar();
		}
	else if (hero->Armor->cost > hero->gold){
		system("cls");
		hero->Armor = bWeapon;
		printf("You have no enought money to buy it");
		getchar();
		}
	else 
	{
		hero->gold -= hero->Armor->cost;
		hero->health += hero->Armor->health;
		hero->damage += hero->Armor->damage;
		hero->mag_damage += hero->Armor->mag_damage;
		hero->mana += hero->Armor->mana;
		hero->magic_protect += hero->Armor->magic_protect;
		hero->armor += hero->Armor->armor;
		hero->critical_damage += hero->Armor->critical_damage - 1;
		hero->critical_chanse += hero->Armor->critical_chanse;
		if(NULL != bWeapon){
			hero->health -= bWeapon->health;
			hero->damage -= bWeapon->damage;
			hero->mag_damage -= bWeapon->mag_damage;
			hero->mana -= bWeapon->mana;
			hero->magic_protect -= bWeapon->magic_protect;
			hero->armor -= bWeapon->armor;
			hero->critical_damage -= bWeapon->critical_damage - 1;
			hero->critical_chanse -= bWeapon->critical_chanse;
		}
	}
}
void createHero (struct Hero ** hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char * Interface[3] = {
		"Mage   ",
		"Warrior",
		"Thief  "
	};
	int a = move(hConsole, 3, Interface, 0, *hero, mage, warrior, thief);
	switch (a)
	{
		case MAGE: *hero = mage; break;
		case WARRIOR: *hero = warrior; break;
		case THIEF: *hero = thief; break;
	}
}
int move(HANDLE hConsole, size_t n, const char * Interface[n], int flag, struct Hero * hero, struct Hero * mage, struct Hero * warrior, struct Hero * thief)
{
	
	struct Weapon * AllWeapons;
	AllWeapons = malloc(sizeof(struct Weapon) * 6);
	AllWeapons[0] = steel_sword;
	AllWeapons[1] = magic_stick;
	AllWeapons[2] = steel_dagger;
	AllWeapons[3] = great_sword;
	AllWeapons[4] = wood_scepter;
	AllWeapons[5] = thief_dagger;
	struct Weapon * AllArmor;
	AllArmor = malloc(sizeof(struct Weapon) * 6);
	AllArmor[0] = steel_armor;
	AllArmor[1] = mage_robe;
	AllArmor[2] = lether_armor;
	AllArmor[3] = dragon_armor;
	AllArmor[4] = arcgmage_robe;
	AllArmor[5] = elven_armor;
	system("cls");
	unsigned a = 0;
	unsigned b;
	int k = 0;
	char ch;
	int color;
	COORD pos;
	pos.Y = 0;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	printf("Push 'x' to exit, to move up push 'w', to move down push 's'\nTo use chosen action push Enter\n");
	COORD pos_gold;
	pos_gold.X = 0;
	pos_gold.Y = 2;
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
		if (flag == 0)
			printHero(a, mage, warrior, thief);
		if (flag == 1)
			printHeroShop(AllWeapons[a], hero);
		if (flag == 2)
			printHeroShop(AllArmor[a], hero);
		if (flag == 3)
			printBot(a, *mage, *warrior, *thief);
		if (flag == 4){
			printHero(hero->class, mage, warrior, thief);
			SetConsoleCursorPosition(hConsole, pos_gold);
			printf("%i gold", hero->gold);
		}
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
		//cleenWorkspace(hConsole, pos);
		switch (ch)
		{
			case 'w': b = a; if (a == 0) a = n;  a--; break;
			case 's': b = a; a++; if (a > n - 1) a = 0; break;
			case 'x': b = a; a = 100; break;
			case 13: color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color); return a; break;
			default : b = a; break;
		}
	
		SetConsoleCursorPosition(hConsole, pos);
		color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		SetConsoleTextAttribute(hConsole, color);
		if (a != b)
			for (unsigned j = 0; j < 30 && Interface[b][j] != '\0'; j++)
				printf("%c", Interface[b][j]);
		//pos.X = 0;
		//pos.Y = 0;
		//SetConsoleCursorPosition(hConsole, pos);

	}
	free(AllWeapons);
	free(AllArmor);
	return a;
	
}
void printHero (int a, struct Hero * mage, struct Hero * warrior, struct Hero * thief)
{
	COORD pos;
	pos.X = 40;
	pos.Y = 5;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, pos);
	switch (a){
		case 0: printf("%.0f health     ", mage->health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f damage     ", mage->damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f magical damage     ", mage->mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f mana     ", mage->mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% magic protect     ", mage->magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% armor    ", mage->armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.1f second on hit    ", mage->attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.2fX crit damage    ", mage->critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%i%% crit chance    ", mage->critical_chanse); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("every 5th hit freeze enemy             "); break; 
		case 1: printf("%.0f health     ", warrior->health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f damage     ",warrior->damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f magical damage     ", warrior->mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f mana     ", warrior->mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% magic protect     ", warrior->magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% armor     ", warrior->armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.1f second on hit    ", warrior->attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.2fX crit damage    ", warrior->critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%i%% crit chance     ", warrior->critical_chanse); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("reduce every 3rd received damage on 50%%"); break; 
		case 2: printf("%.0f health     ", thief->health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f damage     ", thief->damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f magical damage     ", thief->mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f mana     ", thief->mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% magic protect     ", thief->magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.0f%% armor    ", thief->armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.1f second on hit    ", thief->attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%.2fX crit damage     ", thief->critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("%i%% crit chance     ", thief->critical_chanse); pos.Y++; SetConsoleCursorPosition(hConsole, pos); printf("every 2nd hit heal 25%% of hit damage   "); break; 
	}
}
void printHeroShop (struct Weapon weap, struct Hero * hero)
{
	COORD pos;
	pos.X = 40;
	pos.Y = 5;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, pos);
		printf("%.0f + %.0f health           ", hero->health, weap.health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.0f + %.0f damage           ", hero->damage, weap.damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.0f + %.0f magical damage   ", hero->mag_damage, weap.mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.0f + %.0f mana             ", hero->mana, weap.mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.0f%% + %.0f%% magic protect", hero->magic_protect, weap.magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.0f%% + %.0f%% armor        ", hero->armor, weap.armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.1f -> %.1f second on hit           ",hero->attack_speed, weap.attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%.2f + %.2fX crit damage     ", hero->critical_damage, weap.critical_damage - 1); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
		printf("%i%% + %i%% crit chance      ", hero->critical_chanse, weap.critical_chanse); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
		printf("%i - %i gold              ",hero->gold, weap.cost);
}
void printBot (int a, struct Hero bot1, struct Hero bot2, struct Hero bot3)
{
	COORD pos;
	pos.X = 40;
	pos.Y = 5;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, pos);
	switch (a){
		case 0: printf("%.0f health     ", bot1.health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
			printf("%.0f damage     ", bot1.damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f magical damage     ", bot1.mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f mana     ", bot1.mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% magic protect     ", bot1.magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% armor    ", bot1.armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.1f second on hit    ", bot1.attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.2fX crit damage    ", bot1.critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%i%% crit chance    ", bot1.critical_chanse); break; 
		case 1:  printf("%.0f health     ", bot2.health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
			printf("%.0f damage     ", bot2.damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f magical damage     ", bot2.mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f mana     ", bot2.mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% magic protect     ", bot2.magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% armor    ", bot2.armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.1f second on hit    ", bot2.attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.2fX crit damage    ", bot2.critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%i%% crit chance    ", bot2.critical_chanse); break;
		case 2:  printf("%.0f health     ", bot3.health); pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
			printf("%.0f damage     ", bot3.damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f magical damage     ", bot3.mag_damage);pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f mana     ", bot3.mana); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% magic protect     ", bot3.magic_protect); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.0f%% armor    ", bot3.armor); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.1f second on hit    ", bot3.attack_speed); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%.2fX crit damage    ", bot3.critical_damage); pos.Y++; SetConsoleCursorPosition(hConsole, pos);
			printf("%i%% crit chance    ", bot3.critical_chanse); break;
	}
}
int battle(struct Hero * hero, struct Hero * bot1, struct Hero * bot2, struct Hero * bot3)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char * Interface[3] = {
		"Mage         ",
		"Guard        ",
		"Dark Knight  "
	};
	int a = move(hConsole, 3,Interface, 3, hero, bot1, bot2, bot3);
	clock_t start1 = clock();
	clock_t start2 = clock();
	struct Hero * bot;
	int true = 1;
	int gold;
	int rnd;
	switch (a){
		case 0 : bot = bot1; gold = 90 + rand() % 10; break;
		case 1 : bot = bot2; gold = 90 + rand() % 10; break;
		case 2 : bot = bot3; gold = 200 + rand() % 10; break;
		case 100 : return 2;
	}
	hero->curent_health = hero->health;
	bot->curent_health = bot->health;
	hero->curent_mana = hero->mana;
	bot->curent_mana = bot->mana;
	bot->health *= 1.1;
	bot->damage *= 1.05;
	bot->mag_damage *=1.06;
	system("cls");
	float damage;
	int stan = 0;
	char str[35];
	while (true)
	{
		str[0] = '\0';
		if ((clock() - start1) > hero->attack_speed * CLOCKS_PER_SEC)
		{
			rnd = rand() % 100;
			damage = hero->damage * (100 - bot->armor) / 100 + hero->mag_damage * (100 - bot->magic_protect) / 100 + rand() % 5;
			if (rnd < hero->critical_chanse)
				damage *= hero->critical_damage;
			if (hero->class == MAGE)
			{
				stan++;
				if (stan % 5 == 0 && hero->curent_mana > 195){
					start2 += 2 * CLOCKS_PER_SEC;
					hero->curent_mana -= 195;
					sprintf(str, "freeze, your mana is %.0f\0", hero->curent_mana);
				}
			}
			if (hero->class == THIEF)
			{
				stan++;
				if (stan % 2 == 0){
					hero->curent_health += damage * 0.25;
					sprintf(str, "vampire %.0f\0", damage * 0.25);
				}
			}
			start1 += hero->attack_speed * CLOCKS_PER_SEC;
			bot->curent_health -= damage;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			printf("you hit %.0f damage\tenemy health is %.0f\t", damage, bot->curent_health);
			puts(str);
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		if (bot->curent_health < 0)
		{
			hero->gold += gold;
			return 1;
		}
		if ((clock() - start2) > bot->attack_speed * CLOCKS_PER_SEC)
		{
			
			rnd = rand() % 100;
			damage = (bot->damage * (100 - hero->armor)) / 100 + (bot->mag_damage * (100 - hero->magic_protect)) / 100 + rand() % 5;
			if (rnd < bot->critical_chanse)
				damage *= bot->critical_damage;
			if (hero->class == WARRIOR)
			{
				stan++;
				if (stan % 3 == 0){
					damage *= 0.5;
					sprintf(str, "block\0");
				}
			}
			hero->curent_health -= damage;
			start2 += bot->attack_speed * CLOCKS_PER_SEC;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("you caused %.0f damage\tyour health is %.0f\n", damage, hero->curent_health);
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		if (hero->curent_health < 0)
			return 0;
		
		
	}
	
}
void printRec()
{
	system("cls");
	int record;
	char nick[20];
	FILE * fp = NULL;
	fp = fopen("reclab4.txt", "r");
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
void save(struct Hero * hero)
{
	FILE * fp = NULL;
	system("cls");
	printf("enter full name of file in what you will save\n");
	char str[30];
	gets(str);
	fp = fopen(str, "w");
	if (NULL == fp)
		return;
	if (hero->Weapon == NULL && hero->Armor == NULL)
		fprintf(fp, "%i %i %i %i", hero->class, -1, -1, hero->gold);
	else if (hero->Weapon == NULL)
		fprintf(fp, "%i %i %i %i", hero->class, -1, hero->Armor->type, hero->gold);
	else if (hero->Armor == NULL)
		fprintf(fp, "%i %i %i %i", hero->class, hero->Weapon->type, -1, hero->gold);
	else
		fprintf(fp, "%i %i %i %i", hero->class, hero->Weapon->type, hero->Armor->type, hero->gold);
	fclose(fp);
}
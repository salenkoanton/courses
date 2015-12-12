#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
struct Statrup {
	char name[20];
	char spec[20];
	char country[20];
};
struct Founder {
	char name[20];
	struct Statrup * startup;
};
void found(int size, struct Founder * fnd);
void fillStruct (struct Founder * imp, struct Statrup * stu);
void usually(struct Founder * imp, struct Statrup * stu);
struct Founder * create ();
void delete (struct Founder * fnd);
void printS (struct Founder * fnd);
int main()
{
	struct Statrup * allS = NULL;
	allS = malloc(sizeof(struct Statrup) * 3);
	struct Founder * allI = NULL;
	allI = malloc(sizeof(struct Founder) * 3);
	if (NULL == allI || NULL == allS)
		return 1;
	for (int i = 0; i < 3; i++)
		fillStruct(allI + i, allS + i);
	usually(allI, allS);
	printS(allI);
	printS(allI + 2);
	found(3, allI);
	free(allS);
	free(allI);
	
	return 0;
}
void fillStruct (struct Founder * imp, struct Statrup * stu)
{
	imp->startup = stu;
	printf("enter name of startup\n");
	gets(stu->name);
	printf("enter specialisation of startup\n");
	gets(stu->spec);
	printf("enter country, where startup was create\n");
	gets(stu->country);
	printf("enter name of founder of this startup\n");
	gets(imp->name);
}

void usually(struct Founder * imp, struct Statrup * stu)
{
	char str[4][20] = {"no name",
		"no spec",
		"no country",
		"no name"};
	imp->startup = stu;
	strcpy(stu->name, str[0]);
	strcpy(stu->spec, str[0]);
	strcpy(stu->country, str[0]);
	strcpy(imp->name, str[0]);
}

struct Founder * create ()
{
	struct Statrup * stu = NULL;
	struct Founder * fnd = NULL;
	stu = malloc (sizeof(struct Statrup));
	fnd = malloc (sizeof(struct Founder));
	if (stu == NULL || fnd == NULL)
		return NULL;
	fnd->startup = stu;
	return fnd;
}

void delete (struct Founder * fnd)
{
	free(fnd->startup);
	free(fnd);
}

void printS (struct Founder * fnd)
{
	printf ("sturtup name - ");
	puts(fnd->startup->name);
	
	printf ("founder name - ");
	puts(fnd->name);
	
	printf ("country - ");
	puts(fnd->startup->country);
	
	printf ("sturtup specialisation - ");
	puts(fnd->startup->spec);
}

void found(int size, struct Founder * fnd)
{
	for (int i = 0; i < size; i++)
	if (strcmp((fnd + i)->startup->country, "america") == 0)
		if (strcmp((fnd + i)->startup->spec, "IoT") == 0)
		{
			puts("he is from america and it is IoT");
			printS(fnd + i);
		}
}


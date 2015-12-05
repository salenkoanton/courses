#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Post {
	char theme[20];
	char text[100];
	int numberOfKomments;
};

int countKomments(size_t size, struct Post str[size]);
void change(struct Post * str, const char * newText);
void print(struct Post str);
int main(void)
{
	char ch[100];
	size_t size;
	printf("vvedit kilkist postiv\n");
	if(!scanf("%u", &size))
		return 1;
	struct Post PZKShumor[size];
	for(unsigned i = 0; i < size; i++)
	{
		printf("vvedit temu\n");
		fflush(stdin);
		gets(PZKShumor[i].theme);
		fflush(stdin);
		printf("vvedit text\n");
		gets(PZKShumor[i].text);
		fflush(stdin);
		printf("vvedit kilkist komentiv\n");
		scanf("%i", &PZKShumor[i].numberOfKomments);
	}
	printf("kilkist postiv iz bilsh nizh 10: %i\n", countKomments(size, PZKShumor));
	while (1){
	printf("vvedit nomer posta shchob print i zminyty jogo text\nabo vvedit krakozjabry shchob vyjty\n");
	if(!scanf("%u", &size))
		return 0;
	print(PZKShumor[size]);
	printf("vvedit novyy text\n");
	fflush(stdin);
	gets(ch);
	change(&(PZKShumor[size]), ch);
	print(PZKShumor[size]);
	}
	return 0;
}

int countKomments(size_t size, struct Post str[size])
{
	int cnt = 0;
	for (int i = 0; i < size; i++)
		if (str[i].numberOfKomments > 10)
			cnt++;
	return cnt;
}

void change(struct Post * str, const char * newText)
{
	strcpy(str->text, newText);
}

void print(struct Post str)
{
	puts("tema:");
	puts(str.theme);
	puts("text:");
	puts(str.text);
	printf("number of coments: %i\n", str.numberOfKomments);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef int (*LogCallback)(char ch1, char ch2, char ch3);
typedef void (*LogCallback1)(char * ch1, char * ch2, char * ch3);
void alert_func2 (char * ch1, char * ch2, char * ch3);
int check_func1 (char ch1, char ch2, char ch3);
void alert_func1 (char * ch1, char * ch2, char * ch3);
int check_func2 (char ch1, char ch2, char ch3);
void check(char * str, LogCallback checkCB, LogCallback1 alertCB);

int main(void)
{
    LogCallback check1 = check_func1;
    LogCallback check2 = check_func2;
    LogCallback1 alert1 = alert_func1;
    LogCallback1 alert2 = alert_func2;
    char str[100];
    gets(str);
    check(str, check1, alert1);
    check(str, check2, alert2);
    puts(str);


    return 0;
}

void check(char * str, LogCallback checkCB, LogCallback1 alertCB)
{
    for (int i = 2; i < strlen(str); i++)
    {
        if (checkCB(str[i - 2], str[i - 1], str[i]) == 1)
            alertCB((&str[i - 2]), (&str[i - 1]), &(str[i]));
    }
}

int check_func1 (char ch1, char ch2, char ch3)
{
    if (ch1 == ch2 && ch1 == ch3)
        return 1;
    return 0;
}

int check_func2 (char ch1, char ch2, char ch3)
{
    if (ch1 == ch2 + 1 && ch1 == ch3 + 2 || ch1 == ch2 - 1 && ch1 == ch3 - 2 )
        return 1;
    return 0;
}

void alert_func1 (char * ch1, char * ch2, char * ch3)
{
    *ch1 = '0';
    *ch2 = '0';
    *ch3 = '0';
}

void alert_func2 (char * ch1, char * ch2, char * ch3)
{
    *ch1 = 'G';
    *ch2 = 'O';
    *ch3 = 'D';
}

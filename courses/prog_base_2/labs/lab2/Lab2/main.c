#include <stdio.h>
typedef struct words_s words_t;
words_t * senToWords(char * str);
#include <windows.h>

words_t * words_new (char ** words, int count);
int words_count (words_t * self);
char * word_get (words_t * self, int pos);

typedef int (*cmp_f)(words_t * words);
typedef void (*react_f)(words_t * words);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;
dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);




const char * userChoice();
int main(void)
{
    int i = 9;
    int j = 10;
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
     printf("Dynamic loaded!\n");
     fflush(stdin);

    char str[100];
    gets(str);
    words_t * words = senToWords(str);
    printf("Dynamic loaded!\n");
    /*for (int i = 0; words[i] != NULL; i++)
        puts(words[i]);*/
    if (words != NULL)
    if (dll->cmp(words))
        dll->react(words);
    /*if (words[0] == NULL)
        printf("NULL\n");*/
    /*if (dll->cmp(words))
        dll->react(words);*/
    /*if (words[0] == NULL)
        printf("NULL\n");*/
    /*for (int i = 0; i < words_count(words); i++)
        puts(word_get(words, i));*/
    return 0;
}

words_t * senToWords(char * str)
{
    static char ** words = NULL;
    static int wordscount = 1;
    if (strlen(str) == 0)
    {
        printf("string is empty\n");
        return NULL;
    }
    if (words != NULL)
    {
        for (int i = 0; i < wordscount; i++)
            free(words[i]);
        free(words);
        printf("NEW\n");
    }
    wordscount = 1;
    int flag = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ' && flag)
        {
            flag = 0;
            wordscount++;
        }
        if (str[i] != ' ')
            flag = 1;
        if (str[i] == ' ' && str[i + 1] == '\0')
            wordscount--;
    }
    printf("%i\n", wordscount);


    words = malloc(sizeof(char *) * (wordscount + 1));
    char * word;
    word = strtok(str, " ");

    for (int i = 0; i < wordscount; i++)
    {
        words[i] = malloc(sizeof(char) * strlen(word));
        strcpy(words[i], word);
        word = NULL;
        while(word == NULL && i < wordscount - 1)
            if (i == wordscount - 1 && flag)
                break;
            else
                word = strtok(NULL, " ");

    }
    words[wordscount] = NULL;
    if (words[0] == NULL)
        exit(1);
    words_t * self = words_new(words, wordscount);
    return self;
}


const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "check");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}

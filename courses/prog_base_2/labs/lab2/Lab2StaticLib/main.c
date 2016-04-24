// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the static library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.

// A function adding two integers and returning the result
#include <stdlib.h>
#include <string.h>

struct word_s
{
    char * word;
    int length;
};
struct words_s{
    struct word_s * words;
    int length;
};
//typedef struct word_s word_t;
typedef struct words_s words_t;


words_t * words_new (char ** words, int count)
{
    words_t * self = malloc(sizeof(struct words_s));
    self->words = malloc (sizeof(struct word_s) * count);
    self->length = count;
    for (int i = 0; i < count; i++)
    {
        self->words[i].word = malloc(sizeof(char) * strlen(words[i]));
        self->words[i].length = strlen(words[i]);
        strcpy(self->words[i].word, words[i]);
    }
    return self;
}
// A function doing nothing ;)
char * word_get (words_t * self, int pos)
{
    if (pos < self->length && pos >= 0)
        return self->words[pos].word;
    return NULL;
}

void words_free (words_t * words)
{
    for (int i = 0; i < words->length; i++)
        free(words->words[i].word);
    free(words->words);
    free(words);
}

int words_count (words_t * self)
{
    return self->length;
}
// A function always returning zero
int SampleFunction2()
{
    // insert code here

    return 0;
}

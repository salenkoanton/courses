#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED

typedef struct words_s words_t;
words_t * words_new (char ** words, int count);
char * word_get (words_t * self, int pos);
int words_count (words_t * self);

void words_free (words_t * words);


#endif // WORDS_H_INCLUDED

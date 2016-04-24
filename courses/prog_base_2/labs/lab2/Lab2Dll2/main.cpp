#include "main.h"
#include <stdlib.h>
#include <stdio.h>
// a sample exported function

void reaction2(char ** words)
{
    int i;
    for (i = 0; words[i] != NULL; i++)
        puts(words[i]);
    for (int j = i - 1; j >= 0; j--)
        free(words[i]);
    realloc(words, sizeof(char *));
    *words = NULL;
}

int DLL_EXPORT check(words_t * words) {
    return words_count(words) > 4;
}
void DLL_EXPORT reaction(words_t * words) {

    for (int i = 0; i < words_count(words); i++)
        puts(word_get(words, i));
    words_free(words);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}

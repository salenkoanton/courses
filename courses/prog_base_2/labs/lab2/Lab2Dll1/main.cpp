#include "main.h"
//#include "words.h"
#include <stdio.h>
#include <string.h>

// a sample exported function
int DLL_EXPORT check(words_t * words) {
    if (words_count(words) == 0)
        return 0;
    return strlen(word_get(words, words_count(words) - 1)) > 5;
}
void DLL_EXPORT reaction(words_t * words) {

    if (words_count(words) == 0)
    {
        puts("there are no words\n");
        return;
    }
    printf("last word: ");
    puts(word_get(words, words_count(words) - 1));
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

#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "words.h"

int DLL_EXPORT check(words_t * words);
void DLL_EXPORT reaction(words_t * words);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__

#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED
#ifndef WIN_IS_DEF
#define WIN_IS_DEF
#include <windows.h>
#endif
#ifndef HMUTEX_DEF
#define HMUTEX_DEF
  HANDLE hMutex;
#endif // RANDOMIZER_H_INCLUDED
HANDLE * randomizer_new(int size, int * value);
void randomizer_del(HANDLE * consumers, int size);

#endif // RANDOMIZER_H_INCLUDED

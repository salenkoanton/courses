#ifndef ZERO_WRITER_H_INCLUDED
#define ZERO_WRITER_H_INCLUDED
#ifndef WIN_IS_DEF
#define WIN_IS_DEF
#include <windows.h>
#endif
#ifndef HMUTEX_DEF
#define HMUTEX_DEF
  HANDLE hMutex;
#endif // RANDOMIZER_H_INCLUDED
HANDLE * zeroWriter_new(int size, int * value);
void zeroWriter_del(HANDLE * consumers, int size);


#endif // ZERO_WRITER_H_INCLUDED

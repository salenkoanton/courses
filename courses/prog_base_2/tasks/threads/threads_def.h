#ifndef THREADS_DEF_H_INCLUDED
#define THREADS_DEF_H_INCLUDED
#ifndef WIN_IS_DEF
#define WIN_IS_DEF
#include <windows.h>
#endif
HANDLE newThread(LPTHREAD_START_ROUTINE routine, int * ctx);


#endif // THREADS_DEF_H_INCLUDED

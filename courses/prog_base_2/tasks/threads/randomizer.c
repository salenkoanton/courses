#include "randomizer.h"

#include "threads_def.h"
DWORD randomizer(LPVOID args) {
    int * param = (int *)args;
    while (TRUE) {
                WaitForSingleObject(hMutex, INFINITE);
        (*param) = rand() % 21 - 10;
        ReleaseMutex(hMutex);
        Sleep(1);
    }
}

void randomizer_del(HANDLE * consumers, int size){
    for (int i = 0; i < size; i++)
        CloseHandle(consumers[i]);
}

HANDLE * randomizer_new(int size, int * value){
    HANDLE * consumers = malloc(sizeof(HANDLE) * size);
    for(int i = 0; i < size; i++)
        consumers[i] = newThread(randomizer, &value);
    return consumers;
}

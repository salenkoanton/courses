#include "zero_writer.h"
#include "threads_def.h"
DWORD zero_writer(LPVOID args) {


    while (TRUE){
            // Windows handle type
                  // unnamed mutex
   int * param = (int *)args;

    WaitForSingleObject(hMutex, INFINITE); // Request ownership of mutex
    if(*param == 0){

        Sleep(20);
        printf("%i", *param);
        }
    ReleaseMutex(hMutex);

    }

}

void zeroWriter_del(HANDLE * consumers, int size){
    for (int i = 0; i < size; i++)
        CloseHandle(consumers[i]);
}

HANDLE * zeroWriter_new(int size, int * value){
    HANDLE consumers[size];
    for(int i = 0; i < size; i++)
        consumers[i] = newThread(zero_writer, &value);
    return consumers;
}

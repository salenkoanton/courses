#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "zero_writer.h"
#include "randomizer.h"



int main(void) {
    srand(time(NULL));
    int value = 0;
    hMutex = CreateMutex(
        NULL,
        FALSE,
        NULL);
    HANDLE * first_thread = randomizer_new(5, &value);
    HANDLE * second_thread = zeroWriter_new(2, &value);
    while (!_kbhit());
    randomizer_del(first_thread, 5);
    zeroWriter_del(second_thread, 2);
    CloseHandle(hMutex);
    _getch();
    system("cls");
    return 0;
}









#ifndef DLLMANAGER
#define DLLMANAGER
#include <windows.h>
#include <stdlib.h>
#include "enums.h"
#include "list.h"
typedef enum moves (*bot_f)(list_t * moves_list, bool up, bool right, bool down, bool left);

class DLLManager{
private:
    HINSTANCE hLib;
    bot_f bot;
    List * list;
public:
    DLLManager (const wchar_t * dllName)
    {
        hLib = LoadLibrary(dllName);
        bot = NULL;
        if (NULL == hLib)
            exit(3);
        if (NULL != hLib) {
            bot = (bot_f)GetProcAddress(hLib, "bot");
        }
        list = new List((list_size_f)GetProcAddress(hLib, "list_size"), (list_change_f)GetProcAddress(hLib, "list_change"), (list_del_f)GetProcAddress(hLib, "list_del"), (list_get_f)GetProcAddress(hLib, "list_get"), (list_new_f)GetProcAddress(hLib, "list_new"), (list_add_f)GetProcAddress(hLib, "list_add"), (list_free_f)GetProcAddress(hLib, "list_free"));
    }
    bot_f get_bot()
    {
        return bot;
    }
    List * get_list()
    {
        return list;
    }

    ~DLLManager ()
    {
        delete list;
        FreeLibrary((HMODULE)hLib);
    }
};

#endif // DLLMANAGER


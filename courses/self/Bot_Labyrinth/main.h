#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include "enums.h"
#include "list.h"
/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

enum moves DLL_EXPORT bot(list_t * list, bool up, bool right, bool down, bool left);

int DLL_EXPORT list_size(list_t * list);
enum moves DLL_EXPORT list_change(list_t * list, enum moves data, int pos);
enum moves DLL_EXPORT list_del(list_t * list, int pos);
void DLL_EXPORT list_add(list_t * list, enum moves data, int pos);
list_t * DLL_EXPORT list_new();
enum moves DLL_EXPORT list_get(list_t * list, int pos);
void DLL_EXPORT list_free(list_t * list);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__

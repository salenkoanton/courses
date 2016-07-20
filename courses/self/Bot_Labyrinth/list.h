#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "enums.h"
typedef struct list_s list_t;/*
int list_size(list_t * list);
enum moves list_change(list_t * list, enum moves data, int pos);
enum moves list_del(list_t * list, int pos);
void list_add(list_t * list, enum moves data, int pos);
list_t * list_new();
enum moves list_get(list_t * list, int pos);
*/
#endif // LIST_H_INCLUDED


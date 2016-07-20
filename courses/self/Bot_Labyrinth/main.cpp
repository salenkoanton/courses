#include "main.h"
#include "list.h"
// a sample exported function
enum moves DLL_EXPORT bot(list_t * list, bool up, bool right, bool down, bool left)
{
    enum moves result;
    if (up)
        result = UP;
    else if (left)
        result = LEFT;
    else if (down)
        result = DOWN;
    else if (right)
        result = RIGHT;
    else result = NO_MOVE;
    list_add(list, result, 0);
    return result;
}
#include <stdlib.h>
#include "list.h"


struct list_node_s{
    struct list_node_s * next;
    struct list_node_s * prev;
    enum moves data;
};

struct list_s{
    struct list_node_s * head;
    struct list_node_s * tail;
    int size;
};

enum moves DLL_EXPORT list_get(list_t * list, int pos)
{
    struct list_node_s * cur_node = list->head->next;
    if (list->tail == cur_node)
        return NO_MOVE;
    if (pos >= list->size )
    {
        pos = list->size - 1;
    }
    for (int i = 0; i < pos; i++)
        cur_node = cur_node->next;
    return cur_node->data;

}

list_t * DLL_EXPORT list_new ()
{
    list_t * list = (list_t *)malloc(sizeof(struct list_s));
    list->head = (list_node_s *)malloc(sizeof(struct list_node_s));
    list->tail = (list_node_s *)malloc(sizeof(struct list_node_s));
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->size = 0;
    return list;
}

void DLL_EXPORT list_add(list_t * list, enum moves data, int pos)
{
    struct list_node_s * new_node = (list_node_s *)malloc(sizeof(struct list_node_s));
    struct list_node_s * cur_node = list->head;
    if (list->size < pos)
        pos = list->size;
    for (int i = 0; i < pos; i++)
    {
        cur_node = cur_node->next;
    }
    new_node->data = data;
    new_node->prev = cur_node;
    new_node->next = cur_node->next;
    cur_node->next->prev = new_node;
    cur_node->next = new_node;
    list->size++;
}

enum moves DLL_EXPORT list_del(list_t * list, int pos)
{
    enum moves data;
    struct list_node_s * cur_node = list->head->next;
    if (list->tail == cur_node)
        return NO_MOVE;
    if (pos >= list->size )
    {
        pos = list->size - 1;
    }
    for (int i = 0; i < pos; i++)
        cur_node = cur_node->next;
    data = cur_node->data;
    cur_node->prev->next = cur_node->next;
    cur_node->next->prev = cur_node->prev;
    free(cur_node);
    list->size--;
    return data;
}

enum moves DLL_EXPORT list_change(list_t * list, enum moves data, int pos)
{
    enum moves tmp_data;
    struct list_node_s * cur_node = list->head->next;
    if (list->tail == cur_node)
        return NO_MOVE;
    if (pos >= list->size )
    {
        pos = list->size - 1;
    }
    for (int i = 0; i < pos; i++)
        cur_node = cur_node->next;
    tmp_data = cur_node->data;
    cur_node->data = data;
    return tmp_data;
}

int DLL_EXPORT list_size(list_t * list)
{
    return list->size;
}

void DLL_EXPORT list_free(list_t * list)
{
    for (int i = 0; i < list->size; i++)
        list_del(list, 0);
    free(list->tail);
    free(list->head);
    free(list);
}



extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}

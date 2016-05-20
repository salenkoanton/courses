#include <stdlib.h>
#include "list.h"
#include "event.h"

struct list_node_s{
    struct list_node_s * next;
    struct list_node_s * prev;
    int data;
};

struct list_s{
    struct list_node_s * head;
    struct list_node_s * tail;
    int size;
    events_t events;
};

list_t list_new ()
{
    list_t list = malloc(sizeof(struct list_s));
    list->head = malloc(sizeof(struct list_node_s));
    list->tail = malloc(sizeof(struct list_node_s));
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->size = 0;
    list->events = events_new();
    return list;
}

void list_add(list_t list, int data, int pos)
{
    struct list_node_s * new_node = malloc(sizeof(struct list_node_s));

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
    events_add(list->events, data, pos);
    list_sum_check(list);
}

int list_del(list_t list, int pos)
{
    int data;
    struct list_node_s * cur_node = list->head->next;
    if (list->tail == cur_node)
        return INT_MIN;
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
    events_del(list->events, data, pos);
    list_sum_check(list);
    return data;
}

int list_sum_check(list_t list){
    struct list_node_s * cur_node = list->head->next;
    int sum = 0;
    for (int i = 0; i < list->size; i++)
    {
        sum += cur_node->data;
        cur_node = cur_node->next;
    }
    if (sum > 100)
        events_sum(list->events);
}

int list_change(list_t list, int data, int pos)
{
    int tmp_data;
    struct list_node_s * cur_node = list->head->next;
    if (list->tail == cur_node)
        return INT_MIN;
    if (pos >= list->size )
    {
        pos = list->size - 1;
    }
    for (int i = 0; i < pos; i++)
        cur_node = cur_node->next;
    tmp_data = cur_node->data;
    cur_node->data = data;
    events_change(list->events, tmp_data, data, pos);
    list_sum_check(list);
    return tmp_data;
}

events_t list_get_events(list_t list)
{
    return list->events;
}

int list_size(list_t list)
{
    return list->size;
}

void list_free(list_t list)
{
    for (int i = 0; i < list->size; i++)
        list_del(list, 0);
    free(list->tail);
    free(list->head);
    free(list);
}



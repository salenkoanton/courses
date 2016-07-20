#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "enums.h"
struct list_node_s{
    struct list_node_s * next;
    struct list_node_s * prev;
    enum moves data;
};
typedef struct list_s{
    struct list_node_s * head;
    struct list_node_s * tail;
    int size;
} list_t;
typedef int (*list_size_f)(list_t * list);
typedef enum moves (*list_change_f)(list_t * list, enum moves data, int pos);
typedef enum moves (*list_del_f)(list_t * list, int pos);
typedef void (*list_add_f)(list_t * list, enum moves data, int pos);
typedef list_t * (*list_new_f)(void);
typedef enum moves (*list_get_f)(list_t * list, int pos);
typedef void (*list_free_f)(list_t * list);
class List{
private:
    list_size_f list_size;
    list_change_f list_change;
    list_del_f list_del;
    list_get_f list_get;
    list_new_f list_new;
    list_add_f list_add;
    list_free_f list_free;
    list_t * list;
public:
    List(list_size_f list_size, list_change_f list_change, list_del_f list_del, list_get_f list_get, list_new_f list_new, list_add_f list_add, list_free_f list_free)
    {
        if (list_add == NULL)
            exit(5);
        if (list_size == NULL)
            exit(6);
        if (list_change == NULL)
            exit(7);
        if (list_free == NULL)
            exit(8);
        if (list_get == NULL)
            exit(9);
        if (list_new == NULL)
            exit(10);
        if (list_del == NULL)
            exit(11);
        this->list_add = list_add;
        this->list_size = list_size;
        this->list_change = list_change;
        this->list_del = list_del;
        this->list_new = list_new;
        this->list_get = list_get;
        this->list_free = list_free;
        list = list_new();
    }
    ~List()
    {
        list_free(list);
    }
    list_t * get_list()
    {
        return list;
    }

    void add(enum moves data, int pos)
    {
        list_add(list, data, pos);
    }

    enum moves get(int pos)
    {
        return list_get(list, pos);
    }

    enum moves del(int pos)
    {
        return list_del(list, pos);
    }

    enum moves change(enum moves data, int pos)
    {
        return list_change(list, data, pos);
    }

    void refresh()
    {
        list_free(list);
        list = list_new();
    }

    int size()
    {
        return list_size(list);
    }

};

#endif // LIST_H_INCLUDED


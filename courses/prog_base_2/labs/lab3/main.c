#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "event.h"
#include "user.h"
void ev_add(int data, int pos){
    printf ("user 1 knows add elem %i in %i pos\n\n", data, pos);
}

void ev_add1(int data, int pos){
    printf ("user 2 knows add elem %i in %i pos\n\n", data, pos);
}

void ev_del(int data, int pos){
    printf ("user 2 knows del elem %i in %i pos\n\n", data, pos);
}

void ev_change(int bef_data, int cur_data, int pos){
    printf ("user 1 knows change %i on %i in %i\n\n", bef_data, cur_data, pos);
}

void ev_sum()
{
   printf ("user 2 knows sum\n\n");
}

int main()
{
    list_t list = list_new();
    user_t user = user_new(1);
    user_add_subscribe(user, ev_add, list);
    user_t user1 = user_new(2);
    user_change_subscribe(user, ev_change, list);
    user_add_subscribe(user1, ev_add1, list);
    user_del_subscribe(user1, ev_del, list);
    user_sum_subscribe(user1, ev_sum, list);
    for(int i = 0; i < 20; i++)
    {
        list_add(list, i, i);
    }
    for (int i = 0; i < 10; i++)
    {
        list_change(list, i + 10, i);
    }
    for (int i = 0; i < 15; i++)
    {
        list_del(list, 2);
    }
    return 0;
}

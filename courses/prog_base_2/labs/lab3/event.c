#include "event.h"
#include <stdlib.h>
#include <stdio.h>

struct events_s{
    user_t users[5];
};

events_t events_new()
{
    events_t events = malloc(sizeof(struct events_s));
    for (int i = 0; i < 5; i++)
    {
        events->users[i] = NULL;
    }
    return events;
}

int events_contains_user(events_t events, user_t user)
{
    for (int i = 0; i < 5; i++)
        if (events->users[i] == user)
            return 1;
    return 0;
}

void events_add_user(events_t events, user_t user)
{
    for (int i = 0; i < 5; i++)
        if (events->users[i] == NULL)
        {
            events->users[i] = user;
            break;
        }
}

void events_add(events_t ev, int data, int pos)
{
    for (int i = 0; i < 5; i++)
        if (user_add(ev->users[i]) != NULL)
            user_add(ev->users[i])(data, pos);
}

void events_del(events_t ev, int data, int pos)
{
    for (int i = 0; i < 5; i++)
        if (user_del(ev->users[i]) != NULL)
            user_del(ev->users[i])(data, pos);
}

void events_change(events_t ev, int bef_data, int cur_data, int pos)
{
    for (int i = 0; i < 5; i++)
        if (user_change(ev->users[i]) != NULL)
            user_change(ev->users[i])(bef_data, cur_data, pos);
}

void events_sum(events_t ev)
{
    for (int i = 0; i < 5; i++)
        if (user_sum(ev->users[i]) != NULL)
            user_sum(ev->users[i])();
}

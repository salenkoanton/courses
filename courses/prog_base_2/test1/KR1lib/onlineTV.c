#include <string.h>
#include <stdlib.h>
#include "onlineTV.h"
#include "list.h"
struct onlineTV_s {
    list_t playlist;
    char * nameTV;
    list_t watchers;
    list_t history;
};
struct history_s{
    watcher_t * watcher;
    int time;
    int in_off;
};

struct video_s{
    int type;
    char * name;
};

struct watcher_s{
    int id;
    callb callback;
};

void event(onlineTV_t tv)
{
    for (int i = 0; i < list_size(tv->watchers); i++)
        ((watcher_t *)list_get(tv->watchers, i))->callback(get_cur_video(tv));
}

watcher_t * watcher_new(int id, callb callback)
{
    watcher_t * watc = malloc(sizeof(struct watcher_s));
    watc->id = id;
    watc->callback = callback;
    return watc;
}
int watcher_get_id(watcher_t * self)
{
    return self->id;
}
onlineTV_t onlineTV_new()
{
    onlineTV_t tv = malloc(sizeof(struct onlineTV_s));
    tv->nameTV = NULL;
    tv->watchers = list_new();
    tv->playlist = list_new();
    tv->history = list_new();
    return tv;
}

void onlineTV_set_name(onlineTV_t tv, char * name)
{
    if (tv->nameTV != NULL)
        free(tv->nameTV);
    tv->nameTV = malloc(sizeof(char) * strlen(name));
    strcpy(tv->nameTV, name);
}

char * onlineTV_get_name(onlineTV_t tv)
{
    return tv->nameTV;
}

watcher_t * onlineTV_get_watcher(onlineTV_t tv, int pos)
{
    if (pos >= list_size(tv->watchers))
        return NULL;
    return list_get(tv->watchers, pos);
}

int onlineTV_get_count_watchers(onlineTV_t tv)
{
    return list_size(tv->watchers);
}

video_t * video_new(int type, char * name)
{
    video_t * video = malloc(sizeof(struct video_s));
    video->type = type;
    video->name = malloc(sizeof(char) * strlen(name));
    strcpy(video->name, name);
    return video;
}

char * video_get_name(video_t * video)
{
    return video->name;
}

void tv_add_video(onlineTV_t tv, int type, char * name)
{
    video_t * video = video_new(type, name);
    list_add(tv->playlist, video, 0);
}

video_t * get_cur_video(onlineTV_t tv)
{
    return (video_t *)list_get(tv->playlist, list_size(tv->playlist) - 1);
}

void del_video (onlineTV_t tv, int pos)
{
    list_del(tv->playlist, pos);
}

void next_video (onlineTV_t tv)
{
    list_del(tv->playlist, list_size(tv->playlist) - 1);
    if(((video_t *)list_get(tv->playlist, list_size(tv->playlist) - 1))->type == 1) // 1 це тип відео, 0 - реклама
        event(tv);
}

list_t get_playlist(onlineTV_t tv)
{
    list_t list = list_new();
    for (int i = 0; i < list_size(tv->playlist); i++)
        list_add(list, list_get(tv->playlist, i), i);
    return tv->playlist;
}

history_t * history_new(watcher_t * watcher, int time, int in_off)
{
    history_t * hist = malloc(sizeof(struct history_s));
    hist->in_off = in_off;
    hist->time = time;
    hist->watcher = watcher;
    return hist;
}

void add_watcher_from_list(onlineTV_t tv, list_t list, int pos, int time)
{
    history_t * hist = history_new(list_get(list, pos), time, 1);
    list_add(tv->history, hist, 0);
    list_add(tv->watchers, list_get(list, pos), 0);
}

void del_watcher_from_list(onlineTV_t tv, list_t list, int pos, int time)
{
    void * watcher = list_get(list, pos);
    for (int i = 0; i < list_size(tv->watchers); i++)
        if (list_get(tv->watchers, i) == watcher)
        {
            history_t * hist = history_new((watcher_t *)watcher, time, 0);
            list_add(tv->history, hist, 0);
            list_del(tv->watchers, i);
            return;
        }
}

int get_watchers_count (onlineTV_t tv)
{
    return list_size(tv->watchers);
}

list_t get_history (onlineTV_t tv)
{
    list_t list = list_new();
    for (int i = 0; i < list_size(tv->history); i++)
        list_add(list, list_get(tv->history, i), i);
    return list;
}

int history_get_time(history_t * hist)
{
    return hist->time;
}

int history_get_id(history_t * hist)
{
    return hist->watcher->id;
}

int history_get_in_off(history_t * hist)
{
    return hist->in_off;
}




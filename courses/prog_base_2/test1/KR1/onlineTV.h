#ifndef ONLINETV_H_INCLUDED
#define ONLINETV_H_INCLUDED
#include "list.h"
typedef struct onlineTV_s * onlineTV_t;
typedef struct watcher_s watcher_t;
typedef struct history_s history_t;
typedef struct video_s video_t;
typedef void (*callb)(video_t * video);


int history_get_in_off(history_t * hist);
int history_get_id(history_t * hist);
int get_watchers_count (onlineTV_t tv);
list_t get_history (onlineTV_t tv);
int history_get_time(history_t * hist);
void del_watcher_from_list(onlineTV_t tv, list_t list, int pos, int time);
void add_watcher_from_list(onlineTV_t tv, list_t list, int pos, int time);
history_t * history_new(watcher_t * watcher, int time, int in_off);
list_t get_playlist(onlineTV_t tv);
void next_video (onlineTV_t tv);
void del_video (onlineTV_t tv, int pos);
video_t * get_cur_video(onlineTV_t tv);
void tv_add_video(onlineTV_t tv, int type, char * name);
video_t * video_new(int type, char * name);
int onlineTV_get_count_watchers(onlineTV_t tv);
watcher_t * onlineTV_get_watcher(onlineTV_t tv, int pos);
char * onlineTV_get_name(onlineTV_t tv);
void onlineTV_set_name(onlineTV_t tv, char * name);
onlineTV_t onlineTV_new();
int watcher_get_id(watcher_t * self);
watcher_t * watcher_new(int id, callb callback);
char * video_get_name(video_t * video);

#endif // ONLINETV_H_INCLUDED

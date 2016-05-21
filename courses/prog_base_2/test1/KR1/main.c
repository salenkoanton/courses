#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "list.h"
#include "onlineTV.h"

void callback(video_t * video)
{
    printf("another user knows that movie is %s\n", video_get_name(video));
}
void callback1(video_t * video)
{
    printf("user 3 knows about that is %s\n", video_get_name(video));
}

static void test(void **state){
    onlineTV_t tv = onlineTV_new();
    list_t watchers = list_new();
    for(int i = 0; i < 10; i++)
    {
        if (i == 3)
            list_add(watchers, watcher_new(i, callback1), i);
        else
            list_add(watchers, watcher_new(i, callback), i);
    }
    add_watcher_from_list(tv, watchers, 3, 10);
    del_watcher_from_list(tv, watchers, 3, 15);
    add_watcher_from_list(tv, watchers, 4, 25);

    add_watcher_from_list(tv, watchers, 3, 25);
    del_watcher_from_list(tv, watchers, 4, 40);
    del_watcher_from_list(tv, watchers, 3, 50);
    add_watcher_from_list(tv, watchers, 3, 55);
    add_watcher_from_list(tv, watchers, 4, 60);
    list_t hist = get_history(tv);
    for (int i = 0; i < list_size(hist); i++)
    {
        history_t * tmp = (history_t *)list_get(hist, i);

        printf("watcher %i is in/off %i in time %i\n", history_get_id(tmp), history_get_in_off(tmp), history_get_time(tmp));
    }
    tv_add_video(tv, 0, "efear");
    tv_add_video(tv, 1, "Flash");
    tv_add_video(tv, 1, "GOT");
    next_video(tv);
    next_video(tv);


}

static void test1(void **state){
    onlineTV_t tv = onlineTV_new();
    list_t watchers = list_new();
    for(int i = 0; i < 10; i++)
        list_add(watchers, watcher_new(i, callback), i);
    add_watcher_from_list(tv, watchers, 3, 10);
    list_t hist = get_history(tv);
    history_t * tmp = (history_t *)list_get(hist, 0);
    assert_int_equal(history_get_id(tmp), 3);
    assert_int_equal(history_get_time(tmp), 10);
    assert_int_equal(history_get_in_off(tmp), 1);
}

static void test2(void **state){
    onlineTV_t tv = onlineTV_new();
    list_t watchers = list_new();
    for(int i = 0; i < 10; i++)
        list_add(watchers, watcher_new(i, callback), i);
    add_watcher_from_list(tv, watchers, 3, 10);
    del_watcher_from_list(tv, watchers, 3, 15);
    list_t hist = get_history(tv);
    history_t * tmp = (history_t *)list_get(hist, 0); // кожна нома подія записується у 0 позицію спику
    assert_int_equal(history_get_id(tmp), 3);
    assert_int_equal(history_get_time(tmp), 15);
    assert_int_equal(history_get_in_off(tmp), 0);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test),
        cmocka_unit_test(test1),
        cmocka_unit_test(test2),

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

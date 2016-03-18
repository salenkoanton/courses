#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "korpus.h"
static void new_void__korpus_new_true(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_non_null(self);
    korpus_free(self);
}

static void new_void__korpus_audCount(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_int_equal(korpus_audsCount(self), 3);
    korpus_free(self);
}

static void new_void__korpus_aud_take(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_int_equal(korpus_aud_take(self, 1, 1), TRUE);
    assert_int_equal(korpus_aud_take(self, 1, 1), FALSE);
    clock_t time = clock();
    while(clock() < time + CLOCKS_PER_SEC);
    assert_int_equal(korpus_aud_take(self, 1, 1), TRUE);
    korpus_free(self);
}

static void new_void__korpus_aud_isBusy(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_int_equal(korpus_aud_isBusy(self, 1), TRUE);
    assert_int_equal(korpus_aud_take(self, 1, 1), TRUE);
    assert_int_equal(korpus_aud_isBusy(self, 1), FALSE);
    clock_t time = clock();
    while(clock() < time + CLOCKS_PER_SEC);
    assert_int_equal(korpus_aud_isBusy(self, 1), TRUE);
    korpus_free(self);
}

static void new_void__korpus_aud_numberOfSeats(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_int_equal(korpus_aud_numberOfSeats(self, 1), 3);
    korpus_free(self);
}


/*

static void new_void__korpus_new_false(void **state)
{
    int numb = 500000;
    korpus_t * self[numb];
     for (int i = 0; i < numb; i++)
        self[i] = NULL;
    char * name= "nameefvsz";

    int arr[300] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    for (int i = 0; i < numb; i++){
        self[i] = korpus_new(name, 300, arr);
        assert_non_null(self[i]);
        if(i%10000 == 0)
        printf("%i\n", i);
    }
    korpus_free(self);
}
*/


int main(void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void__korpus_new_true),
        cmocka_unit_test(new_void__korpus_audCount),
        cmocka_unit_test(new_void__korpus_aud_isBusy),
        cmocka_unit_test(new_void__korpus_aud_take),
        cmocka_unit_test(new_void__korpus_aud_numberOfSeats),


  /*  cmocka_unit_test(new_void__korpus_new_false),*/
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

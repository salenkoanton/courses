#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "korpus.h"
#include "aud.h"
static void korpus_new_non_null(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_non_null(self);
    korpus_free(self);
}

static void korpus_audCount_true(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    assert_int_equal(korpus_audsCount(self), 3);
    korpus_free(self);
}

static void korpus_audCount_false(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 0;
    int * arr;
    self = korpus_new(name, numb, arr);
    if (self != NULL)
        assert_int_equal(korpus_audsCount(self), 0);
    assert_null(self);
    if (self != NULL)
        korpus_free(self);
}

static void korpus_aud_take_true(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 1);
    assert_int_equal(aud_take(aud, 1), TRUE);
    clock_t time = clock();
    while(clock() < time + CLOCKS_PER_SEC);
    assert_int_equal(aud_take(aud, 1), TRUE);
    korpus_free(self);
}

static void korpus_aud_take_false(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 1);
    assert_int_equal(aud_take(aud, 1), TRUE);
    assert_int_equal(aud_take(aud, 1), FALSE);
    korpus_free(self);
}

static void korpus_aud_isBusy_true(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 1);
    assert_int_equal(aud_isBusy(aud), TRUE);
    assert_int_equal(aud_take(aud, 1), TRUE);
    clock_t time = clock();
    while(clock() < time + CLOCKS_PER_SEC);
    assert_int_equal(aud_isBusy(aud), TRUE);
    korpus_free(self);
}
static void korpus_aud_isBusy_false(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 1);
    assert_int_equal(aud_take(aud, 1), TRUE);
    assert_int_equal(aud_isBusy(aud), FALSE);
    korpus_free(self);
}
static void korpus_aud_numberOfSeats_true(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 1);
    assert_int_equal(aud_numberOfSeats(aud), 3);
    korpus_free(self);
}

static void korpus_aud_numberOfSeats_false(void **state)
{
    korpus_t * self = NULL;
    char * name= "name";
    int numb = 3;
    int arr[3] = {4, 3, 8};
    self = korpus_new(name, numb, arr);
    aud_t * aud = korpus_get_aud(self, 5);

    assert_int_equal(aud_numberOfSeats(aud), -1);
    korpus_free(self);
}



static void korpus_new_null(void **state)
{
    int numb = 500000;
    korpus_t * self[numb];
     for (int i = 0; i < numb; i++)
        self[i] = NULL;
    char * name= "nameefvsz";
    int count = 0;
    int arr[300] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    for (int i = 0; i < numb; i++){
        self[i] = korpus_new(name, 300, arr);
        if (self[i] != NULL)
        assert_non_null(self[i]);
        else
        {
            assert_null(self[i]);
            count = i;
            break;
        }
        if(i%10000 == 0)
        printf("%i korpuses created\n", i);
    }
    for (int i = 0; i < count; i++)
        korpus_free(self[i]);
}



int main(void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(korpus_new_non_null),
        //cmocka_unit_test(korpus_new_null),
        cmocka_unit_test(korpus_audCount_true),
        cmocka_unit_test(korpus_audCount_false),
        cmocka_unit_test(korpus_aud_isBusy_true),
        cmocka_unit_test(korpus_aud_isBusy_false),
        cmocka_unit_test(korpus_aud_take_false),
        cmocka_unit_test(korpus_aud_take_true),
        cmocka_unit_test(korpus_aud_numberOfSeats_true),
        cmocka_unit_test(korpus_aud_numberOfSeats_false),


  /*  cmocka_unit_test(new_void__korpus_new_false),*/
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

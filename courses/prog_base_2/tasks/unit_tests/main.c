#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "array.h"
static void new_void__arr_new__arr_remove(void **state)
{
    arr_t * arr = arr_new(5);
    assert_int_equal(arr_length(arr), 5);
    arr_remove(&arr);
    assert_null(arr);
    arr = arr_new(5000000);
    assert_null(arr);
}

static void new_void__arr_add(void **state)
{
    arr_t * arr = arr_new(5);
    assert_int_equal(arr_add(arr, 3, 10), ARR_OK);
    assert_int_equal(arr_add(arr, 6, 10), ARR_OVERFLOW);
    int elem = 0;
    assert_int_equal(arr_get(arr, 3, &elem), ARR_OK);
    assert_int_equal(elem, 10);
    assert_int_equal(arr_get(arr, 37, &elem), ARR_OVERFLOW);
    arr_remove(&arr);
}

static void new_void__arr_unic(void **state)
{
    arr_t * arr = arr_new(5);
    int mas[] = {1, 5, 6, 7, 1};
    for (int i = 0; i < 5; i++)
        arr_add(arr, i, mas[i]);
    mas[4] = 9;
    arr_t * arr1 = arr_new(5);
    for (int i = 0; i < 5; i++)
        arr_add(arr1, i, mas[i]);
    arr_t * arr2 = arr_unic(arr, arr1);
    int elem = -1;
    arr_get(arr2, 6, &elem);
    assert_int_equal(elem, 7);
    assert_int_equal(arr_length(arr2), arr_count(arr) + arr_count(arr1));

    arr_remove(&arr);
    arr_remove(&arr1);
    arr_remove(&arr2);

}
static void new_void__arr_unic__equal_elem(void **state)
{
    arr_t * arr = arr_new(5);
    int mas[] = {1, 1, 1, 1, 1};
    for (int i = 0; i < 5; i++)
        arr_add(arr, i, mas[i]);
    arr_t * arr1 = arr_new(5);
    for (int i = 0; i < 5; i++)
        arr_add(arr1, i, mas[i]);
    arr_t * arr2 = arr_unic(arr, arr1);
    assert_null(arr2);

    arr_remove(&arr);
    arr_remove(&arr1);
    if(arr2 != NULL)
        arr_remove(&arr2);

}


static void new_void__arr_count(void **state)
{
    arr_t * arr = arr_new(5);
    int mas[] = {1, 7, 6, 7, 1};
    for (int i = 0; i < 5; i++)
        arr_add(arr, i, mas[i]);
    assert_int_equal(1, arr_count(arr));
    arr_remove(&arr);
}

static void new_void__arr_plus__diff_size(void **state)
{
    arr_t * arr = arr_new(10);
    arr_t * arr1 = arr_new(15);
    arr_random(arr, 100);
    arr_random(arr1, 100);
    int elem1 = -1, elem2 = -4;
    arr_t * arr2 = arr_plus(arr, arr1);
    arr_get(arr1, 13, &elem1);
    arr_get(arr2, 13, &elem2);
    assert_int_equal(elem1, elem2);
    arr_remove(&arr);
    arr_remove(&arr1);
    arr_remove(&arr2);
}

static void new_void__arr_plus__equal_size(void **state)
{
    arr_t * arr = arr_new(10);
    arr_t * arr1 = arr_new(10);
    arr_random(arr, 100);
    arr_random(arr1, 100);
    int elem = -1, elem1 = -1, elem2 = -1;
    arr_t * arr2 = arr_plus(arr, arr1);
    arr_get(arr, 3, &elem);
    arr_get(arr1, 3, &elem1);
    arr_get(arr2, 3, &elem2);
    assert_int_equal(elem + elem1, elem2);
    arr_remove(&arr);
    arr_remove(&arr1);
    arr_remove(&arr2);
}

static void new_void__arr_glue(void **state)
{
    arr_t * arr = arr_new(10);
    arr_t * arr1 = arr_new(15);
    arr_random(arr, 10);
    int elem1 = -1;
    int elem2 = -2;
    arr_random(arr1, 10);
    arr_t * arr2 = arr_glue(arr, arr1);
    assert_int_equal(arr_length(arr2), 25);
    arr_get(arr, 3, &elem1);
    arr_get(arr2, 3, &elem2);
    assert_int_equal(elem1, elem2);
    elem1 = -1;
    elem2 = -2;
    arr_get(arr1, 3, &elem1);
    arr_get(arr2, 3 + 10, &elem2);
    assert_int_equal(elem1, elem2);
    arr_remove(&arr);
    arr_remove(&arr1);
    arr_remove(&arr2);
}


int main(void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void__arr_new__arr_remove),
        cmocka_unit_test(new_void__arr_add),
        cmocka_unit_test(new_void__arr_unic),
        cmocka_unit_test(new_void__arr_glue),
        cmocka_unit_test(new_void__arr_unic__equal_elem),
        cmocka_unit_test(new_void__arr_count),
        cmocka_unit_test(new_void__arr_plus__equal_size),
        cmocka_unit_test(new_void__arr_plus__diff_size),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

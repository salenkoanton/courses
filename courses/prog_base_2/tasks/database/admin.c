#include <stdlib.h>
#include <stdio.h>

#include "admin.h"

void admin_print(admin_t * st) {
    printf("Name: %s\nSurname: %s\nBirthbate: %i\nRate: %.3f\nCreating year: %i\nFollowers: %i\n\n",
        st->name, st->surname, st->birthdate, st->rate, st->creating_year, st->followers);
}

void admin_printList(admin_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        admin_print(&arr[i]);
    }
}

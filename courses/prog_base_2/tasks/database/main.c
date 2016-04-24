#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"
#include "admin.h"

int main(void) {
    const char * dbFile = "admin.db";
    admin_t studentList[100];
    db_t * db = db_new(dbFile);

    int countAdmins = db_countAdmins(db);
    printf("Students total: %i\n\n", countAdmins);
    int filterFollowers = 20000;
    int filterYear = 2013;
    int count = db_getStudentsTask(db, filterYear, filterFollowers, studentList, 100);
    printf("Admins with followers > %i and created group > %i year: %i\n\n", filterFollowers, filterYear, count);
    admin_printList(studentList, count);

    /*admin_t * admin = db_getAdminById(db, 3);
    if (admin->id != 3)
        puts("fail");
    admin->creating_year = 1000;
    admin->name[1] = 'b';
    db_updateAdmin(db, admin);
    //db_deleteAdmin(db, 8);
    //db_insertAdmin(db, admin);*/
    db_free(db);
    return 0;
}

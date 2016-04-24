#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>
//#include "sqlite3ext.h"
#include "db_manager.h"
#include "admin.h"

struct db_s {
    sqlite3 * db;
};
static void _fillStudent(sqlite3_stmt * stmt, admin_t * st) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    int birthdate = sqlite3_column_int(stmt, 3);
    double rate = sqlite3_column_double(stmt, 4);
    int creating_year = sqlite3_column_int(stmt, 5);
    int followers = sqlite3_column_int(stmt, 6);
    st->id = id;
    if(name == NULL)
    puts("done");
    strcpy(st->name, (const char *)name);
    strcpy(st->surname, (const char *)surname);
    st->rate = rate;
    st->birthdate = birthdate;
    st->followers = followers;

    st->creating_year = creating_year;

}


db_t * db_new(const char * dbFile) {
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & (self->db));
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self) {
    sqlite3_close(self->db);
    free(self);
}

int db_insertAdmin(db_t * self, admin_t * admin) {
    int newStudentId = -1;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "INSERT INTO admins VALUES (null, ?, ?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, admin->name, strlen(admin->name), NULL);
    sqlite3_bind_text(stmt, 2, admin->surname, strlen(admin->surname), NULL);
    sqlite3_bind_int(stmt, 3, admin->birthdate);
    sqlite3_bind_double(stmt, 4, (double)admin->rate);
    sqlite3_bind_int(stmt, 5, admin->creating_year);
    sqlite3_bind_int(stmt, 6, admin->followers);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select admins\n");
        exit(1);
    }
    return newStudentId;
}

admin_t * db_getAdminById(db_t * self, int id) {
    admin_t * admin = malloc(sizeof(struct admin_s));
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM admins WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select admins\n");
        exit(1);
    } else
        _fillStudent(stmt, admin);
    return admin;
}

void db_updateAdmin(db_t * self, admin_t * admin) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "UPDATE admins SET Name = ?, Surname = ?, Birthdate = ?, Rate = ?, CreatingYear = ?, Followers = ? WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, admin->name, strlen(admin->name), NULL);
    sqlite3_bind_text(stmt, 2, admin->surname, strlen(admin->surname), NULL);
    sqlite3_bind_int(stmt, 3, admin->birthdate);
    sqlite3_bind_double(stmt, 4, (double)admin->rate);
    sqlite3_bind_int(stmt, 5, admin->creating_year);
    sqlite3_bind_int(stmt, 6, admin->followers);
    sqlite3_bind_int(stmt, 7, admin->id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select admins\n");
        exit(1);
    }
}

void db_deleteAdmin(db_t * self, int id) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "DELETE FROM admins WHERE Id == ?";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select admins\n");
        exit(1);
    }
}

int db_countAdmins(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM admins;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}


int db_getStudentsTask(db_t * self, int K, int P, admin_t * arr, int arrMax) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM admins WHERE CreatingYear > ? AND Followers > ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select admins\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillStudent(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}

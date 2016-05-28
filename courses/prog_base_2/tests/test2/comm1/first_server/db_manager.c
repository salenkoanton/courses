#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>
#include "db_manager.h"
#include "json.h"

struct db_s {
    sqlite3 * db;
};

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

int db_insertWorker(db_t * self, struct person * workers) {
    int newStudentId = -1;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "INSERT INTO Worker_tab VALUES (null, ?, ?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, workers->name, strlen(workers->name), NULL);
    sqlite3_bind_text(stmt, 2, workers->surname, strlen(workers->surname), NULL);
    sqlite3_bind_text(stmt, 3, workers->birthdate, strlen(workers->birthdate), NULL);
    sqlite3_bind_int(stmt, 4, workers->age);
    sqlite3_bind_double(stmt, 5, workers->experience_age);
	
    sqlite3_bind_text(stmt, 6, workers->work.shop_name, strlen(workers->work.shop_name), NULL);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
    return newStudentId;
}

struct person * db_getWorkerById(db_t * self, int id) {
    struct person * worker = malloc(sizeof(struct person));
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Worker_tab WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    } else
        //_fillWorker(stmt, worker);
    return worker;
}

void db_updateWorker(db_t * self, struct person * workers, int id) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "UPDATE Worker_tab SET name = ?, surname = ?, birthdate = ?, age = ?, experience_age = ?, shop_name = ? WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, workers->name, strlen(workers->name), NULL);
    sqlite3_bind_text(stmt, 2, workers->surname, strlen(workers->surname), NULL);
    sqlite3_bind_text(stmt, 3, workers->birthdate, strlen(workers->birthdate), NULL);
    sqlite3_bind_int(stmt, 4, workers->age);
    sqlite3_bind_double(stmt, 5, workers->experience_age);
    sqlite3_bind_text(stmt, 6, workers->work.shop_name, strlen(workers->work.shop_name), NULL);
    sqlite3_bind_int(stmt, 7, id); //
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
}

void db_deleteWorker(db_t * self, int id) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "DELETE FROM Worker_tab WHERE Id == ?";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
}

int db_countWorkers(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Worker_tab;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

/*
int db_getStudentsTask(db_t * self, int K, int P, struct person * arr, int arrMax) {
    sqlite3_stmt * stmt = NULL;
    //const char * sqlQuery = "SELECT * FROM Worker_tab WHERE Cash > ? AND Work_time > ?;";
    // to do some kr task!!!!!!!!!!!////////////
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select workers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillWorker(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
*/

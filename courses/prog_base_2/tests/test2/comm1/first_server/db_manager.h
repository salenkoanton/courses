#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "json.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertWorker(db_t * self, struct person * student);
struct person * db_getWorkerById(db_t * self, int id);
void db_updateWorker(db_t * self, struct person * student, int id);
void db_deleteWorker(db_t * self, int id);

int db_countWorkers(db_t * self);

#endif // DB_MANAGER_H_INCLUDED
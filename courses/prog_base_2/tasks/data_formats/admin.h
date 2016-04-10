#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

typedef struct Admin admin_t;
admin_t * admin_create();
void set_admin (admin_t * p,char * name,char * surn, char * birthdate, int worktime, double rate);
void admin_print(admin_t * self);
void admin_free(admin_t * self);
admin_t ** parse(char * text);


#endif // ADMIN_H_INCLUDED

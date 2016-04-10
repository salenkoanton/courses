#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "json.h"
struct Admin{
    char * name;
    char * surname;
    char * birthdate;
    int worktime;
    double rate;
};

admin_t * admin_create(){
    admin_t * p = malloc(sizeof(struct Admin));
    return p;
}


void set_admin (admin_t * p,char * name,char * surn, char * birthdate, int worktime, double rate){
    p->name = malloc(sizeof(char) * strlen(name));
    p->surname = malloc(sizeof(char) * strlen(surn));
    p->birthdate = malloc(sizeof(char) * strlen(birthdate));
    strcpy(p->name, name);
    strcpy(p->surname, surn);
    strcpy(p->birthdate, birthdate);
    p->worktime = worktime;
    p->rate = rate;
}

void admin_print(admin_t * self){
    printf("Name: %s, Surname: %s, Birthdate: %s, Worktime: %i, Rate: %lf ", self->name, self->surname, self->birthdate, self->worktime, self->rate);
    printf("\n\n");
}

void admin_free(admin_t * self){
    free(self->name);
    free(self->surname);
    free(self->birthdate);
    free(self);
}

admin_t ** parse(char * text)
{
	cJSON * jList = cJSON_Parse(text);
	if (!jList) {
		printf("Error before: [%s]\n", cJSON_GetErrorPtr());
		return 1;
	}
    int count = cJSON_GetArraySize(jList);
    admin_t ** admins = malloc(sizeof(admin_t *) * count);
    for (int i = 0; i < count; i++) {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char * surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char * birthdate = cJSON_GetObjectItem(jItem, "birthdate")->valuestring;
        int worktime = cJSON_GetObjectItem(jItem, "worktime")->valueint;
        double rate = cJSON_GetObjectItem(jItem, "rate")->valuedouble;
        admins[i] = admin_create();
        set_admin (admins[i], name, surname, birthdate, worktime, rate);
    }
    cJSON_Delete(jList);
    return admins;
}

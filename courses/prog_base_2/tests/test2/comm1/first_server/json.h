#ifndef JSON_H
#define JSON_H
#include "list.h"
struct work{
    char shop_name[15];
};

struct person{
    char name[15];
    char surname[15];
    char birthdate[11];
    unsigned age;
    float experience_age;
    struct work work;
};
void list_to_xml(list_t list);
list_t xml_to_list(char *text);
char * info_to_xml(char * name, char * group, char * var);
#endif
#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct admin_s {
    int id;
    char name[256];
    char surname[256];
    int birthdate;
    float rate;
    int creating_year;
    int followers;
} admin_t;

void admin_print(admin_t * st);
void admin_printList(admin_t * arr, int len);

#endif // STUDENT_H_INCLUDED

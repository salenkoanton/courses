#ifndef KORPUS_H_INCLUDED
#define KORPUS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

enum boolean_e{
    FALSE = 0,
    TRUE
};
typedef struct korpus_s korpus_t;
void korpus_free(korpus_t * self);
enum boolean_e korpus_aud_isBusy(korpus_t * self, int numb);
enum boolean_e korpus_aud_take(korpus_t * self, int numb, int time);
korpus_t * korpus_new(char * name, int auds, int seats[auds]);
int korpus_audsCount(korpus_t * self);
int korpus_aud_numberOfSeats(korpus_t * self, int numb);
#endif // KORPUS_H_INCLUDED

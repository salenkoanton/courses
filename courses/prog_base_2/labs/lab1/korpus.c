#include "aud.h"
#include "korpus.h"

struct korpus_s {
    aud_t ** auds;
    int audCount;
    char * name;
};

korpus_t * korpus_new(char * name, int auds, int seats[auds])
{
    korpus_t * self = NULL;
    self = malloc(sizeof(struct korpus_s));
    if(self == NULL || auds <= 0)
        return NULL;
    self->name = malloc(sizeof(char) * strlen(name));
    self->audCount = auds;
    if (self->name == NULL)
    {
        free(self);
        return NULL;
    }
    strcpy(self->name, name);
    self->auds = malloc(sizeof(aud_t *) * auds);
    for (int i = 0; i < auds; i++){
        self->auds[i] = aud_new(seats[i], i);
        if (self->auds[i] == NULL)
        {
            for(int j = 0; j < i; j++)
                aud_free(self->auds[j]);
            free(self->name);
            free(self);
            return NULL;
        }
    }
    return self;
}

enum boolean_e korpus_aud_take(korpus_t * self, int numb, int time)
{
    if (numb < 0 || numb >= self->audCount)
        return FALSE;
    return aud_take(self->auds[numb], time);
}

enum boolean_e korpus_aud_isBusy(korpus_t * self, int numb)
{
    if (numb < 0 || numb >= self->audCount)
        return FALSE;
    return aud_isBusy(self->auds[numb]);
}

int korpus_audsCount(korpus_t * self)
{
    return self->audCount;
}

int korpus_aud_numberOfSeats(korpus_t * self, int numb)
{
    return aud_numberOfSeats(self->auds[numb]);
}

void korpus_free(korpus_t * self)
{
    for(int j = 0; j < self->audCount; j++)
        aud_free(self->auds[j]);
    free(self->name);
    free(self);
}

#include "aud.h"
#include "korpus.h"

struct aud_s {
    int numb;
    clock_t time;
    int seats;
};

aud_t * aud_new(int seats, int numb)
{
    aud_t * self = NULL;
    self = malloc(sizeof(struct aud_s));
    if (NULL == self)
        return NULL;
    self->seats = seats;
    self->time = clock();
    self->numb = numb;
    return self;
}

void aud_free(aud_t * self)
{
    free(self);
}

int aud_numberOfSeats(aud_t * self)
{
    return self->seats;
}

enum boolean_e aud_isBusy(aud_t * self)
{
    if (self->time > clock())
        return FALSE;
    else
        return TRUE;
}

enum boolean_e aud_take(aud_t * self, int time)
{
    if (clock() >= self->time)
    {
        self->time = time * CLOCKS_PER_SEC + clock();
    }
    else
        return FALSE;
    return TRUE;
}

int aud_getNumb (aud_t * self)
{
    return self->numb;
}

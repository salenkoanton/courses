#ifndef AUD_H_INCLUDED
#define AUD_H_INCLUDED


typedef struct aud_s aud_t;

enum boolean_e aud_isBusy(aud_t * self);
aud_t * aud_new(int seats, int numb);
int aud_numberOfSeats(aud_t * self);
enum boolean_e aud_take(aud_t * self, int time);
int aud_getNumb (aud_t * self);
void aud_free(aud_t * self);

#endif // AUD_H_INCLUDED

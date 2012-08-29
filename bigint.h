#ifndef _BIGINT_H_
#define _BIGINT_H_

#include<stddef.h>

#define BIGINT_SIGN_MASK 0x01
#define BIGINT_POS 1
#define BIGINT_NEG 0

#define BIGINT_OVERFLOW_MASK 0x02
#define BIGINT_MALLOC_MASK 0x04

#define BIGINT_IS_OVERFLOW(_bigt) \
    (((_bigt).flag&BIGINT_OVERFLOW_MASK)>>1)

#define BIGINT_IS_MALLOC(_bigt) \
    (((_bigt).flag&BIGINT_MALLOC_MASK)>>2)

#define BIGINT_SIGN(_bigt) ((_bigt).flag&BIGINT_SIGN_MASK)

#define BIGINT_MAXDIGIT(_bigt) ((_bigt).maxlen*4)

typedef struct bigint_t
{
    int *digits;
    char flag;
    size_t maxlen,len;
}bigint_t;

void bigint_new(bigint_t *bt,void *ptr,size_t size);
void bigint_zero(bigint_t *bt);
void bigint_free(bigint_t *bt);
void bigint_cpy(bigint_t *dst,bigint_t *src);
void i2big(bigint_t *bt,int n);
void a2big(bigint_t *bt,const char *str);

int bigint_us_cmp(bigint_t *a,bigint_t *b);
//void _bigint_add(bigint_t *a,bigint_t *b,bigint_t *c)
//void _bigint_sub(bigint_t *a,bigint_t *b,bigint_t *c)

void bigint_add(bigint_t *a,bigint_t *b,bigint_t *c);
void bigint_sub(bigint_t *a,bigint_t *b,bigint_t *c);
void bigint_mult(bigint_t *a,bigint_t *b,bigint_t *c);
void bigint_div(bigint_t *a,bigint_t *b,bigint_t *c);
void bigint_mod(bigint_t *a,bigint_t *b,bigint_t *c);
void printbig(bigint_t *bt);

#endif

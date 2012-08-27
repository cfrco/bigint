#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b,c;
    int buf[150];

    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);
    bigint_new(&c,buf+100,50);

    i2big(&a,10000);
    i2big(&b,9999);
    _bigint_sub(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,7654321);
    i2big(&b,1234567);
    _bigint_sub(&a,&b,&c);
    printbig(&c);
    printf("\n");

    a2big(&a,"123456789123456789");
    a2big(&b,"123456789123456789");
    _bigint_sub(&a,&b,&c);
    printbig(&c);
    printf("\n");
    return 0;
}

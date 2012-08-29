#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b,c;
    int buf[150];

    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);
    bigint_new(&c,buf+100,50);

    i2big(&a,123456789);
    i2big(&b,345);
    bigint_mod(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    a2big(&a,"123456789123456789123456789");
    a2big(&b,"987654321");
    bigint_mod(&a,&b,&c);
    printbig(&c);
    printf("\n");
    return 0;
}

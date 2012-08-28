#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b,c;
    int buf[200];
    
    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);
    bigint_new(&c,buf+100,100);

    a2big(&a,"123456789123456789");
    a2big(&b,"9876543210");
    bigint_mult(&a,&b,&c);
    printbig(&c);
    printf("\n");

    return 0;
}

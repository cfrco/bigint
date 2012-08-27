#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b,c;
    int buf[150];

    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);
    bigint_new(&c,buf+100,50);

    i2big(&a,100);
    i2big(&b,150);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,10000);
    i2big(&b,9999);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,10);
    i2big(&b,9999);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,1234567);
    i2big(&b,7654321);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");

    a2big(&a,"123456789123456789");
    a2big(&b,"123456789123456789");
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    a2big(&a,"-123456789123456789");
    a2big(&b,"123456789123456789");
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    a2big(&a,"123456789123456789");
    a2big(&b,"-123456789123456789");
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    a2big(&a,"-123456789123456789");
    a2big(&b,"-123456789123456789");
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,100);
    i2big(&b,-150);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,10000);
    i2big(&b,-9999);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,-10);
    i2big(&b,-9999);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,1234567);
    i2big(&b,-7654321);
    bigint_add(&a,&b,&c);
    printbig(&c);
    printf("\n");
    return 0;
}

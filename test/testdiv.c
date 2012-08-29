#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b,c;
    int buf[150];

    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);
    bigint_new(&c,buf+100,50);

    i2big(&a,99999);
    i2big(&b,3);
    bigint_div(&a,&b,&c);
    printbig(&c);
    printf("\n");
        
    i2big(&a,199999);
    i2big(&b,30);
    bigint_div(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    i2big(&a,123456789);
    i2big(&b,123);
    bigint_div(&a,&b,&c);
    printbig(&c);
    printf("\n");
    
    a2big(&a,"123456789123456789");
    a2big(&b,"123456789123456790");
    bigint_div(&a,&b,&c);
    printbig(&c);
    printf("\n");
    return 0;
}

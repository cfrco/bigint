#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t big;
    int buf[100]; 
    bigint_new(&big,buf,100);

    printbig(&big);
    printf("\n");

    i2big(&big,99);
    printbig(&big);
    printf("\n");
    
    i2big(&big,9999);
    printbig(&big);
    printf("\n");
    i2big(&big,10000);
    printbig(&big);
    printf("\n");
    i2big(&big,123456789);
    printbig(&big);
    printf("\n");

    i2big(&big,0);
    printbig(&big);
    printf("\n");
    i2big(&big,-1);
    printbig(&big);
    printf("\n");
    i2big(&big,-9999);
    printbig(&big);
    printf("\n");
    i2big(&big,-20000);
    printbig(&big);
    printf("\n");


    //=======================
    a2big(&big,"123456789123456789");
    printbig(&big);
    printf("\n");
    a2big(&big,"0");
    printbig(&big);
    printf("\n");
    a2big(&big,"99");
    printbig(&big);
    printf("\n");
    a2big(&big,"9999");
    printbig(&big);
    printf("\n");
    a2big(&big,"19999");
    printbig(&big);
    printf("\n");
    
    a2big(&big,"+123456789123456789");
    printbig(&big);
    printf("\n");
    a2big(&big,"+9999");
    printbig(&big);
    printf("\n");
    a2big(&big,"+19999");
    printbig(&big);
    printf("\n");
    
    a2big(&big,"-123456789123456789");
    printbig(&big);
    printf("\n");
    a2big(&big,"-9999");
    printbig(&big);
    printf("\n");
    a2big(&big,"-19999");
    printbig(&big);
    printf("\n");
    a2big(&big,"-1");
    printbig(&big);
    printf("\n");
    return 0;
}

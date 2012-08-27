#include"bigint.h"
#include<stdio.h>

int main()
{
    bigint_t a,b;
    int buf[100];

    bigint_new(&a,buf,50);
    bigint_new(&b,buf+50,50);

    i2big(&a,10);
    i2big(&b,10);
    printf("%d\n",bigint_us_cmp(&a,&b));

    i2big(&a,20);
    i2big(&b,10);
    printf("%d\n",bigint_us_cmp(&a,&b));
    i2big(&a,20);
    i2big(&b,50);
    printf("%d\n",bigint_us_cmp(&a,&b));
    
    i2big(&a,20000);
    i2big(&b,150);
    printf("%d\n",bigint_us_cmp(&a,&b));
    i2big(&a,-20000);
    i2big(&b,15000);
    printf("%d\n",bigint_us_cmp(&a,&b));
    
    a2big(&a,"323456789123456789");
    a2big(&b,"2123456789123456789");
    printf("%d\n",bigint_us_cmp(&a,&b));
    return 0;
}

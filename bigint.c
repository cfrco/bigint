#include"bigint.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void bigint_new(bigint_t *bt,void *ptr,size_t size)
{
    bt->flag = 1;

    if(ptr==NULL)
    {
        bt->flag += 4;
        bt->digits = (int*)malloc(size*sizeof(int));
    }
    else bt->digits = ptr;

    bt->maxlen = size;

    bt->digits[0] = 0;
    bt->len = 1;
}

void bigint_zero(bigint_t *bt)
{
    bt->digits[0] = 0;
    bt->flag |= 0x01;
    bt->len = 1;
}

void bigint_free(bigint_t *bt)
{
    if(BIGINT_IS_MALLOC(*bt))
        free(bt->digits);

    bt->maxlen = 0;
    bt->flag = 0;
    bt->len = 0;
}

void i2big(bigint_t *bt,int n)
{
    if(n>=0) bt->flag |= 0x01;
    else
    {
        bt->flag &= ~(0x01);
        n = 0-n;
    }

    size_t i;
    for(i=0;i<bt->maxlen;++i)
    {
        bt->digits[i] = n%10000;
        n /= 10000;
        if(n==0)break;
    }

    if(i>=bt->maxlen) bt->flag |= 0x02;
    else bt->flag &= ~(0x02);
    bt->len = i+1;
}
void a2big(bigint_t *bt,const char *str)
{
    size_t len = strlen(str),end=0;

    if(len==0)
    {
        bigint_zero(bt);
        return ;
    }

    if(str[0]=='-')
    {
        bt->flag &= ~(0x01);
        end = 1;
    }
    else
    {
        if(str[0]=='+') end = 1;
        bt->flag |= 0x01;
    }

    size_t i,s=0;
    int n=0,j=1;
    for(i=len-1;i>=end&&s<bt->maxlen;--i)
    {
        if(str[i]>47&&str[i]<58)
            n += (str[i]-48)*j;
        j*=10;

        if(j==10000)
        {
            bt->digits[s++] = n; 
            j = 1;
            n = 0;
        }

        if(i==0)break;
    }

    if(n!=0||s==0)
        bt->digits[s++] = n;

    if(s>=bt->maxlen&&n!=0)
        bt->flag |= 0x02;

    bt->len = s;
}

int bigint_us_cmp(bigint_t *a,bigint_t *b)
{
    if(a->len > b->len)
        return 1;
    else if(a->len < b->len)
        return -1;
    
    size_t i = a->len-1;
    for(;i>=0;--i)
    {
        if(a->digits[i]>b->digits[i])
            return 1;
        else if(a->digits[i]<b->digits[i])
            return -1;
        if(i==0)break;
    }
    return 0;
}

void _bigint_add(bigint_t *a,bigint_t *b,bigint_t *c)
{
    size_t i,e = b->len,max = c->maxlen;
    int carry=0,t;

    for(i=0;i<e&&i<max;++i)
    {
        t = a->digits[i]+b->digits[i]+carry; 

        if(t>9999)
        {
            t -= 10000;
            carry = 1;
        }
        else carry = 0;

        c->digits[i] = t;
    }

    e = a->len;
    for(;i<e&&i<max;++i)
    {
        t = a->digits[i]+carry; 

        if(t>9999)
        {
            t -= 10000;
            carry = 1;
        }
        else carry = 0;

        c->digits[i] = t;

        if(carry==0)
        {
            ++i;
            break;
        }
    }
    
    for(;i<e&&i<max;++i)
        c->digits[i] = a->digits[i];

    if(carry&&i<max)
    {
        c->digits[i++] = carry;
        carry = 0;
    }

    if(i<e||(i==max&&carry!=0))
        c->flag |= 0x02;

    c->len = i;
}

void _bigint_sub(bigint_t *a,bigint_t *b,bigint_t *c)
{
    size_t i,e = b->len,max = c->maxlen;
    int carry=0,t;

    for(i=0;i<e&&i<max;++i)
    {
        t = a->digits[i]-b->digits[i]-carry; 

        if(t<0)
        {
            t += 10000;
            carry = 1;
        }
        else carry = 0;

        c->digits[i] = t;
    }

    e = a->len;
    for(;i<e&&i<max;++i)
    {
        t = a->digits[i]-carry; 

        if(t<0)
        {
            t += 10000;
            carry = 1;
        }
        else carry = 0;

        c->digits[i] = t;

        if(carry==0)
        {
            ++i;
            break;
        }
    }
    
    for(;i<e&&i<max;++i)
        c->digits[i] = a->digits[i];

    if(i<e)
        c->flag |= 0x02;
    
    for(i=e-1;i>0;--i)
        if(c->digits[i]!=0)
            break;

    c->len = i+1;
}

void bigint_add(bigint_t *a,bigint_t *b,bigint_t *c)
{
    bigint_t *tmp; 

    if(bigint_us_cmp(a,b)<0)
    {
        tmp = b;
        b = a;
        a = tmp;
    }

    if(BIGINT_SIGN(*a) && BIGINT_SIGN(*b))
    {
        c->flag |= 0x01;
        _bigint_add(a,b,c);
    }
    else if(!BIGINT_SIGN(*a) && !BIGINT_SIGN(*b))
    {
        c->flag &= ~(0x01);
        _bigint_add(a,b,c);
    }
    else if(BIGINT_SIGN(*a))
    {
        c->flag |= 0x01;
        _bigint_sub(a,b,c);
    }
    else
    {
        c->flag &= ~(0x01);
        _bigint_sub(a,b,c);
    }

    if(c->len==1 && c->digits[0]==0)
        bigint_zero(c);
}

void bigint_sub(bigint_t *a,bigint_t *b,bigint_t *c)
{
    bigint_t *tmp; 
    char s = BIGINT_SIGN(*b);

    if(s)b->flag &= ~(0x01);
    else b->flag |= 0x01;
    bigint_add(a,b,c);
    if(!s)b->flag &= ~(0x01);
    else b->flag |= 0x01;
}

void bigint_mult(bigint_t *a,bigint_t *b,bigint_t *c)
{
    size_t i,j,e = a->len+b->len;
    int t;

    for(i=0;i<e;++i)
        c->digits[i] = 0;

    if(BIGINT_SIGN(*a) == BIGINT_SIGN(*b))
        c->flag |= 0x01;
    else 
        c->flag &= ~(0x01);

    for(i=0;i<a->len;++i)
    {
        for(j=0;j<b->len;++j)
        {
            if(i+j>=c->maxlen)break;
            c->digits[i+j] += a->digits[i]*b->digits[j];   
            e = i+j;
            while(c->digits[e]>9999)
            {
                c->digits[e+1] += c->digits[e]/10000; 
                c->digits[e++] %= 10000;
            }
        }
        if(i+j>=c->maxlen)break;
    }

    if(i+j>=c->maxlen)
        c->flag |= 0x02;
    
    for(i=a->len+b->len-1;i>0;--i)
        if(c->digits[i]!=0)
            break;

    c->len = i+1;
}

void printbig(bigint_t *bt)
{
    size_t i = bt->len-1;

    if(BIGINT_SIGN(*bt) == BIGINT_NEG)
        printf("-");

    printf("%d",bt->digits[i]);
    if(i==0)return;

    for(--i;i>=0;--i)
    {
        printf("%04d",bt->digits[i]);
        if(i==0)break;
    }
}

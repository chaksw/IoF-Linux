/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-15 09:29:32 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-15 14:19:27
 */

#include <stdio.h>

// 1.通过标准输入控制，在屏幕上输出n行的星三角图形
void star_Img();
// 求位于高度100m的球自由落体反弹n次后经过的路程以及n次时反弹高度(每次反弹到高度的一半)
void free_fall(const int r);
// 求分数序列：2/1，3/2，5/3，8/5，13/8，21/13...前20项之和
void sum_fraction_serial(const int n);
// 求1+2!+3!+...+10!的和
void sum_factorial(const int n);
// 求100 ~ 200 之间所有的素数
void prime_number(const unsigned int from, const unsigned int to);
// 输出星号组成的菱形
void printf_rhomb(int n);
// 递增寻找第150/1500个丑数
void Ugly_Num(const int n);

int main(int argc, char **argv)
{
    star_Img();

    int rebound = 10;
    free_fall(rebound);

    int premierN = 20;
    sum_fraction_serial(premierN);

    int num_fac = 10;
    sum_factorial(num_fac);

    int from = 100;
    int to = 200;
    prime_number(from, to);

    int num = 6;
    printf_rhomb(num);

    int n = 150;
    // int n = 1500;
    Ugly_Num(n);
    return 0;
}

void star_Img()
{
    int n = 0;
    printf("entre your number: ");
    scanf("%d", &n);
    for (size_t i = 1; i < (n + 1); i++)
    {
        for (size_t k = (n + 1 - i); k > 0; k--)
            printf("  ");       
        for (size_t j = 0; j < i; j++)
            printf("*   ");
        printf("\n");
    }
    printf("==============================================================\n");
}

void free_fall(const int r)
{
    float height = 100;
    int i = 0;
    float s = 0, rebound_h = 0;
    for (i = 0; i < r; i++)
    {
        s += height;        // nth times falling pass
        s += rebound_h;      // nth times rebound pass
        if(height != 0)
        {
            height = height/2;
            rebound_h = height;
            
        }else break;
    }
    printf("ball has passed %.02f m after %d times falling\n", s, r);
    printf("ball will rebound %.02f m in %dth times.\n", rebound_h, r);
    printf("==============================================================\n");
}

void sum_fraction_serial(const int n)
{
    float sum = 0;
    float num_buf = 0;  
    float nume = 2, deno = 1;
    for (size_t i = 0; i < n; i++)
    {
        sum += (nume / deno);
        num_buf = nume;
        nume += deno;
        deno = num_buf;
    }
    printf("Sum of premier %d serial values = %.4f\n", n, sum);
    printf("==============================================================\n");
}

void sum_factorial(const int n)
{
    int i = 0, j = 0, n_fac = 1;
    u_int64_t sum = 0;
    for (i = 1; i < (n + 1); i++)
    {
        while (j < i)
            n_fac *= (++j);
        sum += n_fac;
    }
    printf("Sum of factorial for %d number = %llu\n", n, sum);
    printf("==============================================================\n");
}


void prime_number(const unsigned int from, const unsigned int to)
{
    unsigned int prime = 0;
    int i = 0, k = 0;
    printf("prime_number in range from %d to %d is :\t", from, to);
    for(int i = from; i < (to + 1); i++)
    {
        for (int k = 2; k < i; k++)
        {   
            if((i % k)  == 0)
                break;
            if(i == (k + 1))
            {
                prime = i;
                printf("%u   ", prime);
                break;
            }
        }
    }
    printf("\n");
    printf("==============================================================\n");
}

void printf_rhomb(int n)
{
    printf("line number = %d\n", n);
    int i = 0, k = 0, j = 0, h = 0;
    for ( i = 1; i < (n + 1); i++)
    {
        for (k = (n - i); k > 0; k--)
            printf(" ");       
        for (j = 0; j < i ; j++)
            printf("*");
            for ( h = 0; h < j - 1; h++)
                printf("*");
        printf("\n");
    }
    for ( i = n - 1; i > 0 ; i--)
    {
        for (k = (n - i); k > 0; k--)
            printf(" ");
        for (j = 0; j < i ; j++)
            printf("*");
            for ( h = 0; h < j - 1; h++)
                printf("*");
        printf("\n");   
    }
    printf("==============================================================\n");
}

void Ugly_Num(const int n)
{
    printf("premier %d Ugly number is :\n", n);
    printf("1   ");
    int value = 2;
    int buf = value;
    int i = 1, ugly_num = 0;
    while(i < n)
    {
        
        if(((buf / 2) == 1) && ((buf % 2) == 0))
        {   
            i++;
            ugly_num = value;
            printf("%d   ", ugly_num);
            value++;
            buf = value;
        }else if(((buf / 2) != 1) &&(buf % 2)  == 0)
        {
            buf /= 2;
        }else if(((buf / 3) == 1) && ((buf % 3) == 0))
        {
            i++;
            ugly_num = value;
            printf("%d   ", ugly_num);
            value++;
            buf = value;
        }else if(((buf / 3) != 1) && (buf % 3) == 0)
        {
            buf /= 3;
        }else if(((buf / 5) == 1) && ((buf % 5) == 0))
        {
            i++;
            ugly_num = value;
            printf("%d   ", ugly_num);
            value++;
            buf = value;
        }else if(((buf / 5) != 1) && (buf % 5) == 0)
        {
            buf /= 5;
        }else
        {
            value++;
            buf = value;
        }  
    }
    printf("\n");   
}
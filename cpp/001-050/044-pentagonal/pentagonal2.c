#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 *
 */

char isPentagonal(unsigned int n)
{
    unsigned int value = 24 * n + 1;
    float f = sqrt(value);
    if (ceil(f) != floor(f))
        return 0;
    f = (f + 1.0) / 6.0;
    if (ceil(f) != floor(f))
        return 0;
    return 1;
}


void test()
{
    for (unsigned int i = 1; i <= 15; i++)
        printf("isPentagonal(%d) == %d\n", i, isPentagonal(i));
}

int main(int argc, char **argv)
{
    const int LIST_SIZE = 10000;
    unsigned int list[LIST_SIZE];
    int listPos = 0;
    test();
    for (unsigned int i = 3; i <= 10000; i++)
    {
        unsigned int dif = 3 * i - 2;
        unsigned int tmp;
        if (isPentagonal(dif))
            if (isPentagonal(3*i*i-4*i+1))
                printf("%d\n", dif);
        tmp = dif;
        for (int j = listPos - 1; j >= 0; j--)
        {
            tmp += list[j];
            if (isPentagonal(tmp))
                if (isPentagonal(i*(3*i-1)/2+j*(3*j-1)/2))
                    printf("%d\n", tmp);
        }
        if (listPos >= LIST_SIZE)
        {
            printf("List too small\n");
            return 1;
        }
        list[listPos++] = dif;

    }

    return 0;
}

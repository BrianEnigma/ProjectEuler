#include <stdio.h>
#include <string.h>
/*
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we 
 * get 3, 5, 6 and 9. The sum of these multiples is 23.
 * 
 * Find the sum of all the multiples of 3 or 5 below 1000
 */

#define MAX_VAL 1000
//#define MAX_VAL 30

void try1()
{
    unsigned int result = 0;
    // Multiples of 5
    for (int i = 0; i < MAX_VAL; i += 5)
        result += i;
    // Multiples of 3
    for (int i = 0; i < MAX_VAL; i += 3)
        result += i;
    printf("%d\n", result);
}

void try2()
{
    unsigned int result = 0;
    // Multiples of 5
    for (int i = 0; i < MAX_VAL; i += 5)
    {
        printf("%d ", i);
        result += i;
    }
    // Multiples of 3 that are not also multiples of 5 or 10
    for (int i = 0; i < MAX_VAL; i += 3)
        if (    ((i & 0x0A) != 0x0A)
             && ((i & 0x05) != 0x05)
           )
        {
            printf("%d ", i);
            result += i;
        }
    printf("\n%d\n", result);
    
}

void try3()
{
    unsigned int result = 0;
    for (int i = 0; i < MAX_VAL; i++)
        if (    ((i % 3) == 0)
             || ((i % 5) == 0)
           )
        {
            printf("%d ", i);
            result += i;
        }
    printf("\n%d\n", result);
}

int main(int argc, char **argv)
{
    try1();
    try2();
    try3();
    return 0;
}

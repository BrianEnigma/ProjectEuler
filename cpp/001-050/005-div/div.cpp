#include <stdio.h>
#include <string.h>

/*
2520 is the smallest number that can be divided by each of the numbers from 1 
to 10 without any remainder.

What is the smallest number that is evenly divisible by all of the numbers 
from 1 to 20?
*/

//#define MAX_DIV 10
#define MAX_DIV 20

int isEvenlyDivisible(unsigned long long number)
{
    for (int i = 2; i <= MAX_DIV; i++)
        if ((number % i) != 0)
            return 0;
    return 1;
}

int test()
{
    unsigned int number = 109641728;
    for (int i = 2; i <= MAX_DIV; i++)
    {
        printf("%d %% %d == %d\n", number, i, number % i);
        if ((number % i) != 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    unsigned long long absoluteMax = 1;
    
    //printf("test() == %d\n", test());
    //return 0;
    for (int i = 2; i < MAX_DIV; i++)
        absoluteMax *= i;
    printf("absoluteMax == %d\n", absoluteMax);
    for (unsigned long long i = 2; i < absoluteMax; i++)
        if (isEvenlyDivisible(i))
        {
            printf("Found: %d\n", i);
            return 0;
        }
    return 0;
}


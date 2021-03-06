#include <stdio.h>
#include <string.h>
#include <math.h>
/*
The sequence of triangle numbers is generated by adding the natural numbers. 
So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The 
first ten terms would be:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:

     1: 1
     3: 1,3
     6: 1,2,3,6
    10: 1,2,5,10
    15: 1,3,5,15
    21: 1,3,7,21
    28: 1,2,4,7,14,28

We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over five hundred 
divisors?
*/

//#define STOP_COUNT 5
#define STOP_COUNT 500

unsigned int factorCount(unsigned int number)
{
    unsigned int result = 2;
    unsigned int max = number / 2;
    for (unsigned int i = 2; i <= max; i++)
        if ((number % i) == 0)
            result++;
    return result;
}

unsigned int triangle(unsigned int number)
{
    unsigned int result = 0;
    for (unsigned int i = 1; i <= number; i++)
        result += i;
    return result;
}

int main(int argc, char **argv)
{
    unsigned int counter = 1;
    unsigned int triangleValue;
    unsigned int factors;
    unsigned int previousFactors = 0;
    while (1) 
    {
        triangleValue = triangle(counter);
        factors = factorCount(triangleValue);
        if (previousFactors < factors)
        {
            previousFactors = factors;
            printf("Number %d has triangle %d and %d factors\n", counter, triangleValue, factors);
        }
        if (factors >= STOP_COUNT)
            break;
        counter++;
    }
    return 0;
}

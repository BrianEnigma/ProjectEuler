#include <stdio.h>
#include <string.h>
#include <gmp.h>
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
//#define STOP_COUNT 100
#define STOP_COUNT 500

mpz_t previousTriangleCounter;

unsigned int factorCount(mpz_t number)
{
    mpz_t maxNumber;
    mpz_t counter;
    mpz_t q;
    mpz_t r;
    unsigned int result = 0;
    
    //if (mpz_cmp_ui(number, 1) == 0)
    //    return 1;
    mpz_init_set(maxNumber, number);
    mpz_init(r);
    mpz_init(q);
    mpz_sqrt(maxNumber, number);
    for (mpz_init_set_ui(counter, 1); mpz_cmp(counter, maxNumber) <= 0; mpz_add_ui(counter, counter, 1))
        if (mpz_divisible_p(number, counter))
            result += 2;
    return result;
}

void nextTriangle(mpz_t result)
{
    mpz_add_ui(previousTriangleCounter, previousTriangleCounter, 1);
    mpz_add(result, result, previousTriangleCounter);
}

int main(int argc, char **argv)
{
    mpz_t counter;
    mpz_t triangleValue;
    unsigned int factors;
    unsigned int previousFactors = 0;
    mpz_init_set_ui(counter, 1);
    mpz_init(triangleValue);
    mpz_init_set_ui(previousTriangleCounter, 0);
    
    while (1) 
    {
        nextTriangle(triangleValue);
        factors = factorCount(triangleValue);
        if (previousFactors < factors)
        {
            previousFactors = factors;
            printf("Number %s has triangle %s and %d factors\n", mpz_get_str(NULL, 10, counter), mpz_get_str(NULL, 10, triangleValue), factors);
        }
        if (factors >= STOP_COUNT)
            break;
        mpz_add_ui(counter, counter, 1);
    }
    return 0;
}
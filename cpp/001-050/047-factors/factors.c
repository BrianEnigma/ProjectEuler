#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * The first two consecutive numbers to have two distinct prime factors are:
 *
 *   14 = 2 x 7
 *   15 = 3 x 5
 *
 * The first three consecutive numbers to have three distinct prime factors are:
 *
 *   644 = 2^2 x 7 x 23
 *   645 = 3 x 5 x 43
 *   646 = 2 x 17 x 19.
 *
 * Find the first four consecutive integers to have four distinct primes
 * factors. What is the first of these numbers?
 *
 */

//#define PRINTFACTORS

unsigned int distinctFactorCount(unsigned int number, int maxCount)
{
    unsigned int result = 0;
    for (unsigned int i = 2; i <= number; i++)
        if ((number % i) == 0)
        {
            number /= i;
#ifdef PRINTFACTORS
            printf("   %d\n", i);
#endif
            if (++result > maxCount)
                return -1;
            while ((number % i) == 0)
                number /= i;
        }
    return result;
}

void consecutiveFactors(unsigned int start, unsigned int end, int requiredFactorCount, int requiredConsecutiveCount)
{
#ifndef PRINTFACTORS
    unsigned int count = 0;
    for (unsigned int n = start; n <= end; n++)
    {
        if (distinctFactorCount(n, requiredFactorCount) == requiredFactorCount)
        {
            //printf("Match on %d\n", n);
            if (++count == requiredConsecutiveCount)
            {
                printf("%d consecutive factors of %d: ", requiredConsecutiveCount, requiredFactorCount);
                for (int i = n - requiredConsecutiveCount + 1; i <= n; i++)
                    printf("%d ", i);
                printf("\n");
            }
        } else
            count = 0;
    }
#endif
}

void test()
{
    printf("distinctFactorCount(14, 2)==%d\n", distinctFactorCount(14, 2));
    printf("distinctFactorCount(14, 1)==%d\n", distinctFactorCount(14, 1));
    printf("distinctFactorCount(644, 3)==%d\n", distinctFactorCount(644, 3));
    printf("distinctFactorCount(1000, 4)==%d\n", distinctFactorCount(1000, 4));
    consecutiveFactors(10, 99, 2, 2);
    consecutiveFactors(100, 999, 3, 3);
}

int main(int argc, char **argv)
{
    test();
    consecutiveFactors(4, 999999, 4, 4);
    return 0;
}

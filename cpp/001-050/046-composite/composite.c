#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * It was proposed by Christian Goldbach that every odd composite number can
 * be written as the sum of a prime and twice a square.
 *
 * 9 = 7 + 2x1^(2)
 * 15 = 7 + 2x2^(2)
 * 21 = 3 + 2x3^(2)
 * 25 = 7 + 2x3^(2)
 * 27 = 19 + 2x2^(2)
 * 33 = 31 + 2x1^(2)
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a
 * prime and twice a square?
 *
 */

//#define MAX_LIST 10000
//unsigned int primeList[MAX_LIST];
//unsigned int primeListLength = 0;

//#define isComposite(value) !isPrime(value)

int isPrime(unsigned int value)
{
    unsigned int max;
    // Fail by definition (prime has to be > 1)
    if (value <= 1)
        return 0;
    if (value == 2)
        return 1;
    // Check if prime
    max = sqrt(value) + 1;
    for (unsigned int i = 2; i <= max; i++)
        if ((value % i) ==  0)
            return 0;
    return 1;
}

//void fillPrimeList()
//{
//    for (int i = 2; i <= 1000000; i++)
//        if (isPrime(i))
//        {
//            primeList[primeListLength++] = i;
//            if (primeListLength > MAX_LIST)
//                break;
//        }
//    printf("Loaded list with %d primes, max is %d\n", primeListLength, primeList[primeListLength]);
//}

char isOddComposite(unsigned int value)
{
    if (value % 2 == 0)
        return 0;
    if (isPrime(value))
        return 0;
    return 1;
}

char isGoldbach(unsigned int value)
{
    unsigned int halfValue = value / 2;
    for (int i = halfValue; i >= 1; i--)
        if ((2 * i * i < value) && isPrime(value - 2 * i * i))
        {
            printf("%d = %d + 2 * %d^2\n", value, value - 2 * i * i, i);
            return 1;
        }
    return 0;
}

int main(int argc, char **argv)
{
//    fillPrimeList();
//    for (unsigned int i = 3; i < 34; i++)
    for (unsigned int i = 3; i < 1000000; i++)
        if (isOddComposite(i))
            if (!isGoldbach(i))
            {
                printf("Found %d\n", i);
                return 0;
            }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*
 * The number, 197, is called a circular prime because all rotations of the
 * digits: 197, 971, and 719, are themselves prime.
 *
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37,
 * 71, 73, 79, and 97.
 *
 * How many circular primes are there below one million?
 *
 */
// A brute-force number length for number < 1mil

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

unsigned int numberLength(unsigned int n)
{
    if (n <= 9)     return 1;
    if (n <= 99)    return 2;
    if (n <= 999)   return 3;
    if (n <= 9999)  return 4;
    if (n <= 99999) return 5;
    if (n <= 999999)return 6;
    return 0;
}

unsigned int rotateOne(unsigned int n, unsigned int len)
{
    int digit = n % 10;
    unsigned int pos = 1;
    unsigned int result = n / 10;
    for (unsigned int i = 1; i < len; i++)
        pos *= 10;
    result += digit * pos;
    return result;
}

int isCircular(unsigned int n)
{
    unsigned int len = numberLength(n);
    if (!isPrime(n))
        return 0;
    for (int i = 1; i < len; i++)
    {
        n = rotateOne(n, len);
        if (!isPrime(n))
            return 0;
    }
    return 1;
}

void test()
{
    unsigned int n = 123890;
    unsigned int len = numberLength(n);
    printf("%d\n", n);
    for (int i = 0; i < len; i++)
    {
        n = rotateOne(n, len);
        printf(" ...%d\n", n);
    }
}

int main(int argc, char **argv)
{
    //const unsigned int MAX = 100;
    const unsigned int MAX = 1000000;
    int hitCount = 0;
    test();
    for (int n = 2; n < MAX; n++)
        if (isCircular(n))
        {
            printf("%d\n", n);
            hitCount++;
        }
    printf("%d hits\n", hitCount);
    return 0;
}

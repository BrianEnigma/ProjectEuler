#include <stdio.h>
#include <string.h>
#include <math.h>
#include "common.h"

int isPrime_ui(unsigned int value)
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

#ifdef BIGNUM
int isPrime_mpz(mpz_t n)
{
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t remainder;

    if (mpz_cmp_ui(n, 1) <= 0) // negatives, zero, 1 : not prime
        return 0;
    if (mpz_cmp_ui(n, 2) == 0) // 2 : prime
        return 1;
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    mpz_sqrt(maxIterator, n);
    mpz_add_ui(maxIterator, maxIterator, 1); // round up
    for (mpz_set_ui(iterator, 2); mpz_cmp(iterator, maxIterator) <= 0; mpz_add_ui(iterator, iterator, 1))
    {
        mpz_cdiv_r(remainder, n, iterator);
        if (mpz_cmp_ui(remainder, 0) == 0)
            return 0;
    }
    return 1;
}
#endif

void printCallback(char *s)
{
    printf("%s\n", s);
}

int doPermutations(char *charset, int charsetLength, char depth, char *buffer, void (*callback)(char *))
{
    char *bufferEnd = buffer + strlen(buffer);
    if (depth == 0)
    {
        callback(buffer);
    }
    for (int i = 0; i < charsetLength; i++)
    {
        if (*(charset + i) != 0)
        {
            char c = *(charset + i);
            *(charset + i) = 0;
            *bufferEnd = c;
            *(bufferEnd + 1) = '\0';
            doPermutations(charset, charsetLength, depth - 1, buffer, callback);
            *bufferEnd = '\0';
            *(charset + i) = c;
        }
    }
    return 0;
}

int numberLength(unsigned int n)
{
    if (n <= 9)                 return 1;
    else if (n <= 99)           return 2;
    else if (n <= 999)          return 3;
    else if (n <= 9999)         return 4;
    else if (n <= 99999)        return 5;
    else if (n <= 999999)       return 6;
    else if (n <= 9999999)      return 7;
    else return -1000; //  this should get someone's attention
}

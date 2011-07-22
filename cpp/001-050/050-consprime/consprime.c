#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * The prime 41, can be written as the sum of six consecutive primes:
 *
 *      41 = 2 + 3 + 5 + 7 + 11 + 13
 *
 * This is the longest sum of consecutive primes that adds to a prime below
 * one-hundred.
 *
 * The longest sum of consecutive primes below one-thousand that adds to a
 * prime, contains 21 terms, and is equal to 953.
 *
 * Which prime, below one-million, can be written as the sum of the most
 * consecutive primes?
 *
 */
//#define LONGEST_MAX_VALUE 100
//#define LONGEST_MAX_VALUE 1000
#define LONGEST_MAX_VALUE 1000000
#define LOOKAHEAD 1000
#define MAX_LIST 100000
unsigned int primeList[MAX_LIST];
unsigned int primeListLength = 0;

unsigned int longestListStart = 0;
unsigned int longestListLength = 0;

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

int isPrimeByLookup(unsigned int value)
{
    for (unsigned int position = 0; (position < primeListLength) && (primeList[position] <= value); position++)
        if (primeList[position] == value)
            return 1;
    return 0;
}

void fillPrimeList()
{
    for (int i = 2; i <= 1000000; i++)
        if (isPrime(i))
        {
            primeList[primeListLength++] = i;
            if (primeListLength > MAX_LIST)
            {
                printf("Out of space @ %d\n", i);
                exit(1);
            }
        }
    printf("Loaded list with %d primes below a million\n", primeListLength);
}

void findLongest(unsigned int max)
{
    unsigned int tmp = 0;
    for (int position = 0; position < primeListLength; position++)
    {
        unsigned int sum = primeList[position];
        for (int length = 1; (length < LOOKAHEAD) && (position + length < primeListLength); length++)
        {
            sum += primeList[position + length];
            //printf("%d:%d\n", length, sum);
            if (isPrime(sum))
            {
                if ((sum <= max) && (length >= longestListLength))
                {
                    printf("New best: length %d @ %d\n", length, primeList[position]);
                    longestListLength = length + 1;
                    longestListStart = position;
                }
            }
            if (sum > max)
                break;
        }
    }
    printf("Best was length %d @ %d\n", longestListLength, primeList[longestListStart]);
    for (int i = 0; i < longestListLength; i++)
        tmp += primeList[longestListStart + i];
    printf(" == %d\n", tmp);
}

int main(int argc, char **argv)
{
    fillPrimeList();
    for (int i = 0; i < 20; i++)
        printf("%d ", primeList[i]);
    printf("\n");
    printf("isPrimeByLookup(19)==%d\n", isPrimeByLookup(19));
    findLongest(LONGEST_MAX_VALUE);
    return 0;
}

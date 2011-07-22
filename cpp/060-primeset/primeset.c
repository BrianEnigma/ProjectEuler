#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/* The primes 3, 7, 109, and 673, are quite remarkable. By taking any two
 * primes and concatenating them in any order the result will always be prime.
 * For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of
 * these four primes, 792, represents the lowest sum for a set of four primes
 * with this property.
 *
 * Find the lowest sum for a set of five primes for which any two primes
 * concatenate to produce another prime.
 */

#define PRIME_LIST_SIZE 10000
#define SEARCH_DEPTH 500
unsigned int listOfPrimes[PRIME_LIST_SIZE];

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

void fillPrimeList()
{
    unsigned int position = 0;
    unsigned int number = 2;
    while (position < PRIME_LIST_SIZE)
    {
        if (isPrime_ui(number))
            listOfPrimes[position++] = number;
        number++;
    }
    printf("Largest prime in our list is %d\n", listOfPrimes[PRIME_LIST_SIZE - 1]);
}

// Binary-search list of primes
unsigned char isPrime(unsigned int value)
{
    int bottom = 0;
    int top = PRIME_LIST_SIZE - 1;
    if (value > listOfPrimes[top])
    {
        printf("ERROR: Past end of list of primes!\n");
        exit(1);
    }
    while (bottom <= top)
    {
        int middle = (top - bottom) / 2 + bottom;
        if (listOfPrimes[middle] == value)
            return 1;
        else if (listOfPrimes[middle] < value)
            bottom = middle + 1;
        else
            top = middle - 1;
    }
    return 0;
}

int numberLength(unsigned int n)
{
    if (n <= 9)                 return 10;
    else if (n <= 99)           return 100;
    else if (n <= 999)          return 1000;
    else if (n <= 9999)         return 10000;
    else if (n <= 99999)        return 100000;
    else if (n <= 999999)       return 1000000;
    else if (n <= 9999999)      return 10000000;
    else return -1000; //  this should get someone's attention
}

unsigned char isConcatPrime(unsigned int value1, unsigned int value2, unsigned char verbose)
{
    unsigned int concatValue;
    if (verbose)
        printf("Testing %d,%d: ", value1, value2);
    concatValue = value1 * numberLength(value2) + value2;
    if (verbose)
        printf("%d", concatValue);
    if (!isPrime_ui(concatValue))
    {
        if (verbose)
            printf(" not prime, fail\n");
        return 0;
    }
    concatValue = value2 * numberLength(value1) + value1;
    if (verbose)
        printf(" %d", concatValue);
    if (!isPrime_ui(concatValue))
    {
        if (verbose)
            printf(" not prime, fail\n");
        return 0;
    }
    if (verbose)
        printf(" good!\n");
    return 1;
}

unsigned char testSet(unsigned int *setStart, unsigned int setSize)
{
    unsigned int sum = 0;
    for (unsigned int a = 0; a < setSize - 1; a++)
        for (unsigned int b = a + 1; b < setSize; b++)
            if (!isConcatPrime(*(setStart + a), *(setStart + b), 0))
                return 0;
    printf("MATCHING SET! ");
    for (int i = 0; i < setSize; i++)
    {
        printf("%d ", *(setStart + i));
        sum += *(setStart + i);
    }
    printf("= %d\n", sum);
    return 1;
}

void findSetRecursive(unsigned int *setStart, unsigned int setMaxSize, unsigned int currentSetSize, unsigned int listPosition)
{
    unsigned int top;
    if (currentSetSize == setMaxSize)
    {
#if 0
        for (int i = 0; i < setMaxSize; i++)
            printf("%d ", *(setStart + i));
        printf("\n");
#endif
        testSet(setStart, currentSetSize);
        return;
    }
    top = listPosition + SEARCH_DEPTH;
    if (top > PRIME_LIST_SIZE)
        top = PRIME_LIST_SIZE;
    for (unsigned int i = listPosition; i < top; i++)
    {
        if (currentSetSize == 0)
            printf("Exploring set starting with %d\n", listOfPrimes[i]);
        *(setStart + currentSetSize) = listOfPrimes[i];
        findSetRecursive(setStart, setMaxSize, currentSetSize + 1, i + 1);
    }
}

int main(int argc, char **argv)
{
    unsigned int knownGoodSet[] = {3, 7, 109, 673};
    //unsigned int mySet[4];
    unsigned int mySet[5];
    printf("Filling cached list of primes\n");
    fillPrimeList();
    printf("Preflight checklist\n");
    for (int i = 2; i < 15; i++)
        printf("isPrime(%d) == %d\n", i, isPrime(i));
    isConcatPrime(7, 109, 1);
    isConcatPrime(5, 109, 1);
    testSet(knownGoodSet, 4);
    knownGoodSet[1] = 11;
    testSet(knownGoodSet, 4);
    printf("This time, for reals:\n");
    // We're starting with "3" instead of "2" as our initial prime in the set
    // because of the concat test.  Any number ending in 2 is even and can't
    // be prime, so no point in having 2 in our set.
    findSetRecursive(mySet, sizeof(mySet) / sizeof(mySet[0]), 0, 1);
    return 0;
}

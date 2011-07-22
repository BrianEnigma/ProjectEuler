#include <stdio.h>
#include <stdlib.h>
//#define BIGNUM
#include "common.h"
/*
 * By replacing the 1^(st) digit of *57, it turns out that six of the
 * possible values: 157, 257, 457, 557, 757, and 857, are all prime.
 *
 * By replacing the 3^(rd) and 4^(th) digits of 56**3 with the same digit,
 * this 5-digit number is the first example having seven primes, yielding the
 * family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993.
 * Consequently 56003, being the first member of this family, is the smallest
 * prime with this property.
 *
 * Find the smallest prime which, by replacing part of the number (not
 * necessarily adjacent digits) with the same digit, is part of an eight
 * prime value family.
 */

#define MAX_LIST 10000000
unsigned int primeList[MAX_LIST];
unsigned int primeListLength = 0;

int isPrimeByLookup(unsigned int value)
{
    for (unsigned int position = 0; (position < primeListLength) && (primeList[position] <= value); position++)
        if (primeList[position] == value)
            return 1;
    if (value > primeList[primeListLength - 1])
        printf("WARNING: past end of prime list (%d %d)\n", value, primeList[primeListLength - 1]);
    return 0;
}

void fillPrimeList()
{
    for (unsigned int i = 2; i <= 10000000; i++)
        if (isPrime_ui(i))
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

int highestBit(unsigned int n)
{
    int result = -1;
    while (n > 0)
    {
        result++;
        n >>= 1;
    }
    return result;
}

int bitCount(unsigned int n)
{
    int result = 0;
    while (n > 0)
    {
        if (n & 0x01)
            result++;
        n >>= 1;
    }
    return result;
}

void printBinary(unsigned int n)
{
    char buffer[64] = "";
    char *p = buffer;
    while (n)
    {
        *p++ = (n & 0x01) ? '1' : '0';
        n >>= 1;
    }
    p--;
    while (p >= &buffer[0])
    {
        printf("%c", *p);
        p--;
    }
    printf("\n");
}

unsigned int replaceDigits(unsigned int original, int bitmask, int newDigit)
{
    int tensPlace = 1;
    unsigned int num;
    while (bitmask > 0)
    {
        if (bitmask & 0x01)
        {
            //                                      original=12345 tensPlace=100 newDigit=0
            num = (original / tensPlace) / 10;  //  num = 123
            //printf("%d\n", num);
            num = (num * 10 + newDigit);        //  num = 129
            //printf("%d\n", num);
            original = (num * tensPlace) + (original % tensPlace); // num=12945
            //printf("%d\n", original);
        }
        bitmask >>= 1;
        tensPlace *= 10;
    }
    return original;
}

void test()
{
    printf("highestBit(64)=%d\n", highestBit(64));
    printf("highestBit(65)=%d\n", highestBit(65));
    printf("bitCount(64)=%d\n", bitCount(64));
    printf("bitCount(65)=%d\n", bitCount(65));
    printf("replaceDigits(12345, 0x04, 9)=%d\n", replaceDigits(12345, 0x04, 9));
    printf("replaceDigits(1234567, 0x0A, 9)=%d\n", replaceDigits(1234567, 0x0A, 9));
}

int main(int argc, char **argv)
{
    int bestHitCount = 0;
    char hitCount = 0;
    char win = 0;
    unsigned int counter = 100;
    //unsigned int counter = 56003;
    unsigned int bestBits = 0;
    fillPrimeList();
    test();
    //return 0;
    for (; !win; counter++)
    {
        int length = numberLength(counter);
        unsigned int bits = 2;
        if (!isPrimeByLookup(counter))
            continue;
        while (!win && (highestBit(bits) + 1 <= length))
        {
            bits++;
            if (bitCount(bits) != 2)
                continue;
            hitCount = 0;
            //printf("%d\n", counter);
            //printBinary(bits);
            for (int digit = 0; digit <= 9; digit++)
            {
                unsigned int tempInt = replaceDigits(counter, bits, digit);
                //printf("    %d\n", tempInt);
                if (isPrimeByLookup(tempInt))
                {
                    //printf("++++%d\n", tempInt);
                    hitCount++;
                    bestBits = bits;
                }
            }
            if (hitCount >= 8)
                win = 1;
        }
        if (hitCount > bestHitCount)
        {
            bestHitCount = hitCount;
            printf("new best: %d\n%d\n", hitCount, counter);
            printBinary(bestBits);
        }
        //if ((hitCount > 0) || (counter == 56003))
        //    printf("%d:%d\n", counter, hitCount);
        //if (counter == 56003)
        //    break;
        if (hitCount >= 7)
            printf("%d:%d\n", counter, hitCount);
    }
    printf("%d:%d\n", counter, hitCount);
    return 0;
}

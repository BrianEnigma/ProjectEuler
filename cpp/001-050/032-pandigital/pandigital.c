#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * We shall say that an n-digit number is pandigital if it makes use of all
 * the digits 1 to n exactly once; for example, the 5-digit number, 15234, is
 * 1 through 5 pandigitial.
 *
 * The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing
 * multiplicand, multiplier, and product is 1 through 9 pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/product identity
 * can be written as a 1 through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so be sure to only
 * include it once in your sum.
 *
 */
#define min(a,b) (a<b) ? a : b
#define max(a,b) (a>b) ? a : b

char products[10000];

int checkWin(char *digitsUsed, int product)
{
    char localDigitsUsed[10];
    memcpy(localDigitsUsed, digitsUsed, 10);
    while (product > 0)
    {
        int digit = product % 10;
        localDigitsUsed[digit]++;
        product /= 10;
    }
    // Shouldn't ever be a zero
    if (localDigitsUsed[0] != 0)
        return 0;
    // 1..9 should each occur once and only once
    for (int i = 1; i <= 9; i++)
        if (localDigitsUsed[i] != 1)
            return 0;
    return 1;
}

int calculateRecurse(char *digitsUsed, int multiplier1, int multiplier2)
{
    // Check win state
    if (checkWin(digitsUsed, multiplier1 * multiplier2))
    {
        printf("%d x %d = %d\n", min(multiplier1, multiplier2), max(multiplier1, multiplier2), multiplier1 * multiplier2);
        products[multiplier1 * multiplier2] = 1;
        return 1;
    }
    // Assuming multipliers are <= 3 digits, exit condition if greater
    if ((multiplier1 > 999) || (multiplier2 > 999))
        return 0;
    // Try each digit from 1..9
    for (int i = 1; i <= 9; i++)
    {
        if (!digitsUsed[i])
        {
            digitsUsed[i] = 1;
            calculateRecurse(digitsUsed, multiplier1 * 10 + i, multiplier2);
            calculateRecurse(digitsUsed, multiplier1, multiplier2 * 10 + i);
            digitsUsed[i] = 0;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int sum = 0;
    char digitsUsed[10];
    memset(digitsUsed, 0, sizeof(digitsUsed));
    memset(products, 0, sizeof(products));
    calculateRecurse(digitsUsed, 0, 0);
    for (int i = 0; i < sizeof(products); i++)
        if (products[i])
            sum += i;
    printf("sum of products is %d\n", sum);
    return 0;
}

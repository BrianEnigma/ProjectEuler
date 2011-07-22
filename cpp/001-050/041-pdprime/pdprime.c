#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * We shall say that an n-digit number is pandigital if it makes use of all
 * the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital
 * and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 *
 */

int isPandigitalN(unsigned int number, unsigned char n)
{
    char digits[10];
    memset(digits, 0, sizeof(digits));
    while (number > 0)
    {
        char digit = number % 10;
        if ((digit == 0) || (digit > n))
            return 0;
        digits[digit]++;
        number /= 10;
    }
    if (digits[0]) // can't be a zero
        return 0;
    for (int i = 1; i < 10; i++)
    {
        if ((i <= n) && (digits[i] != 1))
            return 0;
        if ((i > n) && (digits[i] != 0))
            return 0;
    }
    return 1;
}

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

void test()
{
    unsigned int numbers[] = {987654321, 987654322, 54321, 65432};
    unsigned char n[] = {9, 9, 5, 5};
    for (int i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++)
        printf("isPandigitalN(%d,%d) == %d\n", numbers[i], n[i], isPandigitalN(numbers[i], n[i]));
}

int main(int argc, char **argv)
{
    test();
    for (unsigned char n = 9; n >= 1; n--)
    {
        unsigned int value = 0;
        unsigned int lowerValue = 0;
        for (int i = n; i >= 1; i--)
        {
            value = value * 10 + i;
            lowerValue = lowerValue * 10 + (n - i + 1);
        }
        printf("Starting with %d..%d, pandigital n %d\n", value, lowerValue, n);
        while (value >= lowerValue)
        {
            if (!isPandigitalN(value, n))
            {
                //printf("%d is not pandigital-%d\n", value, n);
                value--;
                continue;
            }
            if (!isPrime(value))
            {
                //printf("%d is not prime\n", value);
                value--;
                continue;
            }
            printf("%d is pandigital-n and prime, with n=%d\n", value, n);
            return 0;
        }
    }
    return 0;
}

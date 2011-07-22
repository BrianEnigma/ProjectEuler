#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Surprisingly there are only three numbers that can be written as the sum of
 * fourth powers of their digits:
 *
 *  1634 = 1^(4) + 6^(4) + 3^(4) + 4^(4)
 *  8208 = 8^(4) + 2^(4) + 0^(4) + 8^(4)
 *  9474 = 9^(4) + 4^(4) + 7^(4) + 4^(4)
 *
 * As 1 = 1^(4) is not a sum it is not included.
 *
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 *
 * Find the sum of all the numbers that can be written as the sum of fifth
 * powers of their digits.
 *
 */

unsigned int power(int value, int exponent)
{
    unsigned int result = 1;
    // Shortcuts
    if ((value == 0) || (value == 1))
        return value;
    if (exponent == 0)
        return 1;
    // Calculate power iteratively
    for (int i = 0; i < exponent; i++)
        result *= value;
    return result;
}

int isMatch(unsigned int value, int length)
{
    unsigned int runningTotal = 0;
    for(int currentValue = value; currentValue > 0; currentValue /= 10)
        runningTotal += power(currentValue % 10, length);
    return (runningTotal == value);
}

int doCalculation(int min, int max, int length)
{
    unsigned int runningTotal = 0;
    for (int i = min; i <= max; i++)
        if (isMatch(i, length))
        {
            printf("%d\n", i);
            runningTotal += i;
        }
    printf("Total = %d\n", runningTotal);
}

int main(int argc, char **argv)
{
    // Do example
    doCalculation(2, 9999, 4);
    // Do real
    doCalculation(2, 999999, 5);
    return 0;
}

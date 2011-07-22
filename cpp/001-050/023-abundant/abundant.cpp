#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/* A perfect number is a number for which the sum of its proper divisors is
 * exactly equal to the number. For example, the sum of the proper divisors
 * of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect
 * number.
 *
 * A number whose proper divisors are less than the number is called deficient
 * and a number whose proper divisors exceed the number is called abundant.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
 * number that can be written as the sum of two abundant numbers is 24. By
 * mathematical analysis, it can be shown that all integers greater than 28123
 * can be written as the sum of two abundant numbers. However, this upper
 * limit cannot be reduced any further by analysis even though it is known
 * that the greatest number that cannot be expressed as the sum of two abundant
 * numbers is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the
 * sum of two abundant numbers.
 *
 */

#define MAX 28123
int integerType[MAX];
char isSum[MAX];

/// Returns 1 for abundant, 0 for perfect, -1 for deficient
int primeSumCompare(int number)
{
    int factorSum = 1;
    int max = number / 2;
    //printf("primeSumCompare for %d\n", number);
    //printf("1");
    for (int i = 2; i <= max; i++)
    {
        if ((number % i) == 0)
        {
            //printf("+%d", i);
            factorSum += i;
        }
    }
    //printf("=%d\n", factorSum);
    if (factorSum == number)
        return 0;
    return (factorSum > number) ? 1 : -1;
}

int main(int argc, char **argv)
{
    unsigned int total = 0;
    printf("%d : %d\n", 12, primeSumCompare(12));
    printf("%d : %d\n", 28, primeSumCompare(28));
    printf("Calculating table\n");
    for (int i = 2; i < MAX; i++)
        integerType[i] = primeSumCompare(i);
    printf("Done calculating table\n");
    printf("Sifting sums\n");
    memset(isSum, 0, sizeof(isSum));
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            int sum = 0;
            if ((integerType[i] > 0) && (integerType[j] > 0))
                sum = i + j;
            if ((sum > 1) && (sum < MAX) && !isSum[sum])
            {
                printf("%d+%d = %d\n", i, j, sum);
                isSum[sum] = 1;
            }
        }
    printf("Calculating total\n");
    for (int i = 1; i < MAX; i++)
        if (!isSum[i])
        {
            total += i;
        }
    printf("Total is %d\n", total);
    return 0;
}

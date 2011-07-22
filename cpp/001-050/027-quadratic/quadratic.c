#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*
 * Euler published the remarkable quadratic formula:
 *
 * n^2 + n + 41
 *
 * It turns out that the formula will produce 40 primes for the consecutive
 * values n = 0 to 39. However, when n = 40, 40^(2) + 40 + 41 = 40(40 + 1) + 41
 * is divisible by 41, and certainly when n = 41, 41^2 + 41 + 41 is clearly
 * divisible by 41.
 *
 * Using computers, the incredible formula  n^2 - 79n + 1601 was discovered,
 * which produces 80 primes for the consecutive values n = 0 to 79. The product
 * of the coefficients, -79 and 1601, is -126479.
 *
 * Considering quadratics of the form:
 *
 *  n^2 + an + b, where |a| < 1000 and |b| < 1000
 *
 *  where |n| is the modulus/absolute value of n
 *  e.g. |11| = 11 and |-4| = 4
 *
 * Find the product of the coefficients, a and b, for the quadratic expression
 * that produces the maximum number of primes for consecutive values of n,
 * starting with n = 0.
 *
 */
int bestA, bestB, bestConsecutive = 0;

int isPrime(int value)
{
    int max;
    // Fail by definition (prime has to be > 1)
    if (value <= 1)
        return 0;
    // Check if prime
    max = sqrt(value) + 1;
    for (int i = 2; i <= max; i++)
        if ((value % i) ==  0)
            return 0;
    return 1;
}

int eulerQuadratic(int a, int b, char forcePrint)
{
    int counter = 0;
    while (1)
    {
        int result = (counter * counter) + (a * counter) + b;
        if (!isPrime(result))
            break;
        counter++;
    }
    if (counter > bestConsecutive)
    {
        printf("a=%d, b=%d found %d consecutive primes\n", a, b, counter);
        bestA = a;
        bestB = b;
        bestConsecutive = counter;
    } else if (forcePrint)
        printf("a=%d, b=%d found %d consecutive primes\n", a, b, counter);
}

int main(int argc, char **argv)
{
    // Sanity-test function based on stated examples
    eulerQuadratic(1, 41, 1);
    eulerQuadratic(-79, 1601, 0);
    // Calculate!
    bestConsecutive = 0; // reset because the two above set it as a side-effect
    for (int a = -1000; a <= 1000; a++)
        for (int b = -1000; b <= 1000; b++)
            eulerQuadratic(a, b, 0);
    printf("bestA=%d, bestB=%d, bestConsecutive=%d\n", bestA, bestB, bestConsecutive);
    printf("bestA*bestB=%d\n", bestA * bestB);
    return 0;
}

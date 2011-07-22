#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the factorial of
 * their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 *
 */
unsigned int factorial(unsigned int n)
{
    unsigned int result = 1;
    if (n == 0)
        return 0;
    while (n > 1)
        result *= n--;
    return result;
}

unsigned int factorialDigits(unsigned int n)
{
    unsigned int result = 0;
    while (n > 0)
    {
        result += factorial(n % 10);
        n /= 10;
    }
    return result;
}

void test()
{
    for (int i = 0; i <= 10; i++)
        printf("%d! = %d\n", i, factorial(i));
    printf("factorialDigits(145) == %d\n", factorialDigits(145));
}

int main(int argc, char **argv)
{
    const int MAX = 100000;
    int throttle = 0;
    int sum = 0;
    int n = 3;
    test();
    while (throttle < MAX)
    {
        if (factorialDigits(n) == n)
        {
            printf("%d\n", n);
            sum += n;
            throttle = 0;
        }
        n++;
        throttle++;
    }
    printf("Hit run of %d non-hits\n", MAX);
    return 0;
}

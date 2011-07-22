#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*The fraction 49/98 is a curious fraction, as an inexperienced mathematician
 * in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which
 * is correct, is obtained by cancelling the 9s.
 *
 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
 *
 * There are exactly four non-trivial examples of this type of fraction, less
 * than one in value, and containing two digits in the numerator and
 * denominator.
 *
 * If the product of these four fractions is given in its lowest common terms,
 * find the value of the denominator.
 *
 */
#define firstDigit(n) (n / 10 % 10)
#define secondDigit(n) (n % 10)
int cumulativeNumerator = 1, cumulativeDenominator = 1;

void simplify(int *numerator, int *denominator)
{
    int i = 2;
    while (i <= *numerator)
    {
        if ( ((*numerator % i) == 0) && ((*denominator % i) == 0) )
        {
            *numerator /= i;
            *denominator /= i;
        } else
            i++;
    }
}

void test()
{
    int numerator, denominator;
    numerator = 10;
    denominator = 20;
    printf("%d/%d = ", numerator, denominator);
    simplify(&numerator, &denominator);
    printf("%d/%d\n", numerator, denominator);
    numerator = 49;
    denominator = 98;
    printf("%d/%d = ", numerator, denominator);
    simplify(&numerator, &denominator);
    printf("%d/%d\n", numerator, denominator);
}

void goofyCancel(int numerator, int denominator)
{
    int n1, d1, n2, d2;
    if (numerator == denominator)
        return;
    if (firstDigit(numerator) == secondDigit(denominator))
    {
        n1 = numerator;
        d1 = denominator;
        n2 = secondDigit(numerator);
        d2 = firstDigit(denominator);
        simplify(&n1, &d1);
        simplify(&n2, &d2);
        if ((n1 == n2) && (d1 == d2))
        {
            printf("%d/%d => %d/%d = %d/%d\n", numerator, denominator, secondDigit(numerator), firstDigit(denominator), n1, d1);
            if ((n1 / d1) < 1)
            {
                cumulativeNumerator *= numerator;
                cumulativeDenominator *= denominator;
            }
        }
    }
    if (secondDigit(numerator) == firstDigit(denominator))
    {
        n1 = numerator;
        d1 = denominator;
        n2 = firstDigit(numerator);
        d2 = secondDigit(denominator);
        simplify(&n1, &d1);
        simplify(&n2, &d2);
        if ((n1 == n2) && (d1 == d2))
        {
            printf("%d/%d => %d/%d = %d/%d\n", numerator, denominator, firstDigit(numerator), secondDigit(denominator), n1, d1);
            if ((n1 / d1) < 1)
            {
                cumulativeNumerator *= numerator;
                cumulativeDenominator *= denominator;
            }
        }
    }
}

int main(int argc, char **argv)
{
    test();
    for (int d = 10; d <= 99; d++)
        for (int n = 10; n <= 99; n++)
            goofyCancel(n, d);
    printf("%d/%d\n", cumulativeNumerator, cumulativeDenominator);
    simplify(&cumulativeNumerator, &cumulativeDenominator);
    printf("%d\n", cumulativeDenominator);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/*
 * The number 3797 has an interesting property. Being prime itself, it is
 * possible to continuously remove digits from left to right, and remain prime
 * at each stage: 3797, 797, 97, and 7. Similarly we can work from right to
 * left: 3797, 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both truncatable from left
 * to right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 *
 *
 * -------
 * BRIAN NOTE: a more elegant way to do this in the future might be to 
 * composite up larger numbers from single-digit primes.
 */

void printNumber(const char *s1, mpz_t n, const char *s2)
{
    printf("%s", s1);
    mpz_out_str(stdout, 10, n);
    printf("%s", s2);
}

int isPrime(mpz_t n)
{
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t remainder;

    if (mpz_cmp_ui(n, 1) <= 0) // negatives, zero, 1 : not prime
        return 0;
    if (mpz_cmp_ui(n, 2) == 0) // 2 : prime
        return 1;
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    mpz_sqrt(maxIterator, n);
    mpz_add_ui(maxIterator, maxIterator, 1); // round up
    for (mpz_set_ui(iterator, 2); mpz_cmp(iterator, maxIterator) <= 0; mpz_add_ui(iterator, iterator, 1))
    {
        mpz_cdiv_r(remainder, n, iterator);
        if (mpz_cmp_ui(remainder, 0) == 0)
            return 0;
    }
    return 1;
}

unsigned int numberLength(mpz_t n)
{
    unsigned int length = 1;
    mpz_t magnitude;
    mpz_init(magnitude);
    mpz_set_ui(magnitude, 10);
    while (mpz_cmp(n, magnitude) >= 0)
    {
        mpz_mul_ui(magnitude, magnitude, 10);
        length++;
    }
    return length;
}

unsigned int isTruncatableRight(mpz_t n)
{
    mpz_t value;
    mpz_init(value);
    mpz_set(value, n);
    while (mpz_cmp_ui(value, 0) > 0)
    {
        //printNumber("right ", value, "\n");
        if (!isPrime(value))
            return 0;
        mpz_tdiv_q_ui(value, value, 10);
    }
    return 1;
}

unsigned int isTruncatableLeft(mpz_t n)
{
    unsigned int len = numberLength(n);
    mpz_t value, power;
    mpz_init(value);
    mpz_init(power);
    mpz_set(value, n);
    mpz_set_ui(power, 1);
    for (unsigned int i = 1; i < len; i++)
        mpz_mul_ui(power, power, 10);
    while (mpz_cmp_ui(power, 0) > 0)
    {
        //printNumber("left ", value, ", power ");
        //printNumber("", power, "\n");
        if (!isPrime(value))
            return 0;
        mpz_mod(value, value, power);
        mpz_tdiv_q_ui(power, power, 10);
    }
    return 1;
}

void test()
{
    unsigned int numbers[] = {1,40,99,100,101,500,998,999,1000,1001};
    mpz_t n;
    mpz_init(n);
    for (int i = 0; i < 30; i++)
    {
        mpz_set_ui(n, i);
        printf("isPrime(%d)==%d\n", i, isPrime(n));
    }
    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++)
    {
        mpz_set_ui(n, numbers[i]);
        printf("isnumberLength(%d)==%d\n", numbers[i], numberLength(n));
    }
    mpz_set_ui(n, 3797); printf("isTruncatableRight(3797)==%d\n", isTruncatableRight(n));
    mpz_set_ui(n, 3797); printf("isTruncatableLeft(3797)==%d\n", isTruncatableLeft(n));
}

int main(int argc, char **argv)
{
    int counter = 0;
    mpz_t n, sum;
    test();
    mpz_init(n);
    mpz_set_ui(n, 8);
    mpz_init(sum);
    while (counter < 11)
    {
        if (isTruncatableLeft(n) && isTruncatableRight(n))
        {
            printNumber("", n, "\n");
            counter++;
            mpz_add(sum, sum, n);
        }
        mpz_add_ui(n, n, 1);
    }
    printNumber("total=", sum, "\n");
    return 0;
}

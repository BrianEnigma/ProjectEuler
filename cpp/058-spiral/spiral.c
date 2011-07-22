#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
/*
 * Starting with 1 and spiralling anticlockwise in the following way, a square
 * spiral with side length 7 is formed.
 *
 * 37 36 35 34 33 32 31
 * 38 17 16 15 14 13 30
 * 39 18  5  4  3 12 29
 * 40 19  6  1  2 11 28
 * 41 20  7  8  9 10 27
 * 42 21 22 23 24 25 26
 * 43 44 45 46 47 48 49
 *
 * It is interesting to note that the odd squares lie along the bottom right
 * diagonal, but what is more interesting is that 8 out of the 13 numbers
 * lying along both diagonals are prime; that is, a ratio of 8/13  62%.
 *
 * If one complete new layer is wrapped around the spiral above, a square
 * spiral with side length 9 will be formed. If this process is continued,
 * what is the side length of the square spiral for which the ratio of primes
 * along both diagonals first falls below 10%?
 *
 */

int isPrime_mpz(mpz_t n)
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

unsigned int calculateNextIteration()
{
    static unsigned char initialized = 0;
    static mpz_t primeHits;
    static mpz_t countTotal;
    static mpz_t highestCorner;
    static mpz_t size;
    mpz_t ratio;
    unsigned int ratioInt;
    char *s;
    if (!initialized) // Initialize statics
    {
        // The 7x7 start spiral we were given...
        mpz_init(size);             mpz_set_ui(size, 3);
        mpz_init(highestCorner);    mpz_set_ui(highestCorner, 9);
        mpz_init(primeHits);        mpz_set_ui(primeHits, 3);
        mpz_init(countTotal);       mpz_set_ui(countTotal, 5);
        initialized = 1;
    }
    mpz_init(ratio); // borrowing ratio for this quick UI output
    mpz_set(ratio, size);
    mpz_add_ui(ratio, ratio, 2);
    printf("size="); mpz_out_str(stdout, 10, ratio); printf(" corners=[");
    // Calculate the next four corners
    for (int i = 0; i < 4; i++)
    {
        mpz_add(highestCorner, highestCorner, size);
        mpz_add_ui(highestCorner, highestCorner, 1);
        mpz_out_str(stdout, 10, highestCorner); printf(" ");
        if (isPrime_mpz(highestCorner))
            mpz_add_ui(primeHits, primeHits, 1);
        mpz_add_ui(countTotal, countTotal, 1);
    }
    printf("] hits="); mpz_out_str(stdout, 10, primeHits);
    printf(" tital="); mpz_out_str(stdout, 10, countTotal);
    mpz_add_ui(size, size, 2);
    mpz_set(ratio, primeHits);
    mpz_mul_ui(ratio, ratio, 100);
    mpz_tdiv_q(ratio, ratio, countTotal);
    ratioInt = mpz_get_ui(ratio);
    printf(" ratio=%d\n", ratioInt);
    return ratioInt;
}


int main(int argc, char **argv)
{
    unsigned int ratio;
#if 0
    for (int i = 0; i < 10; i++)
        calculateNextIteration();
    return 0;
#endif
    while ((ratio = calculateNextIteration()) >= 10)
        ;
    return 0;
}

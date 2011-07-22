#include <stdio.h>
#include <string.h>
#include <gmp.h>

/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see 
that the 6th prime is 13.

What is the 10001st prime number?
*/

//#define NTH 6
#define NTH 10001

int isPrime(mpz_t maxValue)
{
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t remainder;
    
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    //mpz_cdiv_q_ui(maxIterator, maxValue, 2);
    mpz_sqrt(maxIterator, maxValue);
    for (mpz_set_ui(iterator, 2); mpz_cmp(iterator, maxIterator) <= 0; mpz_add_ui(iterator, iterator, 1))
    {
        mpz_cdiv_r(remainder, maxValue, iterator);
        if (mpz_cmp_ui(remainder, 0) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    mpz_t value;
    int primeCounter = 0;
    mpz_init_set_ui(value, 2);
    while (primeCounter < NTH)
    {
        if (isPrime(value))
        {
            primeCounter++;
            printf("Prime number %d is %s\n", primeCounter, mpz_get_str(NULL, 10, value));
        }
        mpz_add_ui(value, value, 1);
    }
    return 0;
}

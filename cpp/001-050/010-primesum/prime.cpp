#include <stdio.h>
#include <string.h>
#include <gmp.h>

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

//#define MAX_VAL 10
#define MAX_VAL 2000000

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
    mpz_t sum;
	mpz_init_set_ui(sum, 0);
	for (mpz_init_set_ui(value, 2); mpz_cmp_ui(value, MAX_VAL) <= 0; mpz_add_ui(value, value, 1))
    {
        if (isPrime(value))
        {
			mpz_add(sum, sum, value);
            //printf("Prime number %s makes sum %s\n", mpz_get_str(NULL, 10, value), mpz_get_str(NULL, 10, sum));
        }
    }
	printf("Sum is %s\n", mpz_get_str(NULL, 10, sum));
    return 0;
}

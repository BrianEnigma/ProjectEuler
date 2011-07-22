#include <stdio.h>
#include <string.h>
#include <gmp.h>
/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

//#define VAL 13195
#define VAL 600851475143

#define XMK_STR(x)  #x
#define MK_STR(x)   XMK_STR(x)

int isPrime(mpz_t maxValue)
{
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t remainder;
    
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    mpz_cdiv_q_ui(maxIterator, maxValue, 2);
    for (mpz_set_ui(iterator, 2); mpz_cmp(iterator, maxIterator) < 0; mpz_add_ui(iterator, iterator, 1))
    {
        mpz_cdiv_r(remainder, maxValue, iterator);
        if (mpz_cmp_ui(remainder, 0) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t maxValue;
    mpz_t remainder;
    
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    mpz_init_set_str(maxValue, MK_STR(VAL), 10);
    //mpz_cdiv_q_ui(maxIterator, maxValue, 2);
    mpz_sqrt(maxIterator, maxValue);
    printf("Starting with: %s\n", mpz_get_str(NULL, 10, maxValue));
    for (mpz_set_ui(iterator, 2); mpz_cmp(iterator, maxIterator) <= 0; mpz_add_ui(iterator, iterator, 1))
    {
        mpz_cdiv_r(remainder, maxValue, iterator);
        if (mpz_cmp_ui(remainder, 0) == 0)
        {
            printf("Factor: %s", mpz_get_str(NULL, 10, iterator));
            if (isPrime(iterator))
                printf(" PRIME!\n");
            printf("\n");
        }
    }
    return 0;
}

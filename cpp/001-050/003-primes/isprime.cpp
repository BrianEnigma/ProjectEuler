#include <stdio.h>
#include <string.h>
#include <gmp.h>

int isPrime(const char *s)
{
    mpz_t maxValue;
    mpz_t iterator;
    mpz_t maxIterator;
    mpz_t remainder;
    
    mpz_init_set_str(maxValue, s, 10);
    mpz_init(remainder);
    mpz_init(iterator);
    mpz_init(maxIterator);
    mpz_cdiv_q_ui(maxIterator, maxValue, 2);
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
    int rc;
    if (argc != 2)
    {
        printf("Put number to test for primeness on command line\n");
        return 0;
    }
    rc = isPrime(argv[1]);
    printf("%s\n", rc ? "is prime" : "is composite");
    return rc;
}

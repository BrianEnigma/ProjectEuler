#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/*
 * The series, 1^(1) + 2^(2) + 3^(3) + ... + 10^(10) = 10405071317.
 *
 * Find the last ten digits of the series, 1^(1) + 2^(2) + 3^(3) + ... +
 * 1000^(1000).
 *
 */

int main(int argc, char **argv)
{
    mpz_t sum;
    mpz_t term;
    mpz_t modulus;
    mpz_init(sum);
    mpz_init(modulus);
    for (int i = 1; i <= 1000; i++)
    {
        mpz_init(term);
        mpz_set_ui(term, i);
        mpz_pow_ui(term, term, i);
        mpz_add(sum, sum, term);
        mpz_clear(term);
    }
    mpz_set_str(modulus, "10000000000", 10);
    mpz_mod(sum, sum, modulus);
    mpz_out_str(stdout, 10, sum);
    printf("\n");
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <gmp.h>
/*
n! means n  (n  1)  ...  3  2  1

Find the sum of the digits in the number 100!
*/

int main(int argc, char **argv)
{
    mpz_t sum;
    mpz_t factorial;
    char *s;
    mpz_init_set_ui(sum, 0);
    mpz_init(factorial);
    mpz_fac_ui(factorial, 100);
    s = mpz_get_str(NULL, 10, factorial);
    for (char *c = s; *c; c++)
        mpz_add_ui(sum, sum, *c - '0');
    printf("%s\n", mpz_get_str(NULL, 10, sum));
    return 0;
}

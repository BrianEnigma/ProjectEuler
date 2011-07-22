#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
/*
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the factorial of
 * their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 *
 */
unsigned int factorial[] = {1,1,2,6,24,120,720,5040,40320,362880};

void factorialDigits(mpz_t result, mpz_t n)
{
    mpz_t current;
    mpz_t tmp;
    mpz_init(result);
    mpz_init(current);
    mpz_init(tmp);
    mpz_set(current, n);
    //mpz_out_str(stdout, 10, current);
    //printf("\n");
    while (mpz_cmp_ui(current, 0) > 0)
    {
        int digit = mpz_mod_ui(tmp, current, 10);
        //printf(" %d\n", digit);
        mpz_add_ui(result, result, factorial[digit]);
        mpz_tdiv_q_ui(tmp, current, 10);
        mpz_set(current, tmp);
    }
}

void test()
{
    mpz_t result, n;
    mpz_init(result);
    mpz_init(n);
    for (int i = 0; i < 10; i++)
        printf("%d! = %d\n", i, factorial[i]);
    for (int i = 144; i <= 146; i++)
    {
        mpz_set_ui(n, i);
        factorialDigits(result, n);
        printf("factorialDigits(");
        mpz_out_str(stdout, 10, n);
        printf(") == ");
        mpz_out_str(stdout, 10, result);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    int counter = 0;
    mpz_t sum;
    mpz_t n;
    mpz_t result;
    mpz_init(sum);
    mpz_init(n);
    mpz_init(result);
    mpz_set_ui(sum, 0);
    mpz_set_ui(n, 3);
    test();
    while (1)
    {
        factorialDigits(result, n);
        if (mpz_cmp(result, n) == 0)
        {
            printf("\n");
            mpz_add(sum, sum, n);
            printf(" + ");
            mpz_out_str(stdout, 10, n);
            printf(" = ");
            mpz_out_str(stdout, 10, sum);
            printf("\n");
        }
        mpz_add_ui(n, n, 1);
#if 0
        if (++counter >= 1000)
        {
            printf(".");
            fflush(stdout);
            counter = 0;
        }
#endif
    }
    return 0;
}

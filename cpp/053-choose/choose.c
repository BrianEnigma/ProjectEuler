#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
/* There are exactly ten ways of selecting three from five, 12345:
 *
 * 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
 *
 * In combinatorics, we use the notation, ^(5)C_(3) = 10.
 *
 * In general,
 *
 * ^(n)C_(r) = n! / r!(n-r)!
 * ,where r <= n, n! = nx(n-1)x...x3x2x1, and 0! = 1.
 *
 * It is not until n = 23, that a value exceeds one-million: ^(23)C_(10) =
 * 1144066.
 *
 * How many, not necessarily distinct, values of  ^(n)C_(r), for 1 <= n <= 100,
 * are greater than one-million?
 */

#define TABLE_SIZE 101
mpz_t factorialTable[TABLE_SIZE];
mpz_t cutoff;

void fillFactorialTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        mpz_init(factorialTable[i]);
    mpz_set_ui(factorialTable[0], 1);
    mpz_set_ui(factorialTable[1], 1);
    for (unsigned int i = 2; i < sizeof(factorialTable) / sizeof(factorialTable[0]); i++)
        mpz_mul_ui(factorialTable[i], factorialTable[i - 1], i);
    printf("factorialTable=[");
    mpz_out_str(stdout, 10, factorialTable[1]); printf(" ");
    mpz_out_str(stdout, 10, factorialTable[2]); printf(" ");
    mpz_out_str(stdout, 10, factorialTable[3]); printf(" ");
    mpz_out_str(stdout, 10, factorialTable[4]); printf(" ");
    mpz_out_str(stdout, 10, factorialTable[5]); printf(" ");
    mpz_out_str(stdout, 10, factorialTable[6]); printf(" ... ");
    mpz_out_str(stdout, 10, factorialTable[TABLE_SIZE - 1]); printf("\n");
}

unsigned int choose(unsigned int nInt, unsigned int rInt)
{
    mpz_t n, r, a, b;
    if (    ((nInt - rInt) < 0)
         || ((nInt - rInt) >= TABLE_SIZE)
         || (nInt < 0)
         || (nInt >= TABLE_SIZE)
         || (rInt < 0)
         || (rInt >= TABLE_SIZE))
    {
        printf("bounds fail! n=%d r=%d\n", nInt, rInt);
        exit(1);
    }
    mpz_init(n); mpz_init(r); mpz_init(a); mpz_init(b);
    mpz_set_ui(n, nInt); mpz_set_ui(r, rInt);
    mpz_set(a, factorialTable[nInt - rInt]); // (n - r)!
    mpz_mul(b, factorialTable[rInt], a); // r!(n - r)!
    mpz_tdiv_q(a, factorialTable[nInt], b);
    if (mpz_cmp(a, cutoff) > 0)
    {
        printf("choose(%d,%d)=", nInt, rInt);
        mpz_out_str(stdout, 10, a);
        printf("\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    mpz_init(cutoff);
    mpz_set_ui(cutoff, 1000000);
    int count = 0;
    fillFactorialTable();
    for (unsigned int n = 1; n <= 100; n++)
        for (unsigned int r = 1; r <= n; r++)
            if (choose(n, r))
                count++;
    printf("count is %d\n", count);
    return 0;
}

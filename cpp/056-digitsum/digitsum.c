#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/* A googol (10^(100)) is a massive number: one followed by one-hundred zeros;
 * 100^(100) is almost unimaginably large: one followed by two-hundred zeros.
 * Despite their size, the sum of the digits in each number is only 1.
 *
 * Considering natural numbers of the form, a^(b), where a, b < 100, what is
 * the maximum digital sum?
 */

void digitSum(mpz_t sum, mpz_t value, unsigned char print)
{
    char *s = NULL;
    mpz_init(sum);
    mpz_set_ui(sum, 0);
    if (print)
        s = mpz_get_str(NULL, 10, value);
    mpz_t remainder;
    mpz_init(remainder);
    while (mpz_cmp_ui(value, 0) > 0)
    {
        // Chop off rightmost digit
        mpz_tdiv_qr_ui(value, remainder, value, 10);
        // Add to sum
        mpz_add(sum, sum, remainder);
    }
    if (print)
    {
        char *sumString = mpz_get_str(NULL, 10, sum);
        printf("%s => %s\n", s, sumString);
        free(sumString);
        free(s);
    }
}

void test()
{
    mpz_t value, sum;
    mpz_init(value);
    mpz_set_str(value, "100000000000000000000", 10);
    digitSum(sum, value, 1);
    mpz_set_str(value, "1234567890", 10);
    digitSum(sum, value, 1);
}

int main(int argc, char **argv)
{
    mpz_t maxSum, currentSum;
    unsigned int maxA, maxB;
    mpz_t pow;
    test();
    mpz_init(pow);
    mpz_init(maxSum);
    mpz_init(currentSum);
    mpz_set_ui(maxSum, 0);
    for (unsigned int a = 1; a < 100; a++)
        for (unsigned int b = 1; b < 100; b++)
        {
            mpz_ui_pow_ui(pow, a, b);
            digitSum(currentSum, pow, 0);
            if (mpz_cmp(currentSum, maxSum) > 0)
            {
                char *s;
                mpz_set(maxSum, currentSum);
                maxA = a;
                maxB = b;
                s = mpz_get_str(NULL, 10, currentSum);
                printf("New max: %d ^ %d produced sum %s\n", a, b, s);
                free(s);
            }
        }
    return 0;
}

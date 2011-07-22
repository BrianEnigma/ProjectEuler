#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/*
 *
 */

int hasSameDigits(mpz_t a, mpz_t b)
{
    char *s;
    char digitCount[2][10];
    memset(digitCount, 0, sizeof(digitCount));
    s = mpz_get_str(NULL, 10, a);
    for (char *c = s; *c; c++)
        digitCount[0][*c - '0']++;
    free(s);
    s = mpz_get_str(NULL, 10, b);
    for (char *c = s; *c; c++)
        digitCount[1][*c - '0']++;
    free(s);
    for (int i = 0; i < 10; i++)
        if (digitCount[0][i] != digitCount[1][i])
            return 0;
    return 1;
}

void test()
{
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_set_ui(a, 12345);
    mpz_set_ui(b, 12345);
    printf("1:%d\n", hasSameDigits(a, b));
    mpz_set_ui(a, 12345);
    mpz_set_ui(b, 12346);
    printf("2:%d\n", hasSameDigits(a, b));
    mpz_set_ui(a, 12345);
    mpz_set_ui(b, 12344);
    printf("3:%d\n", hasSameDigits(a, b));
}

int main(int argc, char **argv)
{
    mpz_t n;
    mpz_t mult;
    test();
    mpz_init(n);
    mpz_init(mult);
    mpz_set_ui(n, 1);
    while (1)
    {
        int matches;
        for (int i = 2; (i <= 6); i++)
        {
            mpz_mul_ui(mult, n, i);
            matches = hasSameDigits(n, mult);
            if (!matches)
                break;
        }
        if (matches)
        {
            mpz_out_str(stdout, 10, n);
            printf("\n");
            for (int i = 2; (i <= 6); i++)
            {
                mpz_mul_ui(mult, n, i);
                mpz_out_str(stdout, 10, mult);
                printf("\n");
            }
            return 0;
        }
        mpz_add_ui(n, n, 1);
    };
    return 0;
}

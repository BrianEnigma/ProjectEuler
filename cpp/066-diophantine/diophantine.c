#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gmp.h"

void findDiophantine(mpz_t d, mpz_t x, mpz_t y, unsigned char print)
{
    unsigned char found = 0;
    mpz_t a;
    mpz_t r;
    mpz_init(a);
    mpz_init(r);
    mpz_set_ui(y, 0);
    for (mpz_set_ui(x, 1); !found; mpz_add_ui(x, x, 1))
    {
        mpz_pow_ui(a, x, 2);        // a = x^2
        mpz_sub_ui(a, a, 1);        // a = x^2 - 1
        mpz_tdiv_qr(a, r, a, d);    // a = (x^2 - 1) / d
        // If there was a remainder, fail.
        if (mpz_cmp_ui(r, 0) != 0)
            continue;
        // If "a" is zero, no way
        if (mpz_cmp_ui(a, 0) == 0)
            continue;
        // We've calculated a = (x^2 - 1) / d but really want to find
        // y^2 = (x^2 - 1) / d so y = sqrt(a).  If a isn't a perfect
        // square, fail.
        if (print) {
            printf("  x="); mpz_out_str(stdout, 10, x);
            printf(", y="); mpz_out_str(stdout, 10, a); printf("\n");
        }
        if (!mpz_perfect_square_p(a))
            continue;
        else {
            mpz_sqrt(y, a);
            found = 1;
        }
    }
    if (!found)
    {
        printf("NOT FOUND\n");
        exit(1);
    }
    mpz_clear(a);
    mpz_clear(r);
}

int find()
{
    mpz_t maxX;
    mpz_t d, x, y;
    mpz_init(maxX); mpz_init(d); mpz_init(x); mpz_init(y);
    mpz_set_ui(maxX, 0);
    for (int i = 2; i <= 1000; i++)
    {
        mpz_set_ui(d, i);
        if (mpz_perfect_square_p(d))
            continue;
        findDiophantine(d, x, y, 0);
        printf("D="); mpz_out_str(stdout, 10, d);
        printf(", x="); mpz_out_str(stdout, 10, x);
        printf(", y="); mpz_out_str(stdout, 10, y); printf("\n");
        if (mpz_cmp(x, maxX) > 0)
        {
            printf("New Max: "); mpz_out_str(stdout, 10, x); printf("\n");
            mpz_set(maxX, x);
        }
    }
    return 0;
}

int test()
{
    mpz_t d, x, y;
    mpz_init(d); mpz_init(x); mpz_init(y);
    // 2..7 and then 29 (because 29 is large enough to be interesting, but still smallish)
    for (int i = 2; i <= 29; i++)
    {
        if ((i == 4) || ((i > 7) && (i != 29)))
            continue;
        mpz_set_ui(d, i);
        findDiophantine(d, x, y, i == 29);
        printf("D="); mpz_out_str(stdout, 10, d);
        printf(", x="); mpz_out_str(stdout, 10, x);
        printf(", y="); mpz_out_str(stdout, 10, y); printf("\n");
    }
    return 0;
}

int main(int argc, char **argv)
{
    test();
    find();
    return 0;
}

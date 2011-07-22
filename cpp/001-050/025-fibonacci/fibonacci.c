#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <gmp.h>
/*
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 * F_(n) = F_(n-1) + F_(n-2), where F_(1) = 1 and F_(2) = 1.
 *
 * Hence the first 12 terms will be:
 *
 *  F_(1) = 1
 *  F_(2) = 1
 *  F_(3) = 2
 *  F_(4) = 3
 *  F_(5) = 5
 *  F_(6) = 8
 *  F_(7) = 13
 *  F_(8) = 21
 *  F_(9) = 34
 *  F_(10) = 55
 *  F_(11) = 89
 *  F_(12) = 144
 *
 * The 12th term, F_(12), is the first term to contain three digits.
 *
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 *
 */

#define MAXLEN 1000

int main(int argc, char **argv)
{
    mpz_t f[2];
    mpz_t sum;
    int pos = 0, term = 2, len;
    mpz_init(f[0]);
    mpz_init(f[1]);
    mpz_init(sum);
    mpz_set_ui(f[0], 1);
    mpz_set_ui(f[1], 1);
    printf("Starting\n");
    while (1)
    {
        // Calculate next number
        mpz_add(sum, f[0], f[1]);
        mpz_out_str(stdout, 10, f[0]);
        printf("+");
        mpz_out_str(stdout, 10, f[1]);
        printf("=");
        mpz_out_str(stdout, 10, sum);
        printf("\n");
        mpz_set(f[pos], sum);
        pos = (pos == 0) ? 1 : 0;
        term++;
        // Check exit condition
        len = mpz_sizeinbase(sum, 10); // this only gives a rough estimation; could actually return value of one more
        printf("term %d, length %d\n", term, len);
        if (len >= MAXLEN)
            break;
    }
    printf("Term %d\n", term);
    return 0;
}

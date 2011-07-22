#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/*
 * The number, 1406357289, is a 0 to 9 pandigital number because it is made up
 * of each of the digits 0 to 9 in some order, but it also has a rather
 * interesting sub-string divisibility property.
 *
 * Let d_(1) be the 1^(st) digit, d_(2) be the 2^(nd) digit, and so on. In
 * this way, we note the following:
 *
 * d_(2)d_(3)d_(4)=406 is divisible by 2
 * d_(3)d_(4)d_(5)=063 is divisible by 3
 * d_(4)d_(5)d_(6)=635 is divisible by 5
 * d_(5)d_(6)d_(7)=357 is divisible by 7
 * d_(6)d_(7)d_(8)=572 is divisible by 11
 * d_(7)d_(8)d_(9)=728 is divisible by 13
 * d_(8)d_(9)d_(10)=289 is divisible by 17
 *
 * Find the sum of all 0 to 9 pandigital numbers with this property.
 *
 */

mpz_t sum;

void printNumber(const char *s1, mpz_t n, const char *s2)
{
    printf("%s", s1);
    mpz_out_str(stdout, 10, n);
    printf("%s", s2);
}

int testNumber(mpz_t number)
{
    mpz_t n;
    mpz_t q;
    mpz_init(n);
    mpz_init(q);
    mpz_tdiv_q_ui(n, number, 1000000);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 2) != 0)
        return 0;
    mpz_tdiv_q_ui(n, number, 100000);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 3) != 0)
        return 0;
    mpz_tdiv_q_ui(n, number, 10000);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 5) != 0)
        return 0;
    mpz_tdiv_q_ui(n, number, 1000);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 7) != 0)
        return 0;
    mpz_tdiv_q_ui(n, number, 100);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 11) != 0)
        return 0;
    mpz_tdiv_q_ui(n, number, 10);
    mpz_mod_ui(n, n, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 13) != 0)
        return 0;
    mpz_mod_ui(n, number, 1000);
    //printNumber("", n, "\n");
    if (mpz_mod_ui(q, n, 17) != 0)
        return 0;
    mpz_add(sum, sum, number);
    printNumber("", number, "\n");
    return 1;
}

int testPrintNumber(mpz_t n)
{
    mpz_out_str(stdout, 10, n);
    printf("\n");
}

int recursePandigital(char *digits, char min, char max, char depth, mpz_t number, int (*callback)(mpz_t))
{
    if (depth == 0)
    {
        callback(number);
    }
    for (int i = max; i >= min; i--)
    {
        if (*(digits + i) == 0)
        {
            *(digits + i) = 1;
            mpz_mul_ui(number, number, 10);
            mpz_add_ui(number, number, i);
            recursePandigital(digits, min, max, depth - 1, number, callback);
            mpz_tdiv_q_ui(number, number, 10);
            *(digits + i) = 0;
        }
    }
    return 0;
}

void test()
{
    mpz_t number;
    char digits[10];
    memset(digits, 0, sizeof(digits));
    mpz_init(number);
    //recursePandigital(digits, 0, 3, 4, number, testPrintNumber);
    mpz_set_str(number, "1406357289", 10);
    testNumber(number);
}

int main(int argc, char **argv)
{
    mpz_t number;
    char digits[10];
    memset(digits, 0, sizeof(digits));
    mpz_init(number);
    mpz_init(sum);
    //test();
    recursePandigital(digits, 0, 9, 10, number, testNumber);
    printNumber("ANSWER: ", sum, "\n");
    return 0;
}

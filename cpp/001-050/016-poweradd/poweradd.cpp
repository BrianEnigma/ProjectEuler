#include <stdio.h>
#include <string.h>
#include <gmp.h>
/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/
//#define POWER 15
#define POWER 1000

int main(int argc, char **argv)
{
    char *digits;
    int sum = 0;
    mpz_t total;
    mpz_init_set_ui(total, 1);
    for (int i = 0; i < POWER; i++)
        mpz_mul_ui(total, total, 2);
    digits = mpz_get_str(NULL, 10, total);
    printf("2^%d is %s\n", POWER, digits);
    for (char *c = digits; *c; c++)
        sum += (*c) - '0';
    printf("Sum of digits is %d\n", sum);
    return 0;
}

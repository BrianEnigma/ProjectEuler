#include <stdio.h>
#include <stdlib.h>
//#define BIGNUM
#include "common.h"

int main(int argc, char **argv)
{
    char letters[3] = {'A','B','C'};
    char buffer[10] = "";
    mpz_t num;
    mpz_init(num);
    for (int i = 1; i < 20; i++)
        printf("isPrime_ui(%d)==%d\n", i, isPrime_ui(i));
    for (int i = 1; i < 20; i++)
    {
        mpz_set_ui(num, i);
        printf("isPrime_mpz(%d)==%d\n", i, isPrime_mpz(num));
    }
    doPermutations(letters, 3, 2, buffer, printCallback);
    return 0;
}

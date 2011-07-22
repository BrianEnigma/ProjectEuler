#include <stdio.h>
#include <string.h>
#include <gmp.h>
/*
The following iterative sequence is defined for the set of positive integers:

n -> n/2 (n is even)
n -> 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 
10 terms. Although it has not been proved yet (Collatz Problem), it is thought 
that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

void goNext(mpz_t number) 
{
    if (mpz_divisible_ui_p(number, 2))
        mpz_cdiv_q_ui(number, number, 2);
    else {
        mpz_mul_ui(number, number, 3);
        mpz_add_ui(number, number, 1);
    }
    //printf(" -> %s", mpz_get_str(NULL, 10, number));
}

void test()
{
    mpz_t number;
    mpz_init_set_ui(number, 13);
    while (mpz_cmp_ui(number, 1) > 0)
    {
        goNext(number);
    }
}

int main(int argc, char **argv)
{
    int startNumber, count;
    int bestStartNumber = 1, bestCount = 0;
    for (startNumber = 2; startNumber < 1000000; startNumber++)
    {
        mpz_t number;
        mpz_init_set_ui(number, startNumber);
        count = 0;
        while (mpz_cmp_ui(number, 1) > 0)
        {
            goNext(number);
            count++;
        }
        if (count > bestCount)
        {
            bestCount = count;
            bestStartNumber = startNumber;
            printf("new best count: %d for number %d\n", count, startNumber);
        }
    }
    return 0;
}

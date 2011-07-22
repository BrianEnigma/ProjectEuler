#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
#include <ctype.h>
//#include <gmp.h>
/*
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 *  192 x 1 = 192
 *  192 x 2 = 384
 *  192 x 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital, 192384576. We
 * will call 192384576 the concatenated product of 192 and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by
 * 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the
 * concatenated product of 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be formed
 * as the concatenated product of an integer with (1,2, ... , n) where n > 1?
 *
 */

int isPandigital(const char *s)
{
    char digits[10];
    memset(digits, 0, sizeof(digits));
    while (*s)
    {
        if (!isdigit(*s))
            return 0;
        digits[*s - '0']++;
        s++;
    }
    if (digits[0]) // can't be a zero
        return 0;
    for (int i = 1; i < 10; i++)
        if (digits[i] != 1)
            return 0;
    return 1;
}

void calc(int seed)
{
    char bigBuffer[256] = "";
    char buffer[20];
    unsigned int multiple = 1;
    while (strlen(bigBuffer) < 9)
    {
        sprintf(buffer, "%d", seed * multiple);
        strcat(bigBuffer, buffer);
        multiple++;
    }
    if (strlen(bigBuffer) == 9)
        if (isPandigital(bigBuffer))
            printf("%s : seed=%d n=%d\n", bigBuffer, seed - 1, multiple);
}

void test()
{
    for (int i = 1; i < 10; i++)
        calc(i);
}

int main(int argc, char **argv)
{
    test();
    for (int i = 11; i <= 99999; i++)
        calc(i);
    return 0;
}
